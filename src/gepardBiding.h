#ifndef GEPARD_BIDING_H
#define GEPARD_BIDING_H

#include <gepard.h>
#include <jerryscript.h>

void bindGepard();
gepard::Gepard* getNativeGepardPtr(jerry_value_t object);
void registerNativeFunction(jerry_value_t object, jerry_external_handler_t nativeFunction, std::string name);

#endif // GEPARD_BIDING_H
