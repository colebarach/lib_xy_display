cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(project_base C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

include_directories(include)

add_library(xy
    src/xy_hardware.c
    src/xy_renderer.c
    src/xy_shapes.c
    src/xy_math.c
)

add_subdirectory(examples)

target_link_libraries(xy pico_stdlib pico_multicore)