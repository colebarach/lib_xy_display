add_executable(ascii_table
    main.c
)

pico_add_extra_outputs(ascii_table)

target_link_libraries(ascii_table
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
