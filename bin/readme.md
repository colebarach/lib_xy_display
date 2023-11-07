# Library Binaries

This directory contains pre-compiled binaries of the library for the supported platforms. See the below sections for platform specific information.

## Raspberry Pi Pico

### Overview

`include` - Directory of library headers, copy of repository include directory

`libxy.a` - Static library, must be linked against

`libxy_import.cmake` - CMake include, optional

`libxy_pico.tar.gz` and `libxy_pico.zip` - Archives of the above files

### Usage

For more information about compiling and flashing software to the Pico, see Raspberry Pi's documentation (https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf). This guide will assume basic knowledge on this process.

For specific examples on using the library in a project, see the `examples/pico` directory in the root of this repository. There is an example of a standalone project using the library.

Process:

 - Extract the `libxy_pico` archive to your project folder (Use either the `.zip` or the `.tar.gz`, the contents are the same).
 - The previous step will have generated a `libxy` directory and a `libxy_import.cmake` file, these should be in the same directory as your `CMakeLists.txt` file.
 - In your `CMakeLists.txt` file, insert the line `include(libxy_import.cmake)` before declaring your executable.
 - At the end of your `CMakeLists.txt` file (at linkage), modify the `target_link_libraries` statement to be `target_link_libraries(<exec name> ${LIB_XY_LINK}  pico_stdlib pico_multicore)` where `<exec name>` is the name of the executable. Other necessary libraries may be added to this statement as well.
 - Compile the project using CMake.

Notes:

- The `libxy_import.cmake` file assumes the library to be located in the directory `libxy`. If it is desired to be moved, this file must be updated.