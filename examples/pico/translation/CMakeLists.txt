add_executable(translation
    main.c
)

pico_add_extra_outputs(translation)

target_link_libraries(translation
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
