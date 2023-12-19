add_executable(hello_world
    main.c
)

pico_add_extra_outputs(hello_world)

target_link_libraries(hello_world
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
