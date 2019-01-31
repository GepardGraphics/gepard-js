#ifndef SURFACE_BIDING_H
#define SURFACE_BIDING_H

#include <jerryscript.h>
#include <surfaces/gepard-xsurface.h>

jerry_value_t surfaceHasToQuitHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t createXSurfaceHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);

void bindXSurface();
gepard::XSurface* getNativeXSurfacePtr(jerry_value_t object);

#endif // SURFACE_BIDING_H
