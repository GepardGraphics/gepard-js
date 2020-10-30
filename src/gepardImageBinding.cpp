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

#include "gepardImageBinding.h"

#include "utils.h"
#include <iostream>

static void native_image_freecb(void *native_p)
{
    std::cout << "image (" << native_p << ") is going to be freed!" << std::endl;
    gepard::Image* ctx = reinterpret_cast<gepard::Image*>(native_p);
    if (ctx)
        delete ctx;
    ctx = nullptr;
}

static void native_image_data_freecb(void *native_p)
{
    // Nothing else to do, the image's back buffer is going to be freed with the native image
    native_p = nullptr;
}

static const jerry_object_native_info_t native_image_type_info =
{
    native_image_freecb
};

jerry_value_t loadPngHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    if (args_cnt != 1 && !jerry_value_is_string(args_p[0])) {
        return jerry_create_undefined();
    }
    std::string fileName = getStringFromObject(args_p[0]);
    gepard::Image image = gepard::utils::loadPng(fileName);
    std::cout << fileName << std::endl;
    return createImageObject(image);
}

jerry_value_t savePngHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    if (args_cnt != 2 && !jerry_value_is_string(args_p[1])) {
        return jerry_create_undefined();
    }
    std::string fileName = getStringFromObject(args_p[1]);
    gepard::Image* image = getNativeImagePtr(args_p[0]);
    bool success = false;
    if (image)
        success = gepard::utils::savePng(*image, fileName);
    return jerry_create_boolean(success);
}

jerry_value_t createImageObject(gepard::Image image)
{
    // TODO: add copy constructor to gepard::Image
    gepard::Image* imagePtr = new gepard::Image(image.width(), image.height(), image.data());
    std::cout << "createImageObject: " << image.width() << " " << image.height() << std::endl;

    jerry_value_t object = jerry_create_object();
    jerry_value_t j_width = jerry_create_number(imagePtr->width());
    jerry_value_t j_height = jerry_create_number(imagePtr->height());
    registerProperty(object, j_width, "width");
    registerProperty(object, j_height, "height");
    jerry_release_value(j_width);
    jerry_release_value(j_height);
    jerry_set_object_native_pointer(object, imagePtr, &native_image_type_info);
    // The const cast isn't nice, add access to the image data in the gepard
    jerry_value_t typeArray = jerry_create_arraybuffer_external(imagePtr->data().size() * sizeof(uint32_t),
        reinterpret_cast<uint8_t*>(const_cast<uint32_t*>(imagePtr->data().data())), native_image_data_freecb);

    registerProperty(object, typeArray, "data");
    jerry_release_value(typeArray);

    return object;
}

void bindImage()
{
    jerry_value_t glob_obj_val = jerry_get_global_object();
    registerNativeFunction(glob_obj_val, loadPngHandler, "loadPng");
    registerNativeFunction(glob_obj_val, savePngHandler, "savePng");

    jerry_release_value(glob_obj_val);
}

gepard::Image *getNativeImagePtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &native_image_type_info);
    if (hasNativePointer)
        return reinterpret_cast<gepard::Image*>(nativePointer);
    return nullptr;
}
