add_executable(pong
    main.c
)

pico_add_extra_outputs(pong)

target_link_libraries(pong
    ${CMAKE_SOURCE_DIR}/../../../bin/pico/libxy.a
    pico_stdlib
    pico_multicore
)