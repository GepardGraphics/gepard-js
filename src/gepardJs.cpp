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

    bindXSurface();
    bindGepard();
    bindImage();

    jerry_value_t eval_ret = jerry_eval((const jerry_char_t*)(jsCode.c_str()), jsCode.size(), JERRY_PARSE_NO_OPTS);

    /* Free JavaScript value, returned by eval */
    jerry_release_value(eval_ret);

    /* Cleanup engine */
    jerry_cleanup();

    return 0;
}
