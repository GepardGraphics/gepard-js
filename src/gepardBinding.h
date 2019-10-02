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

#ifndef GEPARD_BIDING_H
#define GEPARD_BIDING_H

#include <gepard.h>
#include <jerryscript.h>


jerry_value_t fillRectHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t setFillColorHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t setStrokeColorHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t getImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t createImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t drawImageHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t putImageDataHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t closePathHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t beginPathHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t fillHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t strokeHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t saveHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t restoreHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t moveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t lineToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t quadraticCurveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t bezierCurveToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t arcToHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t rectHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t arcHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t createGepardHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t scaleHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t translateHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t rotateHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t transformHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t setTransformHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);

#if USE_GEPARD_EXPERIMENTAL
jerry_value_t expFinishHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t expSetPresentModeOnDemandHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
jerry_value_t expSetPresentModeImmediateHandler(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt);
#endif // USE_GEPARD_EXPERIMENTAL

void bindGepard();
gepard::Gepard* getNativeGepardPtr(jerry_value_t object);

#endif // GEPARD_BIDING_H
