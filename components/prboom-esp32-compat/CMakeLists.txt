

idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "." "${CMAKE_CURRENT_BINARY_DIR}" include
                    PRIV_REQUIRES spi_flash fatfs prboom prboom-wad-tables)

# TODO: switch to c11
# target_compile_options(${COMPONENT_LIB} PRIVATE "-std=gnu11")

