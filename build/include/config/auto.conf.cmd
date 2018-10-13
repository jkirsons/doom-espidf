deps_config := \
	/home/Jason/esp/esp-idf/components/app_trace/Kconfig \
	/home/Jason/esp/esp-idf/components/aws_iot/Kconfig \
	/home/Jason/esp/esp-idf/components/bt/Kconfig \
	/home/Jason/esp/esp-idf/components/driver/Kconfig \
	/home/Jason/esp/esp-idf/components/esp32/Kconfig \
	/home/Jason/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/Jason/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/Jason/esp/esp-idf/components/ethernet/Kconfig \
	/home/Jason/esp/esp-idf/components/fatfs/Kconfig \
	/home/Jason/esp/esp-idf/components/freertos/Kconfig \
	/home/Jason/esp/esp-idf/components/heap/Kconfig \
	/home/Jason/esp/esp-idf/components/http_server/Kconfig \
	/home/Jason/esp/esp-idf/components/libsodium/Kconfig \
	/home/Jason/esp/esp-idf/components/log/Kconfig \
	/home/Jason/esp/esp-idf/components/lwip/Kconfig \
	/home/Jason/esp/esp-idf/components/mbedtls/Kconfig \
	/home/Jason/esp/esp-idf/components/mdns/Kconfig \
	/home/Jason/esp/esp-idf/components/mqtt/Kconfig \
	/home/Jason/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/Jason/esp/esp-idf/components/openssl/Kconfig \
	/home/Jason/esp/esp-idf/components/pthread/Kconfig \
	/home/Jason/esp/esp-idf/components/spi_flash/Kconfig \
	/home/Jason/esp/esp-idf/components/spiffs/Kconfig \
	/home/Jason/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/Jason/esp/esp-idf/components/vfs/Kconfig \
	/home/Jason/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/Jason/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/Jason/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/Jason/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/Jason/esp/doom/components/prboom-esp32-compat/Kconfig.projbuild \
	/home/Jason/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
