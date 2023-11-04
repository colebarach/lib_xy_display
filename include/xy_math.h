#ifndef XY_MATH_H
#define XY_MATH_H

// X-Y Math -------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// To do:
// - What should these datatypes be?

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdint.h>

// Lookup Tables --------------------------------------------------------------------------------------------------------------

extern uint8_t cos256x256Unsigned[256];

extern uint8_t sin256x256Unsigned[256];

extern int8_t cos256x256Signed[256];

extern int8_t sin256x256Signed[256];

#endif // XY_MATH_H