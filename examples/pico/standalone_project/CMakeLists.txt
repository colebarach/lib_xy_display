cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(lib_xy_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include(libxy_import.cmake)

add_executable(example_standalone
    src/main.c
)

pico_add_extra_outputs(example_standalone)

target_link_libraries(example_standalone
    ${LIB_XY_LINK}
    pico_stdlib
    pico_multicore
)
