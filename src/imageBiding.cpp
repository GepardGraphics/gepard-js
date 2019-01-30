#include "imageBiding.h"

#include "utils.h"
#include <iostream>

static void native_image_freecb(void *native_p)
{
    std::cout << "image (" << native_p << ") is going to be freed!" << std::endl;
    gepard::Image* ctx = reinterpret_cast<gepard::Image*>(native_p);
    if (ctx)
        delete ctx;
    ctx = nullptr;
}

static void native_image_data_freecb(void *native_p)
{
    // Nothing else to do, the image's back buffer is going to be freed with the native image
    native_p = nullptr;
}

static const jerry_object_native_info_t native_image_type_info =
{
    native_image_freecb
};

static jerry_value_t loadPng(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    if (args_cnt != 1 && !jerry_value_is_string(args_p[0])) {
        return jerry_create_undefined();
    }
    std::string fileName = getStringFromObject(args_p[0]);
    gepard::Image image = gepard::utils::loadPng(fileName);
    std::cout << fileName << std::endl;
    return createImageObject(image);
}

static jerry_value_t savePng(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    if (args_cnt != 2 && !jerry_value_is_string(args_p[1])) {
        return jerry_create_undefined();
    }
    std::string fileName = getStringFromObject(args_p[1]);
    gepard::Image* image = getNativeImagePtr(args_p[0]);
    bool success = false;
    if (image)
        success = gepard::utils::savePng(*image, fileName);
    return jerry_create_boolean(success);
}

jerry_value_t createImageObject(gepard::Image image)
{
    // TODO: add copy constructor to gepard::Image
    gepard::Image* imagePtr = new gepard::Image(image.width(), image.height(), image.data());
    std::cout << "createImageObject: " << image.width() << " " << image.height() << std::endl;

    jerry_value_t object = jerry_create_object();
    jerry_value_t j_width = jerry_create_number(imagePtr->width());
    jerry_value_t j_height = jerry_create_number(imagePtr->height());
    registerProperty(object, j_width, "width");
    registerProperty(object, j_height, "height");
    jerry_release_value(j_width);
    jerry_release_value(j_height);
    jerry_set_object_native_pointer(object, imagePtr, &native_image_type_info);
    // The const cast isn't nice, add access to the image data in the gepard
    jerry_value_t typeArray = jerry_create_arraybuffer_external(imagePtr->data().size() * sizeof(uint32_t),
        reinterpret_cast<uint8_t*>(const_cast<uint32_t*>(imagePtr->data().data())), native_image_data_freecb);

    registerProperty(object, typeArray, "data");
    jerry_release_value(typeArray);

    return object;
}

void bindImage()
{
    jerry_value_t glob_obj_val = jerry_get_global_object();
    registerNativeFunction(glob_obj_val, loadPng, "loadPng");
    registerNativeFunction(glob_obj_val, savePng, "savePng");

    jerry_release_value(glob_obj_val);
}

gepard::Image *getNativeImagePtr(jerry_value_t object)
{
    void* nativePointer = nullptr;
    const jerry_object_native_info_t *type_p = nullptr;
    bool hasNativePointer = jerry_get_object_native_pointer(object, &nativePointer, &type_p);
    if (hasNativePointer && type_p == &native_image_type_info)
        return reinterpret_cast<gepard::Image*>(nativePointer);
    return nullptr;
}
