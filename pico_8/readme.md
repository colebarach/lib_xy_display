# 8-bit Source for the Raspberry Pi Pico

This is the source code for an implementation of the xy_display library on a Raspberry Pi Pico microcontroller. The hardware descriptions are listed below, but the source may be adjusted to fit a different configuration.

## Usage

See the repository 'readme' file for information about using the library.

## Compilation

For more information about compiling and flashing software to the Pico, see Raspberry Pi's documentation (https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf). This guide will assume basic knowledge on this process.

Requirements:

- CMake
- Make
- GNU ARM toolchain for embedded systems
- Raspberry Pi Pico C SDK

Steps:

 - Open a command line with the working directory set to the pico_8/build directory.
 - Run 'cmake ..' to generate the makefile for the build.
 - Run 'make' to compile the library and the 'main.c' application.
 - Make will have generated a 'main.uf2' file in the build directory, flash this to the Pico.
 - The Pico will reboot, now running the main application.

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