set(GPJS_SOURCES gepardJs.cpp)

add_executable(gepardJS ${GPJS_SOURCES})
target_link_libraries(gepardJS ${GPJS_LIB_DEPENDENCIES})
target_include_directories(gepardJS PRIVATE ${GPJS_INCLUDE_DEPENDENCIES})
