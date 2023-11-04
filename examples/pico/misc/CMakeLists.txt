add_executable(misc
    main.c
)

pico_add_extra_outputs(misc)

target_link_libraries(misc
    ${CMAKE_SOURCE_DIR}/../../../bin/pico/libxy.a
    pico_stdlib
    pico_multicore
)