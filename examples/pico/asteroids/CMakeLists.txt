add_executable(asteroids
    main.c
)

pico_add_extra_outputs(asteroids)

target_link_libraries(asteroids
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
