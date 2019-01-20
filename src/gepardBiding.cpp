#include "gepardBiding.h"

#include "imageBiding.h"
#include "surfaceBiding.h"
#include "utils.h"
#include <jerryscript.h>
#include <jerryscript-ext/arg.h>
#include <gepard.h>
#include <iostream>
#include <surfaces/gepard-xsurface.h>
#include <string.h>
#include <vector>

static void native_gepard_freecb(void *native_p)
{
    std::cout << "gepard (" << native_p << ") is going to be freed!" << std::endl;
    gepard::Gepard* ctx = reinterpret_cast<gepard::Gepard*>(native_p);
    if (ctx)
        delete ctx;
    ctx = nullptr;
}

static const jerry_object_native_info_t native_gepard_type_info =
{
    native_gepard_freecb
};

jerry_value_t getDoubleArgs(const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt, gepard::Gepard** ctx, double* params, uint32_t paramsCnt, uint32_t requiredParams)
{
    *ctx = getNativeGepardPtr(this_val);
    if (!*ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    std::vector<jerryx_arg_t> mapping;
    // TODO: handle the Gepard pointer here
    mapping.push_back(jerryx_arg_ignore());

    // TODO: fix the terrible compiler warnings of the inline functions
    for (uint32_t i = 0; i < requiredParams; i++) {
        mapping.push_back(jerryx_arg_number(params + i, JERRYX_ARG_NO_COERCE, JERRYX_ARG_REQUIRED));
    }
    for (uint32_t i = requiredParams; i < paramsCnt; i++) {
        mapping.push_back(jerryx_arg_number(params + i, JERRYX_ARG_NO_COERCE, JERRYX_ARG_OPTIONAL));
    }

    return jerryx_arg_transform_this_and_args(this_val, args_p, args_cnt, mapping.data(), paramsCnt + 1);
}

jerry_value_t attributeSetterHelper(const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt, gepard::Gepard** ctx, std::string& attribute)
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

static jerry_value_t fillRect(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 4);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->fillRect(params[0], params[1], params[2], params[3]);
    return jerry_create_undefined();
}

static jerry_value_t setFillColor(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    // Alpha is optional
    params[3] = 1.0;
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 3);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->setFillColor(params[0], params[1], params[2], params[3]);
    return jerry_create_undefined();
}

static jerry_value_t setStrokeColor(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    // Alpha is optional
    params[3] = 1.0;
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 3);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->setStrokeColor(params[0], params[1], params[2], params[3]);
    return jerry_create_undefined();
}

static jerry_value_t getImageData(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 4);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    gepard::Image image = ctx->getImageData(params[0], params[1], params[2], params[3]);
    return createImageObject(image);
}

static jerry_value_t createImageData(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    gepard::Image image;
    if (args_cnt != 1) {
        double params[2];
        const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 2, 2);
        if (jerry_value_is_error(rv))
        {
            return rv;
        }
        image = ctx->createImageData(params[0], params[1]);
    } else {
        // TODO: this seems a bit messy
        gepard::Image* imagePtr = getNativeImagePtr(args_p[0]);
        const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, nullptr, 0, 0);
        if (jerry_value_is_error(rv))
        {
            return rv;
        }
        if (!imagePtr) {
            return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Image object!");
        }
        image = ctx->createImageData(*imagePtr);
    }
    return createImageObject(image);
}

static jerry_value_t drawImage(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    if (args_cnt == 0) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not enough arguments!");
    }
    gepard::Image* imagePtr = getNativeImagePtr(args_p[0]);
    if (!imagePtr) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Image object!");
    }
    double params[8];
    memset((void*)params, 0, 8 * sizeof(double));
    const jerry_value_t rv = getDoubleArgs(this_val, args_p + 1, args_cnt - 1, &ctx, params, 8, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    switch (args_cnt) {
    case 3:
        ctx->drawImage(*imagePtr, params[0], params[1]);
        break;
    case 5:
        ctx->drawImage(*imagePtr, params[0], params[1], params[2], params[3]);
        break;
    case 9:
        ctx->drawImage(*imagePtr, params[0], params[1], params[2], params[3],
                params[4], params[5], params[6], params[7]);
        break;
    default:
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Wrong number of arguments!");
        break;
    }
    return jerry_create_undefined();
}

static jerry_value_t putImageData(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    // TODO: This is almost the same as the drawImage, reduce the cloned lines!
    gepard::Gepard* ctx = nullptr;
    if (args_cnt == 0) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not enough arguments!");
    }
    gepard::Image* imagePtr = getNativeImagePtr(args_p[0]);
    if (!imagePtr) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Image object!");
    }
    double params[6];
    memset((void*)params, 0, 6 * sizeof(double));
    const jerry_value_t rv = getDoubleArgs(this_val, args_p + 1, args_cnt - 1, &ctx, params, 6, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    switch (args_cnt) {
    case 3:
        ctx->putImageData(*imagePtr, params[0], params[1]);
        break;
    case 9:
        ctx->putImageData(*imagePtr, params[0], params[1], params[2], params[3],
                params[4], params[5]);
        break;
    default:
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Wrong number of arguments!");
        break;
    }
    return jerry_create_undefined();
}

static jerry_value_t closePath(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->closePath();
    return jerry_create_undefined();
}

static jerry_value_t beginPath(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->beginPath();
    return jerry_create_undefined();
}

static jerry_value_t fill(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->fill();
    return jerry_create_undefined();
}

static jerry_value_t stroke(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->stroke();
    return jerry_create_undefined();
}

static jerry_value_t save(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->save();
    return jerry_create_undefined();
}

static jerry_value_t restore(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->restore();
    return jerry_create_undefined();
}

static jerry_value_t moveTo(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[2];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 2, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->moveTo(params[0], params[1]);
    return jerry_create_undefined();
}

static jerry_value_t lineTo(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[2];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 2, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->lineTo(params[0], params[1]);
    return jerry_create_undefined();
}

static jerry_value_t quadraticCurveTo(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 4);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->quadraticCurveTo(params[0], params[1], params[2], params[3]);
    return jerry_create_undefined();
}

static jerry_value_t bezierCurveTo(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[6];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 6, 6);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->bezierCurveTo(params[0], params[1], params[2], params[3], params[4], params[5]);
    return jerry_create_undefined();
}

static jerry_value_t arcTo(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[5];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 5, 5);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->arcTo(params[0], params[1], params[2], params[3], params[4]);
    return jerry_create_undefined();
}


static jerry_value_t rect(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[4];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 4, 4);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->rect(params[0], params[1], params[2], params[3]);
    return jerry_create_undefined();
}

static jerry_value_t arc(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[6];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 6, 6);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->arc(params[0], params[1], params[2], params[3], params[4], params[5]);
    return jerry_create_undefined();
}

static jerry_value_t fillStyleSetter(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx;
    std::string attribute;
    jerry_value_t retVal = attributeSetterHelper(this_val, args_p, args_cnt, &ctx, attribute);
    if (!jerry_value_is_error(retVal)) {
        ctx->fillStyle = attribute;
    }

    // What the heck I'm supposed to return
    // returning and object doesn't do anything
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
    return jerry_create_string((const jerry_char_t *)style.c_str()); //jerry_create_undefined();
}

static jerry_value_t createGepard(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    gepard::XSurface* surface = nullptr;
    if (args_cnt == 1)
        surface = getNativeXSurfacePtr(args_p[0]);

    if (!surface)
        return jerry_create_undefined();

    ctx = new gepard::Gepard(surface);

    jerry_value_t object = jerry_create_object();
    jerry_set_object_native_pointer(object, ctx, &native_gepard_type_info);

    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "Gepard_proto");
    jerry_value_t gpProto = jerry_get_property(glob_obj_val, prop_name);
    jerry_release_value(prop_name);
    jerry_release_value(glob_obj_val);

    if (!jerry_value_is_undefined(gpProto)) {
        jerry_value_t success = jerry_set_prototype(object, gpProto);
        jerry_release_value(success);
    }

    jerry_release_value(gpProto);

    return object;
}

static jerry_value_t scale(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[2];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 2, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->scale(params[0], params[1]);
    return jerry_create_undefined();
}

static jerry_value_t translate(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[2];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 2, 2);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->translate(params[0], params[1]);
    return jerry_create_undefined();
}

static jerry_value_t rotate(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params;
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, &params, 1, 1);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->rotate(params);
    return jerry_create_undefined();
}

static jerry_value_t transform(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[6];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 6, 6);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->transform(params[0], params[1], params[2], params[3], params[4], params[5]);
    return jerry_create_undefined();
}

static jerry_value_t setTransform(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = nullptr;
    double params[6];
    const jerry_value_t rv = getDoubleArgs(this_val, args_p, args_cnt, &ctx, params, 6, 6);
    if (jerry_value_is_error(rv))
    {
        return rv;
    }
    ctx->setTransform(params[0], params[1], params[2], params[3], params[4], params[5]);
    return jerry_create_undefined();
}

void registerPropertyDesctiptor(jerry_value_t object)
{
    jerry_property_descriptor_t propDesc;
    jerry_value_t function = jerry_create_external_function(fillStyleSetter);
    jerry_init_property_descriptor_fields(&propDesc);
    propDesc.setter = function;
    propDesc.is_set_defined = true;
    jerry_release_value(function);
    function = jerry_create_external_function(fillStyleGetter);
    propDesc.getter = function;
    propDesc.is_get_defined = true;
    jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) "fillStyle");
    jerry_value_t retval = jerry_define_own_property (object, prop_name, &propDesc);
    jerry_release_value(retval);
    jerry_release_value(function);
    jerry_release_value(prop_name);
    jerry_free_property_descriptor_fields(&propDesc);
}

void createGepardPrototype()
{
    jerry_value_t gpProto = jerry_create_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "Gepard_proto");

    registerNativeFunction(gpProto, fillRect, "fillRect");

    // Path functions
    registerNativeFunction(gpProto, closePath, "closePath");
    registerNativeFunction(gpProto, beginPath, "beginPath");
    registerNativeFunction(gpProto, fill, "fill");
    registerNativeFunction(gpProto, stroke, "stroke");
    registerNativeFunction(gpProto, moveTo, "moveTo");
    registerNativeFunction(gpProto, lineTo, "lineTo");
    registerNativeFunction(gpProto, quadraticCurveTo, "quadraticCurveTo");
    registerNativeFunction(gpProto, bezierCurveTo, "bezierCurveTo");
    registerNativeFunction(gpProto, arcTo, "arcTo");
    registerNativeFunction(gpProto, arc, "arc");
    registerNativeFunction(gpProto, rect, "rect");

    // State functions
    registerNativeFunction(gpProto, save, "save");
    registerNativeFunction(gpProto, restore, "restore");
    registerNativeFunction(gpProto, scale, "scale");
    registerNativeFunction(gpProto, rotate, "rotate");
    registerNativeFunction(gpProto, translate, "translate");
    registerNativeFunction(gpProto, transform, "transform");
    registerNativeFunction(gpProto, setTransform, "setTransform");
    registerNativeFunction(gpProto, setFillColor, "setFillColor");
    registerNativeFunction(gpProto, setStrokeColor, "setStrokeColor");

    // Image functions
    registerNativeFunction(gpProto, getImageData, "getImageData");
    registerNativeFunction(gpProto, createImageData, "createImageData");
    registerNativeFunction(gpProto, drawImage, "drawImage");
    registerNativeFunction(gpProto, putImageData, "putImageData");

    registerPropertyDesctiptor(gpProto);

    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_set_property(glob_obj_val, prop_name, gpProto);

    jerry_release_value(gpProto);
    jerry_release_value(prop_name);
    jerry_release_value(glob_obj_val);
}

void bindGepard()
{
    createGepardPrototype();
    jerry_value_t func_obj = jerry_create_external_function (createGepard);
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "Gepard");

    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_set_property(glob_obj_val, prop_name, func_obj);
    jerry_release_value(glob_obj_val);

    jerry_release_value(func_obj);
    jerry_release_value(prop_name);
}

gepard::Gepard *getNativeGepardPtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &type_p);
    if (hasNativePointer && type_p == &native_gepard_type_info)
        return reinterpret_cast<gepard::Gepard*>(nativePointer);
    return nullptr;
}
