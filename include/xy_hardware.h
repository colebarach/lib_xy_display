#ifndef XY_HARDWARE_H
#define XY_HARDWARE_H

// X-Y Hardware ---------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Base hardware abstraction for the X-Y library. This file is responsible for (TODO)
//
// To do:
// - Should the XY_CURSOR be exposed?
// - I want these functions inline'd, how to do this?
// - Consider implementation specific versions of this header, would solve above problems.

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdint.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

typedef uint16_t xyCoord;

typedef int32_t xyCoordLong;

struct xyPoint
{
    xyCoord x;
    xyCoord y;
};

// Functions ------------------------------------------------------------------------------------------------------------------

// X-Y Cursor Set
// - Call to set the position of the cursor
void xyCursorSet(xyCoord x, xyCoord y);

// X-Y Delay
void xyDelay();

// XY Cursor Initialize
// - Call to initialize the cursor for output
// - Required to be called before output is used
// - Note: If using the rendering method, this call is already made by the xyRendererInitialize function
void xyCursorInitialize();

xyCoord xyWidth();

xyCoord xyHeight();

#endif // XY_HARDWARE_H
