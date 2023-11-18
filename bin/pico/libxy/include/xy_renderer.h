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
// Naming: This library reserves the 'xy' prefix, see the below prototypes for specifics.
// 
// To do:
// - String objects would be nice, need an internal stack for that
// - Render period is only approximate right now, specific timing may help with inconsistent appearances
// - How should the null shape be handled? It may need changed for strings. (Consider screen burn-in)
// - Reimplement string, overhaul methods
// - Does xy hardware need included here, it defines a lot of functions not used by the end user
// - Hiding a shape still consumes a cycle, this can cause burn-in. How to fix this without recursion?

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_hardware.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdbool.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

struct xyShape
{
    volatile struct xyPoint* points;     // Array of points to render
    uint16_t        pointCount;          // Number of elements in the point array
    xyCoord         positionX;           // X offset of the shape
    xyCoord         positionY;           // Y offset of the shape
    bool            visible;             // Indicates whether to render the shape or not
};

// Rendering ------------------------------------------------------------------------------------------------------------------

// Render Shape
// - Call to add the specified shape to the render stack
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile struct xyShape* xyRendererRenderShape(volatile struct xyPoint* points, uint16_t pointCount, xyCoord positionX, xyCoord positionY);

// Render Char
// - Call to render a character to the screen at the given position
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile struct xyShape* xyRendererRenderChar(char data, xyCoord xPosition, xyCoord yPosition);

// // Render String
// // - TODO: Should this have bounds?
// // - Call to render a string to the screen at the given position
// // - Returns 0 on success, -1 otherwise
// int16_t xyRendererRenderString(const char* data, uint16_t xPosition, uint16_t yPosition);

// Clear Stack
// - Call to empty the render stack
void xyRendererClearStack();

// Renderer -------------------------------------------------------------------------------------------------------------------

// Initialize Renderer
// - Call to initialize the renderer.
// - Must be called before any other function is used.
void xyRendererInitialize();

// Stop Renderer
// - Call to disable the renderer.
void xyRendererStop();

// Shapes ---------------------------------------------------------------------------------------------------------------------

// Allocate Shape
// - Call to allocate memory for a new shape with a specified number of points.
// - Shape must be de-allocated when no longer in use.
struct xyPoint* xyShapeAllocate(uint16_t size);

// Copy Shape
// - Call to copy the points of the source shape into the destination shape
// - The size of the destination must be greater than or equal to the size of the source shape
void xyShapeCopy(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY);

// Append to Shape
// - Call to append the source shape to the index in the destination
// - Use x and y origin to shift the position of the source shape
void xyShapeAppend(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, uint16_t destinationIndex, xyCoord originX, xyCoord originY);

// Rotate Shape
// - Call to rotate the points about the specified pivot by a specified angle
// - Theta is an 8-bit unsigned integer, mapping [0, 2PI) to [0, 256)
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeRotate(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, uint8_t theta);

// Scale Shape
// - Call to scale a shape by the floating point x and y scalars
// - The distance to the origin of each point is multiplied by xScalar and yScalar
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeScale(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, float scalarX, float scalarY);

// Multiply Shape
// - Call to scale a shape up about the specified origin
// - The distance to the origin of each point is multiplied by xScale and yScale
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeMultiply(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, xyCoord scalarX, xyCoord scalarY);

// Divide Shape
// - Call to scale a shape down about the specified origin
// - The distance to the origin of each point is divided by xScale and yScale
// - Source and destination may be the same array, in which the original data of the source is lost
void xyShapeDivide(volatile struct xyPoint* source, volatile struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, xyCoord divisorX, xyCoord divisorY);

#endif // XY_RENDERER_H
