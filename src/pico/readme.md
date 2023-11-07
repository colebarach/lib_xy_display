# Source for the Raspberry Pi Pico

## Dependencies

This library is dependent on the Raspberry Pi Pico C SDK. When linking against this library, it is also necessay to link against the `pico_stdlib` and `pico_multicore` libraries.

## Project Compilation and Linkage

For compiling a standalone project using the library, see the `bin/readme.md` file.

## Library Compilation

Note that pre-compiled versions of the library are available in the `bin` directory. If compiling the library is necessary, follow the below steps.

Process:

- Create the following path in the root of the repository `build/pico`.
- Open a command line with the working directory set to this directory.
- Run `cmake ../../src/pico/` to generate the build files using the pico CMakeLists
- Run `cmake --build .` to compile the library.
- After compilation, a file named `libxy.a` will have been created.

Note for completeness sake, the `bin` directory should be updated, but it is not necessary. To do so:

- Copy the `libxy.a` file into the `bin/pico/libxy` directory, overwriting the old version.
- If the headers have been modified, remove the `/bin/pico/libxy/include` directory and copy the root `include` directory in its place.
- Compress the `/bin/pico/libxy` directory and the `libxy_import.cmake` file into `/bin/libxy.tar.gz`.
- Do the same for the `libxy.zip` file as well.
