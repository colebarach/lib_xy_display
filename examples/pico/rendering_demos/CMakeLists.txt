add_executable(rendering_demos
    main.c
)

pico_add_extra_outputs(rendering_demos)

target_link_libraries(rendering_demos
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
