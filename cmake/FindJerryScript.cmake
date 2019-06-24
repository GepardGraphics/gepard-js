# Copyright (C) 2019, Gepard Graphics
# Copyright (C) 2019, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
