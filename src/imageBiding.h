#ifndef IMAGE_BIDING_H
#define IMAGE_BIDING_H

#include <jerryscript.h>
#include <gepard-image.h>

void bindImage();
gepard::Image* getNativeImagePtr(jerry_value_t object);
jerry_value_t createImageObject(gepard::Image image);

#endif // SURFACE_BIDING_H
