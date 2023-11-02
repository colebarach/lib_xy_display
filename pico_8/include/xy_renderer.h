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
    uint16_t* points;              // Array of X-Y values, see xy_hardware.h for details on packaging
    uint16_t  pointCount;          // Number of elements in point array
    uint8_t   xPosition;           // X offset of the shape
    uint8_t   yPosition;           // Y offset of the shape
};

// Rendering ------------------------------------------------------------------------------------------------------------------

// Render Shape
// - Call to add the specified shape to the render stack
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile struct xyShape* xyRendererRenderShape(uint16_t* points, uint16_t pointCount, uint8_t xPosition, uint8_t yPosition);

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

// Renderer -------------------------------------------------------------------------------------------------------------------

// Initialize
// - Call to initialize the x-y renderer
// - Must be called before any other function is used
void xyRendererInitialize();

// Shapes ---------------------------------------------------------------------------------------------------------------------

// Allocate Shape
// - Call to allocate memory for a new shape with a specified number of points.
// - Shape must be de-allocated when no longer in use.
uint16_t* xyShapeAllocate(uint16_t size);

// De-allocate Shape
// - Call to de-allocate the memory created for a shape.
// - The referenced shape cannot be used after this.
void xyShapeDeallocate(uint16_t* target);

// Copy Shape
// - Call to copy the points of the source shape into the destination shape
// - The size of the destination must be greater than or equal to the size of the source shape
void xyShapeCopy(uint16_t* source, uint16_t* destination, uint16_t sourceSize);

void xyShapeAppend(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint16_t destinationOffset, uint8_t xOffset, uint8_t yOffset);

// Rotate Shape
// - Call to rotate the points about the specified pivot by a specified angle
// - Theta is an 8-bit unsigned integer, mapping [0, 2PI) to [0, 256)
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeRotate(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xPivot, uint8_t yPivot, uint8_t theta);

// Scale Shape
void xyShapeScale(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, float xScale, float yScale);

// Multiply Shape
// - Call to scale a shape up about the specified origin
// - The distance to the origin of each point is multiplied by xScale and yScale
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeMultiply(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, int16_t xScale, int16_t yScale);

// Divide Shape
// - Call to scale a shape down about the specified origin
// - The distance to the origin of each point is divided by xScale and yScale
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeDivide(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, int16_t xScale, int16_t yScale);

#endif // XY_RENDERER_H