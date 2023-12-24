add_executable(crt_diagram
    main.c
)

pico_add_extra_outputs(crt_diagram)

target_link_libraries(crt_diagram
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
