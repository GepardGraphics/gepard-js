#ifndef GEPARD_ATTRIBUTE_BINDING_H
#define GEPARD_ATTRIBUTE_BINDING_H

#include <jerryscript.h>

jerry_value_t fillStyleSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t fillStyleGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t strokeStyleSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t strokeStyleGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineCapSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineCapGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineJoinSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineJoinGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineWidthSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineWidthGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t miterLimitSetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t miterLimitGetterHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);

void bindGepardAttributes(jerry_value_t object);

#endif // GEPARD_ATTRIBUTE_BINDING_H
