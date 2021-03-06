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

#include "gepardAttributeBinding.h"

#include "gepardBinding.h"
#include "utils.h"
#include <gepard.h>
#include <jerryscript.h>

jerry_value_t attributeStringHelper(const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt, gepard::Gepard** ctx, std::string& attribute)
{
    *ctx = getNativeGepardPtr(this_val);
    if (!*ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    if (args_cnt != 1 && !jerry_value_is_string(args_p[0])) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Wrong arguments!");
    }

    attribute = getStringFromObject(args_p[0]);
    return jerry_create_undefined();
}

jerry_value_t attributeNumberHelper(const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt, gepard::Gepard** ctx, double& attribute)
{
    *ctx = getNativeGepardPtr(this_val);
    if (!*ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    if (args_cnt != 1 && !jerry_value_is_number(args_p[0])) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Wrong arguments!");
    }

    attribute = jerry_get_number_value(args_p[0]);
    return jerry_create_undefined();
}

jerry_value_t fillStyleSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->fillStyle = attribute;
    }

    // What the heck am I supposed to return
    // returning an object doesn't do anything
    // defining the getter (see below) shadows the proper jerry_object setting
    return retVal;
}

jerry_value_t fillStyleGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->fillStyle;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

jerry_value_t strokeStyleSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->strokeStyle = attribute;
    }
    return retVal;
}

jerry_value_t strokeStyleGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->strokeStyle;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

jerry_value_t lineCapSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineCap = attribute;
    }
    return retVal;
}

jerry_value_t lineCapGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->lineCap;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

jerry_value_t lineJoinSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineJoin = attribute;
    }
    return retVal;
}

jerry_value_t lineJoinGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->lineJoin;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

jerry_value_t lineWidthSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    double attribute;
    jerry_value_t retVal = attributeNumberHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineWidth = attribute;
    }
    return retVal;
}

jerry_value_t lineWidthGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    return jerry_create_number(ctx->lineWidth);
}

jerry_value_t miterLimitSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    double attribute;
    jerry_value_t retVal = attributeNumberHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->miterLimit = attribute;
    }
    return retVal;
}

jerry_value_t miterLimitGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    return jerry_create_number(ctx->miterLimit);
}

void registerPropertyDescriptor(jerry_value_t object, jerry_external_handler_t setter, jerry_external_handler_t getter, std::string name)
{
    jerry_property_descriptor_t propDesc;
    jerry_init_property_descriptor_fields(&propDesc);
    propDesc.setter = jerry_create_external_function(setter);
    propDesc.is_set_defined = true;
    propDesc.getter = jerry_create_external_function(getter);
    propDesc.is_get_defined = true;
    jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) name.c_str());
    jerry_value_t retval = jerry_define_own_property (object, prop_name, &propDesc);
    jerry_release_value(retval);
    jerry_release_value(prop_name);
    jerry_free_property_descriptor_fields(&propDesc);
}

void bindGepardAttributes(jerry_value_t object)
{
    registerPropertyDescriptor(object, fillStyleSetterHandler, fillStyleGetterHandler, "fillStyle");
    registerPropertyDescriptor(object, strokeStyleSetterHandler, strokeStyleGetterHandler, "strokeStyle");
    registerPropertyDescriptor(object, lineCapSetterHandler, lineCapGetterHandler, "lineCap");
    registerPropertyDescriptor(object, lineJoinSetterHandler, lineJoinGetterHandler, "lineJoin");
    registerPropertyDescriptor(object, lineWidthSetterHandler, lineWidthGetterHandler, "lineWidth");
    registerPropertyDescriptor(object, miterLimitSetterHandler, miterLimitGetterHandler, "miterLimit");
}
