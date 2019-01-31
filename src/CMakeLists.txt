set(GPJS_SOURCES
    gepardSurfaceBinding.cpp
    gepardBinding.cpp
    gepardAttributeBinding.cpp
    gepardImageBinding.cpp
    utils.cpp
)

set(GPJS_APP_SOURCES
    gepardJs.cpp
)

set(GEPARD_JS_HEADERS
    gepardSurfaceBinding.h
    gepardBinding.h
    gepardAttributeBinding.h
    gepardImageBinding.h
)

add_library(gepardJS SHARED ${GPJS_SOURCES})
target_link_libraries(gepardJS ${GPJS_LIB_DEPENDENCIES})
target_include_directories(gepardJS PRIVATE ${GPJS_INCLUDE_DEPENDENCIES})

add_executable(gepardJsApp ${GPJS_APP_SOURCES})
target_link_libraries(gepardJsApp gepardJS ${GPJS_LIB_DEPENDENCIES})
target_include_directories(gepardJsApp PRIVATE ${GPJS_INCLUDE_DEPENDENCIES})

file(COPY ${GEPARD_JS_HEADERS} DESTINATION ${INCLUDE_OUTPUT_DIR})

set_target_properties(gepardJS
                      PROPERTIES
                      FRAMEWORK ON
                      VERSION ${PROJECT_VERSION}
                      PUBLIC_HEADER "${GEPARD_JS_HEADERS}"
)

install(TARGETS gepardJS
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
