#include "gepardBiding.h"

#include "surfaceBiding.h"
#include "utils.h"
#include <jerryscript.h>
#include <gepard.h>
#include <iostream>
#include <surfaces/gepard-xsurface.h>

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

static jerry_value_t fillRect(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    jerry_value_t retVal = jerry_create_undefined();
    if (!ctx || args_cnt != 4) {
        return retVal;
    }
    double x = jerry_get_number_value(args_p[0]);
    double y = jerry_get_number_value(args_p[1]);
    double w = jerry_get_number_value(args_p[2]);
    double h = jerry_get_number_value(args_p[3]);

    // TODO: Error checking
    ctx->fillRect(x, y, w, h);
    return retVal;
}

static jerry_value_t setFillColor(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    gepard::Gepard* ctx = getNativeGepardPtr(this_val);
    jerry_value_t retVal = jerry_create_undefined();
    if (!ctx || args_cnt < 3 || args_cnt > 4) {
        return retVal;
    }
    int r = (int)jerry_get_number_value(args_p[0]);
    int g = (int)jerry_get_number_value(args_p[1]);
    int b = (int)jerry_get_number_value(args_p[2]);
    float a = (args_cnt == 4) ? jerry_get_number_value(args_p[3]) : 1.0;

    // TODO: Error checking
    ctx->setFillColor(r, g, b, a);
    return retVal;
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

