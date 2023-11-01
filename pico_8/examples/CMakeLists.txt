add_executable(example_pong
    pong/main.c
    ../src/xy_hardware.c
    ../src/xy_renderer.c
    ../src/xy_shapes.c
    ../src/xy_math.c
)
pico_add_extra_outputs(example_pong)
target_link_libraries(example_pong pico_stdlib pico_multicore)