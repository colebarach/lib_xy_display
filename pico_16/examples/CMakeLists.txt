# Misc ------------------------------------------------------------------------------------------------------------------------

add_executable(example_misc
    misc/main.c
)

pico_add_extra_outputs(example_misc)

target_link_libraries(example_misc
    xy
    pico_stdlib
    pico_multicore
)

# Pong ------------------------------------------------------------------------------------------------------------------------

add_executable(example_pong
    pong/main.c
)

pico_add_extra_outputs(example_pong)

target_link_libraries(example_pong
    xy
    pico_stdlib
    pico_multicore
)
