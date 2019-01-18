#ifndef GPJS_UTILS_H
#define GPJS_UTILS_H

#include <jerryscript.h>
#include <string>

void registerNativeFunction(jerry_value_t object, jerry_external_handler_t nativeFunction, std::string name);
void registerProperty(jerry_value_t object, jerry_value_t prop, std::string name);
std::string getStringFromObject(jerry_value_t object);

#endif // GPJS_UTILS_H
