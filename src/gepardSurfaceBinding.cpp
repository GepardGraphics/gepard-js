/* Copyright (C) 2019, Gepard Graphics
 * Copyright (C) 2019, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gepardSurfaceBinding.h"

#include "utils.h"
#include <jerryscript.h>
#include <surfaces/gepard-xsurface.h>
#include <surfaces/gepard-memory-buffer-surface.h>
#include <iostream>

static void native_x_surface_freecb(void *native_p)
{
    std::cout << "X surface (" << native_p << ") is going to be freed!" << std::endl;
    gepard::XSurface* surface = reinterpret_cast<gepard::XSurface*>(native_p);
    if (surface)
        delete surface;
    surface = nullptr;
}

static const jerry_object_native_info_t native_x_surface_type_info =
{
    native_x_surface_freecb
};

static void native_memory_surface_freecb(void *native_p)
{
    std::cout << "Memory surface (" << native_p << ") is going to be freed!" << std::endl;
    gepard::MemoryBufferSurface* surface = reinterpret_cast<gepard::MemoryBufferSurface*>(native_p);
    if (surface)
        delete surface;
    surface = nullptr;
}

static const jerry_object_native_info_t native_memory_surface_type_info =
{
    native_memory_surface_freecb
};

jerry_value_t surfaceHasToQuitHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    bool result = true;
    gepard::XSurface* surface = getNativeXSurfacePtr(this_val);
    if (surface) {
        result = surface->hasToQuit();
    }
    return jerry_create_boolean(result);
}

jerry_value_t createXSurfaceHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::XSurface* surface = nullptr;
    double width = 600;
    double height = 600;
    if (args_cnt == 2) {
        width = (int)jerry_get_number_value(args_p[0]);
        height = (int)jerry_get_number_value(args_p[1]);
    }
    std::cout << "width, height: " << width << " " << height << std::endl;
    surface = new gepard::XSurface(width, height);
    jerry_value_t object = jerry_create_object();
    jerry_set_object_native_pointer(object, surface, &native_x_surface_type_info);

    jerry_value_t j_width = jerry_create_number(width);
    jerry_value_t j_height = jerry_create_number(height);
    registerProperty(object, j_width, "width");
    registerProperty(object, j_height, "height");
    jerry_release_value(j_width);
    jerry_release_value(j_height);

    registerNativeFunction(object, surfaceHasToQuitHandler, "hasToQuit");

    return object;
}

jerry_value_t createMemorySurfaceHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::MemoryBufferSurface* surface = nullptr;
    double width = 600;
    double height = 600;
    if (args_cnt == 2) {
        width = (int)jerry_get_number_value(args_p[0]);
        height = (int)jerry_get_number_value(args_p[1]);
    }
    std::cout << "width, height: " << width << " " << height << std::endl;
    surface = new gepard::MemoryBufferSurface(width, height);
    jerry_value_t object = jerry_create_object();
    jerry_set_object_native_pointer(object, surface, &native_memory_surface_type_info);

    jerry_value_t j_width = jerry_create_number(width);
    jerry_value_t j_height = jerry_create_number(height);
    registerProperty(object, j_width, "width");
    registerProperty(object, j_height, "height");
    jerry_release_value(j_width);
    jerry_release_value(j_height);

    return object;
}

void bindSurface()
{
    jerry_value_t glob_obj_val = jerry_get_global_object();
    registerNativeFunction(glob_obj_val, createXSurfaceHandler, "createXSurface");
    registerNativeFunction(glob_obj_val, createMemorySurfaceHandler, "createMemorySurface");
    jerry_release_value(glob_obj_val);
}

gepard::XSurface* getNativeXSurfacePtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &type_p);
    if (hasNativePointer && type_p == &native_x_surface_type_info)
        return reinterpret_cast<gepard::XSurface*>(nativePointer);
    return nullptr;
}

gepard::MemoryBufferSurface* getNativeMemorySurfacePtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &type_p);
    if (hasNativePointer && type_p == &native_memory_surface_type_info)
        return reinterpret_cast<gepard::MemoryBufferSurface*>(nativePointer);
    return nullptr;
}

gepard::Surface* getNativeSurfacePtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &type_p);
    if (hasNativePointer && (type_p == &native_x_surface_type_info || type_p == &native_memory_surface_type_info))
        return reinterpret_cast<gepard::Surface*>(nativePointer);
    return nullptr;
}
