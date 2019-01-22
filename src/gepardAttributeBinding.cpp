#include "gepardAttributeBinding.h"

#include "gepardBiding.h"
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

static jerry_value_t fillStyleSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

static jerry_value_t fillStyleGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->fillStyle;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

static jerry_value_t strokeStyleSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->strokeStyle = attribute;
    }
    return retVal;
}

static jerry_value_t strokeStyleGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->strokeStyle;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

static jerry_value_t lineCapSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineCap = attribute;
    }
    return retVal;
}

static jerry_value_t lineCapGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->lineCap;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

static jerry_value_t lineJoinSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeStringHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineJoin = attribute;
    }
    return retVal;
}

static jerry_value_t lineJoinGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::string style = ctx->lineJoin;
    return jerry_create_string((const jerry_char_t *)style.c_str());
}

static jerry_value_t lineWidthSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    double attribute;
    jerry_value_t retVal = attributeNumberHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->lineWidth = attribute;
    }
    return retVal;
}

static jerry_value_t lineWidthGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    return jerry_create_number(ctx->lineWidth);
}

static jerry_value_t miterLimitSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    double attribute;
    jerry_value_t retVal = attributeNumberHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->miterLimit = attribute;
    }
    return retVal;
}

static jerry_value_t miterLimitGetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    return jerry_create_number(ctx->miterLimit);
}


void registerPropertyDesctiptor(jerry_value_t object, jerry_external_handler_t setter, jerry_external_handler_t getter, std::string name)
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
    registerPropertyDesctiptor(object, fillStyleSetter, fillStyleGetter, "fillStyle");
    registerPropertyDesctiptor(object, strokeStyleSetter, strokeStyleGetter, "strokeStyle");
    registerPropertyDesctiptor(object, lineCapSetter, lineCapGetter, "lineCap");
    registerPropertyDesctiptor(object, lineJoinSetter, lineJoinGetter, "lineJoin");
    registerPropertyDesctiptor(object, lineWidthSetter, lineWidthGetter, "lineWidth");
    registerPropertyDesctiptor(object, miterLimitSetter, miterLimitGetter, "miterLimit");
}
