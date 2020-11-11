Gepard-JS
====

The Gepard-JS is a JavaScript binding of the [Gepard](https://github.com/GepardGraphics/gepard) library
on top of the [JerryScript](https://github.com/jerryscript-project/jerryscript) engine.

## Requirements

The Gepard-JS requires the Gepard library and the JerryScript library.

## Build the code

The `GEPARD_INSTALL_DIR` and `JERRYSCRIPT_INSTALL_DIR` need to be set to their corresponding directories.
Example commands are shown below.

```
cmake -Bbuild -H. -DGEPARD_INSTALL_DIR=modules/gepard/build/ -DJERRYSCRIPT_INSTALL_DIR=modules/jerryscript/install/
make -C build
```

## Run the gepardJSApp

The `gepardJSApp` is a simple executable which runs the JavaScript file passed as an argument.

```
build/bin/gepardJSApp examples/fill-rect.js
```
