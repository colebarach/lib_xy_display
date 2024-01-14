#ifndef XY_HARDWARE_H
#define XY_HARDWARE_H

// X-Y Hardware ---------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Base hardware abstraction for the X-Y library. This file is responsible for the following:
//    - Defining datatypes for the X and Y signals.
//    - Implementing the X and Y signal outputs.
//    - Providing a method to update the X and Y signal values.
//
//   The main purpose of this file is to implement a standard interface that higher lever sections of the library may refer to.
//   This file is not intended to be used directly in user applications, but that does not mean that it cannot be.
//
// Naming: This file reserves the 'xy' prefix.

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdint.h>
#include <stdbool.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

// X-Y Coordinate
// - The smallest datatype required to contain an X or Y position.
// - Note: this does not indicate the range of values that may be displayed, use the width / height functions for that.
typedef int16_t xyCoord_t;

// X-Y Coordinate (Long)
// - Extended datatype for holding an X or Y position with room to prevent overflow (used for arithmetic).
// - Guaranteed to be twice the size in bits and signed.
// - This is meant to be an intermediate value, this datatype should not be converted to a standard coordinate unless it is
//   certain to fit.
typedef int32_t xyCoordLong_t;

// X-Y Point
// - Datatype to represent a coordinate pair to be displayed.
struct xyPoint
{
    xyCoord_t x;
    xyCoord_t y;
};

// Typedef for brevity.
typedef struct xyPoint xyPoint_t;

// Color Channel
// - Datatype to represent a color value (red, green, or blue).
// - Only holds values from [0, 255].
typedef uint8_t xyColor_t;

// Functions ------------------------------------------------------------------------------------------------------------------

// Setup X & Y Ports
// - Call to setup the X and Y signal parallel ports.
// - Each port will begin at the pin number specified by the offset and span the specified number of contiguous pins.
// - For proper functionality, these ports may not overlap.
// - This must be called before the X-Y library can be used, calling any other function in the library before this one is
//   undefined behavior.
void xySetupXy(uint16_t portXOffset_, uint16_t portXSize, uint16_t portYOffset_, uint16_t portYSize);

// Setup Z Signal PWM
// - Call to setup the Z signal PWM output using the specified pin.
// - This function is subject to the limitation of the current hardware, please refer to your device's restrictions on PWM
//   output. If an invalid request is made, the behavior of this function is undefined.
// - The Z signal will output the apparent brightness (luma) of the intended color to render.
// - This signal is a redundant version of the RGB outputs, it may be used if RGB is not an option.
// - Use -1 to indicate the pin is to not be used.
void xySetupZ(int16_t pinZ);

// Setup RGB Signals PWM
// - Call to setup the red, green, and blue signal PWM outputs using the specified pins.
// - This function is subject to the limitations of the current hardware, please refer to your device's restrictions on PWM
//   output. If an invalid request is made, the behavior of this function is undefined.
// - The red, green, and blue signals will output a 3 PWM signals, the duty cycle of each corresponding to the value of each
//   channel.
// - If -1 is specified for any pin number, said signal will not be output.
void xySetupRgb(int16_t pinRed, int16_t pinGreen, int16_t pinBlue);

// Setup RC-Filter Timing
// - Call to set the time parameters of the output RC filter.
// - Will determine how long to wait between cursor update to ensure the intended position is reached.
// - Use the RC constant to specify the time constant of the output filter in us.
// - Use pixel threshold to specify how close the cursor must get to the intended position.
void xySetupRcTiming(uint16_t rcConstantUs_, uint16_t rcPixelThreshold_);

// Setup RGB/Z Signal Delay
// - Call to store the minimum required delay to change the value of the RGB / Z outputs.
// - The xyCursorColor function will block for this amount of time after updating the output.
void xySetupRgbzDelay(uint16_t delayUs);

// Setup Screen
// - Call to set the boundaries of the screen.
// - Use the wrap variable to specify whether coordinates out of bounds should be clamped to or wrapped around the screen.
void xySetupScreen(xyCoord_t width, xyCoord_t height, bool wrap);

// Move Cursor
// - Call to move the cursor to the specified position.
// - Will clamp / wrap the coordinates depending on the specified screen settings.
void xyCursorMove(xyCoord_t x, xyCoord_t y);

// Color Cursor
// - Call to set the color of the cursor to the specified value.
// - Only expects value that fit within the xyColor_t datatype (0 to 255 inclusive).
// - Will block for the amount of time specified in the xySetupRbgzDelay function.
void xyCursorColor(xyColor_t red, xyColor_t green, xyColor_t blue);

// Get Cursor Move Delay
// - Call to get the number of microseconds to wait after performing a move to the specified position.
uint16_t xyGetCursorDelayUs(xyCoord_t x, xyCoord_t y);

// Get Cursor Move Delay
// - Call to get the number of microseconds to wait after performing a move from point 1 to point 2.
uint16_t xyGetMoveDelayUs(xyCoord_t x1, xyCoord_t y1, xyCoord_t x2, xyCoord_t y2);

// Get Screen Width
// - Call to get the width of the screen in pixels.
xyCoord_t xyScreenWidth();

// Get Screen Height
// - Call to get the height of the screen in pixels.
xyCoord_t xyScreenHeight();

// Get Cursor Position X
// - Call to get the current position of the cursor
xyCoord_t xyCursorX();

// Get Cursor Position Y
// - Call to get the current position of the cursor
xyCoord_t xyCursorY();

#endif // XY_HARDWARE_H
