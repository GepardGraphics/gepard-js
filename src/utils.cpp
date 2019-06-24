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

#include "utils.h"

#include <assert.h>

void registerNativeFunction(jerry_value_t object, jerry_external_handler_t nativeFunction, std::string name)
{
    jerry_value_t func_obj = jerry_create_external_function(nativeFunction);
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) name.c_str());
    jerry_set_property(object, prop_name, func_obj);
    jerry_release_value(func_obj);
    jerry_release_value(prop_name);
}

void registerProperty(jerry_value_t object, jerry_value_t prop, std::string name)
{
    jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) name.c_str());
    jerry_set_property(object, prop_name, prop);
    jerry_release_value(prop_name);
}

std::string getStringFromObject(jerry_value_t object)
{
    // TODO: support utf8
    assert(jerry_value_is_string(object));
    uint32_t length = jerry_get_string_length(object);
    char* buffer = (char*)malloc(length + 1);
    uint32_t copiedLength = jerry_string_to_char_buffer(object, (jerry_char_t*)buffer, length);
    buffer[length] = '\0';
    return buffer;
}
