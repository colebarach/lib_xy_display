#ifndef XY_RENDERER_H
#define XY_RENDERER_H

// X-Y Renderer ---------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Set of functions related to the rendering system. Rendering, as opposed to drawing, allows the CPU to less
//   directly control the X-Y output. Rendering abstracts the act of displaying into shapes which are individually addressable.
//   Rendering is dependent on multiprogramming capability with precise timing, the platform and associated libraries must
//   support this, or this system is not possible.
// 
// Naming: This library reserves the 'xyRenderer' and 'xyShape' prefixes, see the below prototypes for specifics.

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_hardware.h"

// Datatypes ------------------------------------------------------------------------------------------------------------------

struct xyShape
{
    const uint16_t* points;              // Array of X-Y values, see xy_hardware.h for details on packing
    uint16_t        pointCount;          // Number of elements in point array
    uint8_t         xPosition;           // X offset of the shape
    uint8_t         yPosition;           // Y offset of the shape
};

// Public Functions -----------------------------------------------------------------------------------------------------------

// Render Shape
// - Call to add the specified shape to the render stack
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile struct xyShape* xyRendererRenderShape(const uint16_t* points, const uint16_t pointCount, uint8_t xPosition, uint8_t yPosition);

// Render Char
// - Call to render a character to the screen at the given position
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile struct xyShape* xyRendererRenderChar(char data, uint16_t xPosition, uint16_t yPosition);

// Render String
// - TODO: Should this have bounds?
// - Call to render a string to the screen at the given position
// - Returns 0 on success, -1 otherwise
int16_t xyRendererRenderString(const char* data, uint16_t xPosition, uint16_t yPosition);

// Clear Stack
// - Call to empty the render stack
void xyRendererClearStack();

// Initialize
// - Call to initialize the x-y renderer
// - Must be called before any other function is used
void xyRendererInitialize();

#endif // XY_RENDERER_H