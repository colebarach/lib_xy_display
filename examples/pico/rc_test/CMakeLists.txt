add_executable(rc_test
    main.c
)

pico_add_extra_outputs(rc_test)

target_link_libraries(rc_test
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
