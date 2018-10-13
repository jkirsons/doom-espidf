// Copyright 2016-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <stdlib.h>

#include "doomdef.h"
#include "doomtype.h"
#include "m_argv.h"
#include "d_event.h"
#include "g_game.h"
#include "d_main.h"
#include "gamepad.h"
#include "lprintf.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

//The gamepad uses keyboard emulation, but for compilation, these variables need to be placed
//somewhere. This is as good a place as any.
int usejoystick=0;
int joyleft, joyright, joyup, joydown;


//atomic, for communication between joy thread and main game thread
volatile int joyVal=0;

typedef struct {
	int gpio;
	int *key;
} GPIOKeyMap;

//Mappings from PS2 buttons to keys
static const GPIOKeyMap keymap[]={
	{36, &key_up},
	{34, &key_down},
	{32, &key_left},
	{39, &key_right},
	
	{33, &key_use},				//cross
	{35, &key_fire},			//circle
	{35, &key_menu_enter},
	{0, NULL},
};
/*	
	{0x2000, &key_menu_enter},		//circle
	{0x8000, &key_pause},			//square
	{0x1000, &key_weapontoggle},	//triangle

	{0x8, &key_escape},				//start
	{0x1, &key_map},				//select
	
	{0x400, &key_strafeleft},		//L1
	{0x100, &key_speed},			//L2
	{0x800, &key_straferight},		//R1
	{0x200, &key_strafe},			//R2

	{0, NULL},
};
*/

void gamepadPoll(void)
{
}

static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
/*			event_t ev;
			int level = gpio_get_level(gpio_num);
			for (int i=0; keymap[i].key!=NULL; i++)
				if(keymap[i].gpio == gpio_num)
				{
					ev.type=level?ev_keyup:ev_keydown;
					ev.data1=*keymap[i].key;
					D_PostEvent(&ev);
				}
*/
}


void gpioTask(void *arg) {
    uint32_t io_num;
	int level;
	event_t ev;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
			for (int i=0; keymap[i].key!=NULL; i++)
				if(keymap[i].gpio == io_num)
				{
					level = gpio_get_level(io_num);
					//lprintf(LO_INFO, "GPIO[%d] intr, val: %d\n", io_num, level);
					ev.type=level?ev_keyup:ev_keydown;
					ev.data1=*keymap[i].key;
					D_PostEvent(&ev);
				}
        }
    }
}

void gamepadInit(void)
{
	lprintf(LO_INFO, "gamepadInit: Initializing game pad.\n");
}

void jsInit() 
{
	gpio_config_t io_conf;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    //bit mask of the pins, use GPIO... here
	for (int i=0; keymap[i].key!=NULL; i++)
    	if(i==0)
			io_conf.pin_bit_mask = (1ULL<<keymap[i].gpio);
		else 
			io_conf.pin_bit_mask |= (1ULL<<keymap[i].gpio);
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);


    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    //start gpio task
	xTaskCreatePinnedToCore(&gpioTask, "GPIO", 1500, NULL, 7, NULL, 0);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_SHARED);
    //hook isr handler for specific gpio pin
	for (int i=0; keymap[i].key!=NULL; i++)
    	gpio_isr_handler_add(keymap[i].gpio, gpio_isr_handler, (void*) keymap[i].gpio);

	lprintf(LO_INFO, "jsInit: GPIO task created.\n");
}

