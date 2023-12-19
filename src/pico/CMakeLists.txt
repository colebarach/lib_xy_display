cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(lib_xy_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(../../include)

add_library(xy
    xy_hardware.c
    xy_renderer.c
    xy_shapes.c
    xy_math.c
)

target_link_libraries(xy
    pico_stdlib
    hardware_pwm
    pico_multicore
)
