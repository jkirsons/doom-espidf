

idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "." "${CMAKE_CURRENT_BINARY_DIR}" include
                    PRIV_REQUIRES spi_flash fatfs prboom prboom-wad-tables)

