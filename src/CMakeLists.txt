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

add_library(gepardJS SHARED ${GPJS_SOURCES})
target_link_libraries(gepardJS ${GPJS_LIB_DEPENDENCIES})
target_include_directories(gepardJS PRIVATE ${GPJS_INCLUDE_DEPENDENCIES})

add_executable(gepardJsApp ${GPJS_APP_SOURCES})
target_link_libraries(gepardJsApp gepardJS ${GPJS_LIB_DEPENDENCIES})
target_include_directories(gepardJsApp PRIVATE ${GPJS_INCLUDE_DEPENDENCIES})
