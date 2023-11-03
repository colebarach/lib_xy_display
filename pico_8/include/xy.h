#ifndef XY_H
#define XY_H

// X-Y ------------------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: X-Y aggregate library. Organizes includes and provides demos of library capability.
// 
// Naming: This library reserves the 'xy' prefix.
//
// To do:
// - Configurable screen and font sizes would be nice, if hardware supports it.
// - I'd like to move to >10-bit output, obviously this needs changes.
// - Blanking is important, need to figure that out 
// - Characters need updated to clean double tracing and weird end-points.
// - ASCII table needs finished
// - Configurable XY packaging, consider using macro for register assignment
// - Generic X-Y storage in points, currently hardware dependent.
// - Pick and implement a constant period for the renderer / pen, ex. 1us
// - Demos for renderer need dynamically allocated memory, how to handle this

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_hardware.h"
#include "xy_drawing.h"
#include "xy_renderer.h"
#include "xy_shapes.h"
#include "xy_math.h"

#endif // XY_H