#ifndef SURFACE_BIDING_H
#define SURFACE_BIDING_H

#include <jerryscript.h>
#include <surfaces/gepard-xsurface.h>

void bindXSurface();
gepard::XSurface* getNativeXSurfacePtr(jerry_value_t object);

#endif // SURFACE_BIDING_H
