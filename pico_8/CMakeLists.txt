cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(project_base C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

include_directories(include)

add_executable(main
    src/main.c
    src/xy_hardware.c
    src/xy_renderer.c
    src/xy_shapes.c
)

pico_add_extra_outputs(main)

target_link_libraries(main pico_stdlib pico_multicore pico_rand)
