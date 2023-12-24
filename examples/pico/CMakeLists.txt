cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(lib_xy_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(../../include)

add_subdirectory(hello_world)
add_subdirectory(ascii_table)
add_subdirectory(strings)
add_subdirectory(translation)
# add_subdirectory(animation)
add_subdirectory(crt_diagram)
add_subdirectory(procedural_models)
