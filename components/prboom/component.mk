#
# Component Makefile
#
# This Makefile should, at the very least, just include $(SDK_PATH)/make/component.mk. By default, 
# this will take the sources in the src/ directory, compile them and link them into 
# lib(subdirectory_name).a in the build directory. This behaviour is entirely configurable,
# please read the SDK documents if you need to do this.
#

#include $(IDF_PATH)/make/component_common.mk




CFLAGS += -Wno-error=char-subscripts -Wno-error=unused-value -Wno-error=parentheses -Wno-error=int-to-pointer-cast -Wno-pointer-sign \
		-Wno-error=unused-but-set-parameter -Wno-error=maybe-uninitialized -Wno-error=unused-const-variable -Wno-error=misleading-indentation \
		-Wno-error=nonnull -Wno-error=dangling-else -Wno-error=format-overflow -Wno-error=duplicate-decl-specifier -Wno-error=sizeof-pointer-div