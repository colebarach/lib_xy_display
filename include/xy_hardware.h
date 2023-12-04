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
//
// To do:
// - Blanking

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdint.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

// X-Y Coordinate
// - The smallest datatype required to contain an X or Y position.
// - Note: this does not indicate the range of values that may be displayed, use the width / height functions for that.
typedef uint16_t xyCoord_t;

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

// Functions ------------------------------------------------------------------------------------------------------------------

// X-Y Initialize
// - Call to initialize the X-Y cursor outputs and the library's internal state.
// - The contiguous bit-field of specified length and offset is reserved as an output for the individual X and Y signals.
// - Must be called before the library is used.
// - Note that a higher level portion of the library may perform this step in its initialization (see respective documentation
//   to determine if this is the case).
void xyInitialize(uint16_t xBitOffset, uint16_t xBitLength, uint16_t yBitOffset, uint16_t yBitLength, xyCoord_t xWidth, xyCoord_t yHeight);

// X-Y Cursor Set
// - Call to set the position of the cursor.
void xyCursorSet(xyCoord_t x, xyCoord_t y);

// X-Y Width
// - Call to get the width of the screen.
xyCoord_t xyWidth();

// X-Y Height
// - Call to get the height of the screen.
xyCoord_t xyHeight();

#endif // XY_HARDWARE_H
