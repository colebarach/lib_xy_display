add_executable(long_text
    main.c
)

pico_add_extra_outputs(long_text)

target_link_libraries(long_text
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
