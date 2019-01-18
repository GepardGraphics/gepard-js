#include "gepardBiding.h"

#include "imageBiding.h"
#include "surfaceBiding.h"
#include "utils.h"
#include <jerryscript.h>
#include <jerryscript-ext/arg.h>
#include <gepard.h>
#include <iostream>
#include <surfaces/gepard-xsurface.h>
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

static jerry_value_t getImageData(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    if (!ctx || args_cnt != 4) {
        return jerry_create_undefined();
    }
    double x = jerry_get_number_value(args_p[0]);
    double y = jerry_get_number_value(args_p[1]);
    double w = jerry_get_number_value(args_p[2]);
    double h = jerry_get_number_value(args_p[3]);

    // TODO: Error checking
    gepard::Image image = ctx->getImageData(x, y, w, h);
    return createImageObject(image);
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

void createGepardPrototype()
{
    jerry_value_t gpProto = jerry_create_object();
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "Gepard_proto");

    registerNativeFunction(gpProto, fillRect, "fillRect");
    registerNativeFunction(gpProto, setFillColor, "setFillColor");
    registerNativeFunction(gpProto, getImageData, "getImageData");

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

