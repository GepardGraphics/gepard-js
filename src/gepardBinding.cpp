#include "gepardBinding.h"

#include "gepardAttributeBinding.h"
#include "gepardImageBinding.h"
#include "gepardSurfaceBinding.h"
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

jerry_value_t fillRectHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t setFillColorHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t setStrokeColorHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t getImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t createImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t drawImageHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t putImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t closePathHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->closePath();
    return jerry_create_undefined();
}

jerry_value_t beginPathHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->beginPath();
    return jerry_create_undefined();
}

jerry_value_t fillHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->fill();
    return jerry_create_undefined();
}

jerry_value_t strokeHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->stroke();
    return jerry_create_undefined();
}

jerry_value_t saveHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->save();
    return jerry_create_undefined();
}

jerry_value_t restoreHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx) {
        return jerry_create_error(JERRY_ERROR_COMMON, (const jerry_char_t*)"Not a native Gepard object!");
    }
    ctx->restore();
    return jerry_create_undefined();
}

jerry_value_t moveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t lineToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t quadraticCurveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t bezierCurveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t arcToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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


jerry_value_t rectHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t arcHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t createGepardHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t scaleHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t translateHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t rotateHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t transformHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

jerry_value_t setTransformHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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

void createGepardPrototype()
{
    jerry_value_t gpProto = jerry_create_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "Gepard_proto");

    registerNativeFunction(gpProto, fillRectHandler, "fillRect");

    // Path functions
    registerNativeFunction(gpProto, closePathHandler, "closePath");
    registerNativeFunction(gpProto, beginPathHandler, "beginPath");
    registerNativeFunction(gpProto, fillHandler, "fill");
    registerNativeFunction(gpProto, strokeHandler, "stroke");
    registerNativeFunction(gpProto, moveToHandler, "moveTo");
    registerNativeFunction(gpProto, lineToHandler, "lineTo");
    registerNativeFunction(gpProto, quadraticCurveToHandler, "quadraticCurveTo");
    registerNativeFunction(gpProto, bezierCurveToHandler, "bezierCurveTo");
    registerNativeFunction(gpProto, arcToHandler, "arcTo");
    registerNativeFunction(gpProto, arcHandler, "arc");
    registerNativeFunction(gpProto, rectHandler, "rect");

    // State functions
    registerNativeFunction(gpProto, saveHandler, "save");
    registerNativeFunction(gpProto, restoreHandler, "restore");
    registerNativeFunction(gpProto, scaleHandler, "scale");
    registerNativeFunction(gpProto, rotateHandler, "rotate");
    registerNativeFunction(gpProto, translateHandler, "translate");
    registerNativeFunction(gpProto, transformHandler, "transform");
    registerNativeFunction(gpProto, setTransformHandler, "setTransform");
    registerNativeFunction(gpProto, setFillColorHandler, "setFillColor");
    registerNativeFunction(gpProto, setStrokeColorHandler, "setStrokeColor");

    // Image functions
    registerNativeFunction(gpProto, getImageDataHandler, "getImageData");
    registerNativeFunction(gpProto, createImageDataHandler, "createImageData");
    registerNativeFunction(gpProto, drawImageHandler, "drawImage");
    registerNativeFunction(gpProto, putImageDataHandler, "putImageData");

    bindGepardAttributes(gpProto);

    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_set_property(glob_obj_val, prop_name, gpProto);

    jerry_release_value(gpProto);
    jerry_release_value(prop_name);
    jerry_release_value(glob_obj_val);
}

void bindGepard()
{
    createGepardPrototype();
    jerry_value_t func_obj = jerry_create_external_function (createGepardHandler);
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
