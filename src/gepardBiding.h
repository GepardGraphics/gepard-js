#ifndef GEPARD_BIDING_H
#define GEPARD_BIDING_H

#include <gepard.h>
#include <jerryscript.h>

void bindGepard();
gepard::Gepard* getNativeGepardPtr(jerry_value_t object);

#endif // GEPARD_BIDING_H
