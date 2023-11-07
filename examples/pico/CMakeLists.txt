cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(lib_xy_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(../../include)

add_subdirectory(rendering_demos)
add_subdirectory(pong)
add_subdirectory(asteroids)