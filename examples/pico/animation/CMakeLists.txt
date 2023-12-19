add_executable(animation
    main.c
)

pico_add_extra_outputs(animation)

target_link_libraries(animation
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
