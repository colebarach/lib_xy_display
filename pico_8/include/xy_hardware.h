#ifndef XY_HARDWARE_H
#define XY_HARDWARE_H

// X-Y Hardware ---------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Base hardware abstraction for the X-Y library. This file is responsible for defining the registers and
// functions that are exclusive to the platform.

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Libraries
#include <pico/stdlib.h>

// Registers ------------------------------------------------------------------------------------------------------------------

#define XY_CURSOR sio_hw->gpio_out // Cursor Register, holds the XY position of the cursor.
// HI byte - Unsigned integer, represents y position
// LO byte - Unsigned integer, represents x position

#define XY_DELAY() sleep_us(1);

void xyCursorInitialize();

// Adding to and subtracting from the same register in a single operation -----------------------------------------------------
// - The XY_CURSOR register allows the X and Y coordinates to be updated at the same time, although in effect this is only true if
// the operation is identical for the two. To performing different operations on the HI and LO words requires multiple
// instruction cycles, which is not ideal. To prevent this, the principles of the 2's complement may be leveraged. Adding a
// large integer has the same effect as subtracting a small one, due to overflow.
//
// - Adding X
// XY_CURSOR += N
//
// - Subtracting X
// XY_CURSOR += 2^16 - N
//
// - Adding Y
// XY_CURSOR += 2^8 * N
//
// - Subtracting Y
// XY_CURSOR += 2^16 - 2^8 * N

#define ADD_X(x) x
#define SUB_X(x) 0x0000 - x
#define ADD_Y(y) (y << 8)
#define SUB_Y(y) 0x0000 - (y << 8)

#endif // XY_HARDWARE_H