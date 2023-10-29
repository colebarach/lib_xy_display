#ifndef XY_SHAPES_H
#define XY_SHAPES_H

// X-Y Shapes -----------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Collection of primate shapes to use in X-Y rendering.

// Includes -------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdint.h>

// Primatives -----------------------------------------------------------------------------------------------------------------

#define XY_SHAPE_SIZE_NULL 0
extern uint16_t* const xyShapeNull;

#define XY_SHAPE_SIZE_POINT 1
extern uint16_t xyShapePoint[XY_SHAPE_SIZE_POINT];

// ASCII ----------------------------------------------------------------------------------------------------------------------

// 16x16 ASCII Character Symbol Array
// - Index correlates to the integer value of said symbol, ex. index 0x30 => '0'
// - Each element is a pointer to the base of the point array of the symbol
// - The size of the symbol's point array is stored in the below array.
extern uint16_t* xyShape16x16Ascii[128];

// 16x16 ASCII Character Symbol Sizes Array
// - Parallel array to the xyShape16x16Ascii array. See above for more info
extern uint16_t xyShapeSize16x16Ascii[128];

#endif // XY_SHAPES_H