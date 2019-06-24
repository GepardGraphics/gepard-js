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

cmake_minimum_required(VERSION 2.8.10)
project(gepard-js C CXX)

set(PROJECT_VERSION 0.0.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(Gepard)
find_package(JerryScript)
find_package(GLESv2)
find_package(EGL)
find_package(PNG)
find_package(X11)

set(EXTRA_FLAGS "-Wall -pedantic -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")

set(BINARY_OUTPUT_DIR ${PROJECT_BINARY_DIR}/bin)
set(LIB_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib)
set(INCLUDE_OUTPUT_DIR ${PROJECT_BINARY_DIR}/include)

file(MAKE_DIRECTORY ${BINARY_OUTPUT_DIR})
file(MAKE_DIRECTORY ${LIB_OUTPUT_DIR})
file(MAKE_DIRECTORY ${INCLUDE_OUTPUT_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})

set(GPJS_LIB_DEPENDENCIES ${GEPARD_LIBS} ${JERRYSCRIPT_LIBS} ${GLESv2_LIBRARY} ${EGL_LIBRARY} ${X11_LIBRARIES} ${PNG_LIBRARIES})
set(GPJS_INCLUDE_DEPENDENCIES ${JERRYSCRIPT_INCLUDE_DIR} ${GEPARD_INCLUDE_DIR})

add_subdirectory(src)
