# This module is written for the installed version of the jerryscript

find_path(JERRYSCRIPT_INCLUDE_DIR "jerryscript-core.h"
            PATHS JERRYSCRIPT_INSTALL_DIR "${JERRYSCRIPT_INSTALL_DIR}/include")
find_path(JERRYSCRIPT_LIBRARY_DIR "libjerry-core.a"
            PATHS JERRYSCRIPT_INSTALL_DIR "${JERRYSCRIPT_INSTALL_DIR}/lib")

            
list(APPEND JERRYSCRIPT_LIB_LIST "libjerry-core.a"  "libjerry-ext.a"  "libjerry-libm.a"  "libjerry-port-default.a")
foreach(jerry_lib ${JERRYSCRIPT_LIB_LIST})
    list(APPEND JERRYSCRIPT_LIBS "${JERRYSCRIPT_LIBRARY_DIR}/${jerry_lib}")
endforeach(jerry_lib)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JerryScript REQUIRED_VARS JERRYSCRIPT_INCLUDE_DIR JERRYSCRIPT_LIBRARY_DIR JERRYSCRIPT_LIBS)
