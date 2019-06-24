/* Copyright (C) 2019, Gepard Graphics
 * Copyright (C) 2019, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
