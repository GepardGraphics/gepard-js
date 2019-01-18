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
    char* fileName = (char*)malloc(length + 1);
    uint32_t copiedLength = jerry_string_to_char_buffer(object, (jerry_char_t*)fileName, length);
    fileName[length] = '\0';
    return fileName;
}
