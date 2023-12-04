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
// Naming: This file reserves the 'xyRenderer' and 'xyShape' prefixes, although the required 'xy_hardware.h' file reserves the
//   'xy' prefix.
// 
// To do:
// - String objects would be nice, need an internal stack for that
// - Render period is only approximate right now, specific timing may help with inconsistent appearances
// - How should the null shape be handled? It may need changed for strings. (Consider screen burn-in)
// - Reimplement string, overhaul methods
// - Hiding a shape still consumes a cycle, this can cause burn-in. How to fix this without recursion?

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_hardware.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdbool.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

// X-Y Shape
// - Handler for a set of X-Y points to draw in series.
// - The position and visibility parameters may be used to control the way a shape is rendered.
struct xyShape
{
    volatile xyPoint_t* points;          // Array of points to render
    uint16_t            pointCount;      // Number of elements in the point array
    xyCoord_t           positionX;       // X offset of the shape
    xyCoord_t           positionY;       // Y offset of the shape
    bool                visible;         // Indicates whether to render the shape or not
};

// Typedef for brevity.
typedef struct xyShape xyShape_t;

// Rendering ------------------------------------------------------------------------------------------------------------------

// Render Shape
// - Call to add the specified shape to the render stack
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile xyShape_t* xyRendererRenderShape(volatile xyPoint_t* points, uint16_t pointCount, xyCoord_t positionX, xyCoord_t positionY);

// Render Char
// - Call to render a character to the screen at the given position
// - Returns a reference to the successfully created shape, returns NULL otherwise
volatile xyShape_t* xyRendererRenderChar(char data, xyCoord_t xPosition, xyCoord_t yPosition);

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
// - Call to initialize the renderer using the specified output port.
// - See the 'xyCursorInitialize' function in 'xy_hardware.h' for details on the pin usage.
// - Must be called before any other function is used.
void xyRendererInitialize(uint16_t xBitOffset, uint16_t xBitLength, uint16_t yBitOffset, uint16_t yBitLength, xyCoord_t xWidth, xyCoord_t yHeight);

// Stop Renderer
// - Call to disable the renderer.
void xyRendererStop();

// Shapes ---------------------------------------------------------------------------------------------------------------------

// Copy Shape
// - Call to copy the points of the source shape into the destination shape.
// - The size of the destination must be greater than or equal to the size of the source shape.
void xyShapeCopy(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY);

// Append to Shape
// - Call to append the source shape to the index in the destination.
// - Use x and y origin to shift the position of the source shape.
void xyShapeAppend(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, uint16_t destinationIndex, xyCoord_t originX, xyCoord_t originY);

// Translate Shape
// - Call to translate the source shape into the destination buffer.
// - Applies the translations in the order of: offset, scale, then rotation.
// - Offsets the shape by offsetX and offsetY.
// - Scales the shape by scalarX and scalarY.
// - Rotates the shape by the angle theta.
void xyShapeTranslate(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t offsetX, xyCoord_t offsetY, float scalarX, float scalarY, float theta);

// Rotate Shape
// - Call to rotate the points about the specified pivot by a specified floating-point angle.
// - Source and destination may be the same array, in which the original data of the source is lost.
void xyShapeRotate(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, float theta);

// Rotate Shape (Integer)
// - Call to rotate the points about the specified pivot by a specified angle.
// - Theta is an 8-bit unsigned integer, mapping [0, 2*PI) to [0, 256).
// - Source and destination may be the same array, in which the original data of the source is lost.
void xyShapeRotateInt(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, uint8_t theta);

// Scale Shape
// - Call to scale a shape by the floating point x and y scalars.
// - The distance to the origin of each point is multiplied by xScalar and yScalar.
// - Source and destination may be the same array, in which the original data of the source is lost.
void xyShapeScale(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, float scalarX, float scalarY);

// Multiply Shape
// - Call to scale a shape up about the specified origin.
// - The distance to the origin of each point is multiplied by xScale and yScale.
// - Source and destination may be the same array, in which the original data of the source is lost.
void xyShapeMultiply(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t scalarX, xyCoord_t scalarY);

// Divide Shape
// - Call to scale a shape down about the specified origin.
// - The distance to the origin of each point is divided by xScale and yScale.
// - Source and destination may be the same array, in which the original data of the source is lost.
void xyShapeDivide(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t divisorX, xyCoord_t divisorY);

#endif // XY_RENDERER_H
