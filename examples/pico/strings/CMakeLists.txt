add_executable(strings
    main.c
)

pico_add_extra_outputs(strings)

target_link_libraries(strings
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
