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

/* CONFIG */
// #define LCD_TEST

#include "esp_attr.h"

#include "rom/cache.h"
#include "rom/ets_sys.h"
//#include "rom/spi_flash.h"
#include "rom/crc.h"

#include "soc/soc.h"
#include "soc/dport_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/efuse_reg.h"
#include "soc/rtc_cntl_reg.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "esp_err.h"
#include <stdint.h>
//#include "nvs_flash.h"
//#include "esp_partition.h"

//#include "i_system.h"

#include "spi_lcd.h"
#include "i_video.h"
#include "lcd_test.h"

// TODO: move it to lcd_test.c
uint8_t levels_b[] = {0, 10, 20, 31};
uint8_t levels_g[] = {0, 9, 18, 27, 36, 45, 54, 63};
uint8_t levels_r[] = {0, 4,  8, 12, 16, 20, 24, 31};

// TODO: get rid of this extern as the size may change on the other side.
extern int16_t lcdpal[256];
// end move it to lcd_test.c

extern void jsInit();
extern int doom_main(int argc, char const * const *argv);
extern void spi_lcd_init() ;

void doomEngineTask(void *pvParameters)
{
    char const *argv[]={"doom","-cout","ICWEFDA", NULL};
    doom_main(3, argv);
}

void app_main()
{
	spi_lcd_init();
	jsInit();

	#ifdef LCD_TEST
		// TODO: move it to lcd_test.c
		for (size_t pal_id=0u; pal_id<sizeof(lcdpal); ++pal_id)
		{
			/* create simple palette mapping RGB332 to RGB565 */
			int16_t val = ( levels_r[(pal_id & 0xE0)>>5] << 11) | (levels_g[(pal_id & 0x1C)>>2]<<5) | (levels_b[(pal_id & 0x3)]);
			lcdpal[pal_id] = ((val & 0xFF) << 8) | ((val & 0xFF00) >> 8);
		}
		// end move it to lcd_test.c

		updateTestScreen();

		xTaskCreatePinnedToCore(&lcdTestTask, "lcdTestTask", 18000, NULL, 5, NULL, 0);
	#else // LCD_TEST
		xTaskCreatePinnedToCore(&doomEngineTask, "doomEngine", 18000, NULL, 5, NULL, 0);
	#endif // LCD_TEST

}
