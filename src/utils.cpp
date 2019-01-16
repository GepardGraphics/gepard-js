#include "utils.h"

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
