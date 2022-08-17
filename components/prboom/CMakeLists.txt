

idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "." "${CMAKE_CURRENT_BINARY_DIR}" "../prboom-wad-tables/include")

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=char-subscripts -Wno-error=unused-value -Wno-error=parentheses -Wno-error=int-to-pointer-cast -Wno-pointer-sign -Wno-error=unused-but-set-parameter -Wno-error=maybe-uninitialized -Wno-error=unused-const-variable -Wno-error=misleading-indentation -Wno-error=nonnull -Wno-error=dangling-else -Wno-error=format-overflow -Wno-error=duplicate-decl-specifier -Wno-error=sizeof-pointer-div -Wno-error=char-subscripts -Wno-error=unused-value -Wno-error=parentheses -Wno-error=int-to-pointer-cast -Wno-pointer-sign -Wno-unused-but-set-variable -Wno-maybe-uninitialized)

