#ifndef SURFACE_BIDING_H
#define SURFACE_BIDING_H

#include <jerryscript.h>
#include <surfaces/gepard-xsurface.h>
#include <surfaces/gepard-memory-buffer-surface.h>

jerry_value_t surfaceHasToQuitHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t createXSurfaceHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t createMemorySurfaceHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);

void bindSurface();
gepard::XSurface* getNativeXSurfacePtr(jerry_value_t object);
gepard::MemoryBufferSurface* getNativeMemorySurfacePtr(jerry_value_t object);
gepard::Surface* getNativeSurfacePtr(jerry_value_t object);

#endif // SURFACE_BIDING_H
