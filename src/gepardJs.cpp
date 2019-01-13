#include "jerryscript.h"
#include "gepard.h"
#include "surfaces/gepard-xsurface.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

static jerry_value_t createContext2D(const jerry_value_t func_value, const jerry_value_t this_val, const jerry_value_t *args_p, const jerry_length_t args_cnt)
{
    if (args_cnt > 0)
        std::cout << "heyho" << std::endl;
    return jerry_create_undefined ();
}

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
    std::cout << jsCode;
    jsFile.close();
    
    const jerry_char_t script[] = "createContext2D(600, 800)";
    jerry_init (JERRY_INIT_EMPTY);

    gepard::XSurface surface(600, 800);
    gepard::Gepard ctx(&surface);

    jerry_value_t func_obj = jerry_create_external_function (createContext2D);
    jerry_value_t prop_name = jerry_create_string((const jerry_char_t *) "createContext2D");
    
    jerry_value_t glob_obj_val = jerry_get_global_object();
    jerry_set_property(glob_obj_val, prop_name, func_obj);
    jerry_release_value(glob_obj_val);
    
    jerry_release_value(func_obj);
    jerry_release_value(prop_name);
    jerry_value_t eval_ret = jerry_eval((const jerry_char_t*)(jsCode.c_str()), jsCode.size(), JERRY_PARSE_NO_OPTS);

    /* Free JavaScript value, returned by eval */
    jerry_release_value (eval_ret);

    /* Cleanup engine */
    jerry_cleanup();

    while (!surface.hasToQuit()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));   // Only for CPU sparing.
    }

    return 0;
}
