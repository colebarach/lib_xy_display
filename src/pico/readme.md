# Library Implementation for the Raspberry Pi Pico

This is the source code for an implementation of the xy_display library on a Raspberry Pi Pico microcontroller. The hardware descriptions are listed below, but the source may be adjusted to fit a different configuration.

## Usage

See the repository 'readme' file for information about using the library.

### Library Dependencies

This library is dependent on the Raspberry Pi Pico C SDK. When linking against this library, it is also necessay to link against the `pico_stdlib` and `pico_multicore` libraries. Details on this are provided in the project compilation section.

### Project Compilation and Linkage

For more information about compiling and flashing software to the Pico, see Raspberry Pi's documentation (https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf). This guide will assume basic knowledge on this process.

CMake is used to generate the project toolchain. Refer to the `examples/pico` directory for examples on using this library in a project, multiple CMakeLists.txt files are present for reference.

Requirements:

- CMake
- GNU ARM toolchain for embedded systems
- Raspberry Pi Pico C SDK

If you are already able to develop and compile C programs for the Raspberry Pi Pico, these requirements are satisfied.

Process:

 - Locate the static library file for the pico implementation (`libxy.a`), a pre-compiled version is located in `bin/pico/`.
 - Copy the absolute path to this file, it may be copied elsewhere for convienence (ex. `<your project directory>/lib/libxy.a`).
 - Create the `CMakeLists.txt` file for your project if it does not already exist, use the Raspberry Pi Pico C SDK's template if needed.
 - Add `include_directories(<inc. path>)` before your executable declaration, where `<inc. path>` is the path of the `include` folder in this repository.
 - Add `target_link_libraries(misc <lib. path> pico_stdlib pico_multicore)` at the end of the CMakeLists.txt, where `<lib. path>` is the path of the static library located earlier.

### Examples Compilation

Multiple examples are provided in the repository root directory. Compilation of these is similar to the above process.

Process:
 - Locate the `examples/pico` directory, create a new directory named `build`
 - Change the working directory into this new directory and run `cmake ..` to generate the build files.
 - Run `cmake --build` to compile the examples.
 - Inside this folder, a new subdirectory for each example has been created, containing the `.utf` file which may be flashed to the pico.

### Library Compilation

If recompiling the library is necessary, it can be done similarly to the above process. The requirements are no different than those above.

Process:

- Create a two new directories named `bin/pico` for the build files in the repository root directory.
- Open a command line with the working directory set to this directory.
- Run `cmake ../../src/pico/` to generate the build files using the pico CMakeLists
- Run `cmake --build` to compile the library.
- After compilation, a file named `libxy.a` will have been created, this may be linked in any project.

## Hardware

The required hardware is as follows:

- Raspberry Pi Pico
- 2 external 8-bit parallel DACs
- 2 low-pass filters

### Microcontroller GPIO

The lower 16 bits of the GPIO are reserved for the signal generation. The lower byte (bits 0 to 7) are the X signal, while the upper byte (bits 8 to 15) are the Y signal. Each signal is a 8-bit, unsigned integer. Example outputs are listed below:

| GPIO Output | X   | Y   | Position            |
|------------:|----:|----:|:--------------------|
| 0x0000      | 0   | 0   | Bottom left corner  |
| 0x00FF      | 255 | 0   | Bottom right corner |
| 0xFF00      | 0   | 255 | Top left corner     |
| 0xFFFF      | 255 | 255 | Top right corner    |
| 0x8080      | 128 | 128 | Center              |

### 8-bit DAC

The 8-bit DACs should be setup as to linearly map these codes to an analog voltage. The value of the maximum voltage can be arbitrary, the only requirement is that the mapping is approximately linear.

A simple but effective DAC design for this setup is a resistor ladder. 

### Low-Pass Filter

The output of the DAC, in an ideal case, is going to be a series of voltage steps. When the outputs of both DACs are steady, a dot is drawn to the screen. When a step occurs this dot moves to the next steady position. The purpose of the low-pass filters is to 'smooth' the movements of this dot. By adding an RC filter to the output of each DAC, the voltage step turns into an exponential curve. Ideally this curve will be linear, but the required complexity of achieving this is outweighed by the little improvement in appearance it offers. The continuity of the voltage curve means that the dot will spend a portion of its time 'moving' from the first position to the next. If the X and Y curves are both proportional to one another, this will create a straight line on the screen. The brightness of this line will vary depending on the derivative of the voltage curves, although in practice this is negligible.
