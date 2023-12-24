add_executable(procedural_models
    main.c
)

pico_add_extra_outputs(procedural_models)

target_link_libraries(procedural_models
    ${CMAKE_SOURCE_DIR}/../../bin/pico/libxy/libxy.a
    pico_stdlib
    pico_multicore
)
