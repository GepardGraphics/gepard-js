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

#include "gepardBinding.h"
#include "gepardImageBinding.h"
#include "gepardSurfaceBinding.h"

#include <jerryscript.h>
#include <jerryscript-ext/handler.h>
#include <gepard.h>
#include <surfaces/gepard-xsurface.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>


int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: gepardJS scriptToRun.js" << std::endl;
        return 1;
    }
    std::ifstream jsFile;
    jsFile.open(argv[1]);
    if (!jsFile.is_open()) {
        std::cerr << "Failed to open the js file!" << std::endl;
        return 1;
    }
    
    std::string jsCode { std::istreambuf_iterator<char>(jsFile), std::istreambuf_iterator<char>() };
    std::cout << "Code:" << std::endl << jsCode << std::endl << "\\EOF" << std::endl;
    jsFile.close();

    jerry_init (JERRY_INIT_EMPTY);

    jerryx_handler_register_global((const jerry_char_t *) "print", jerryx_handler_print);

    bindSurface();
    bindGepard();
    bindImage();

    jerry_value_t eval_ret = jerry_eval((const jerry_char_t*)(jsCode.c_str()), jsCode.size(), JERRY_PARSE_NO_OPTS);

    /* Free JavaScript value, returned by eval */
    jerry_release_value(eval_ret);

    /* Cleanup engine */
    jerry_cleanup();

    return 0;
}
