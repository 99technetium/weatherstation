deps_config := \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/app_trace/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/aws_iot/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/bt/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/esp32/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/ethernet/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/fatfs/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/freertos/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/heap/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/libsodium/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/log/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/lwip/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/mbedtls/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/openssl/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/pthread/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/spi_flash/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/spiffs/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/tcpip_adapter/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/wear_levelling/Kconfig \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/bootloader/Kconfig.projbuild \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/esptool_py/Kconfig.projbuild \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/components/partition_table/Kconfig.projbuild \
	/media/marc/HOME/home/docs/studium/17HS/CAOS/weatherstation/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
