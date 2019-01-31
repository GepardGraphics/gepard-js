#ifndef IMAGE_BIDING_H
#define IMAGE_BIDING_H

#include <jerryscript.h>
#include <gepard-image.h>

jerry_value_t loadPngHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t savePngHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);

void bindImage();
gepard::Image* getNativeImagePtr(jerry_value_t object);
jerry_value_t createImageObject(gepard::Image image);

#endif // SURFACE_BIDING_H
