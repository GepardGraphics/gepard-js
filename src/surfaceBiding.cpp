#include "surfaceBiding.h"

#include <jerryscript.h>
#include <surfaces/gepard-xsurface.h>
#include <iostream>

static void native_surface_freecb(void *native_p)
{
    std::cout << "surface (" << native_p << ") is going to be freed!" << std::endl;
    gepard::XSurface* surface = reinterpret_cast<gepard::XSurface*>(native_p);
    if (surface)
        delete surface;
    surface = nullptr;
}

static const jerry_object_native_info_t native_surface_type_info =
{
    .free_cb = native_surface_freecb
};

static jerry_value_t surfaceHasToQuit(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;

    bool result = true;
    bool hasNativePointer = jerry_get_object_native_pointer(this_val, &nativePointer, &type_p);
    if (hasNativePointer && type_p == &native_surface_type_info && nativePointer) {
        gepard::XSurface* surface = reinterpret_cast<gepard::XSurface*>(nativePointer);
        result = surface->hasToQuit();
    }
    //std::cout << "has to quit: " << result << std::endl;
    return jerry_create_boolean(result);
}

static jerry_value_t createXSurface(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
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
    jerry_set_object_native_pointer(object, surface, &native_surface_type_info);

    jerry_value_t j_width = jerry_create_number(width);
    jerry_value_t j_height = jerry_create_number(height);

    jerry_value_t prop_name = jerry_create_string ((const jerry_char_t *) "width");
    jerry_set_property(object, prop_name, j_width);
    jerry_release_value(prop_name);
    jerry_release_value(j_width);

    jerry_value_t func_obj = jerry_create_external_function(surfaceHasToQuit);
    prop_name = jerry_create_string((const jerry_char_t *) "hasToQuit");
    jerry_set_property(object, prop_name, func_obj);

    jerry_release_value(func_obj);
    jerry_release_value(prop_name);

    prop_name = jerry_create_string ((const jerry_char_t *) "height");
    jerry_set_property(object, prop_name, j_height);
    jerry_release_value(prop_name);
    jerry_release_value(j_height);

    return object;
}

void bindXSurface()
{
    jerry_value_t func_obj = jerry_create_external_function (createXSurface);
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "createXSurface");

    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_set_property(glob_obj_val, prop_name, func_obj);
    jerry_release_value(glob_obj_val);

    jerry_release_value(func_obj);
    jerry_release_value(prop_name);
}
