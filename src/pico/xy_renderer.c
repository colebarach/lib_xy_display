// Header
#include "xy_renderer.h"

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_math.h"
#include "xy_shapes.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Libraries
#include <pico/stdlib.h>
#include <pico/multicore.h>

// C Standard Libraries
#include <stdlib.h>
#include <math.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define RENDER_STACK_SIZE 256            // Maximum number of shapes being rendered in a single frame, may be modified.

// Global Memory --------------------------------------------------------------------------------------------------------------

volatile xyShape_t renderStack[RENDER_STACK_SIZE];             // Stack of shapes to be rendered
volatile uint16_t  stackTop        = 0;                        // Index of the top of the stack (next empty index)
volatile bool      rendererActive = false;                     // Indicates whether or not to run the renderer.

uint16_t           stackShapeIndex = 0;                        // Index of the current shape being rendered (index in stack)
uint16_t           stackPointIndex = 0;                        // Index of the current point being rendered (index in shape)

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Renderer Interrupt
// - Call to render the next point in the stack
void rendererInterrupt();

// Renderer Entrypoint
// - Infinite loop for rendering, calls rendererInterrupt() periodically
// - Entrypoint for Pico core #1
// - Does not return
void rendererEntrypoint();

// Function Definitions -------------------------------------------------------------------------------------------------------

volatile xyShape_t* xyRendererRenderShape(volatile xyPoint_t* points, uint16_t pointCount, xyCoord_t positionX, xyCoord_t positionY)
{
    // Check for full stack
    if(stackTop >= RENDER_STACK_SIZE) return NULL;

    // Write shape to stack and update top
    renderStack[stackTop].points     = points;
    renderStack[stackTop].pointCount = pointCount;
    renderStack[stackTop].positionX  = positionX;
    renderStack[stackTop].positionY  = positionY;
    renderStack[stackTop].visible    = true;
    ++stackTop;

    // Return a reference to the new shape
    return &(renderStack[stackTop - 1]);
}

volatile xyShape_t* xyRendererRenderChar(char data, xyCoord_t xPosition, xyCoord_t yPosition)
{
    // Fetch the character shape from the ASCII table, render, and return the reference
    return xyRendererRenderShape(xyShape16x16Ascii[data], xyShapeSize16x16Ascii[data], xPosition, yPosition);
}

// int16_t xyRendererRenderString(const char* data, uint16_t xPosition, uint16_t yPosition)
// {
//     uint16_t index = 0;

//     uint16_t cursorXPosition = xPosition;
//     uint16_t cursorYPosition = yPosition;

//     while(data[index] != '\0')
//     {
//         // Check for control characters and screen bounds
//         // - TODO: Hard coded values
//         // - TODO: This code is weird, could be organized better
//         if(data[index] == '\n' || cursorXPosition + 0x0C > 0xFF)
//         {
//             // Check y bounds
//             if(cursorYPosition < 0x14)
//             {
//                 return -1;
//             }

//             // Move to new line
//             cursorXPosition = xPosition;
//             cursorYPosition -= 0x14;

//             if(data[index] == '\n')
//             {
//                 ++index;
//                 continue;
//             }
//         }

//         // Render character and check for error
//         if(xyRendererRenderChar(data[index], cursorXPosition, cursorYPosition) == NULL)
//         {
//             return -1;
//         }

//         // Increment cursor and index
//         // - TODO: Hard coded values
//         cursorXPosition += 0x10;
//         ++index;
//     }

//     return 0;
// }

void xyRendererClearStack()
{
    stackTop = 0;
}

void xyRendererInitialize(uint16_t xBitOffset, uint16_t xBitLength, uint16_t yBitOffset, uint16_t yBitLength, xyCoord_t xWidth, xyCoord_t yHeight)
{
    // Initialize lower level library
    xyInitialize(xBitOffset, xBitLength, yBitOffset, yBitLength, xWidth, yHeight);

    // Set flag
    rendererActive = true;

    // Start core 1
    multicore_launch_core1(rendererEntrypoint);
}

void xyRendererStop()
{
    // Reset cursor
    xyCursorSet(0, 0);

    // Set flag to stop core 1
    rendererActive = false;
}

void rendererInterrupt()
{
    // Check for empty stack
    if(stackTop == 0) return;

    // Keep point index within shape
    if(stackPointIndex >= renderStack[stackShapeIndex].pointCount)
    {
        stackPointIndex = 0;
        ++stackShapeIndex;
    }

    // Keep stack index within stack
    if(stackShapeIndex >= stackTop) stackShapeIndex = 0;

    // Ignore hidden and null shapes
    if(!renderStack[stackShapeIndex].visible || renderStack[stackShapeIndex].points == NULL || renderStack[stackShapeIndex].pointCount == 0)
    {
        ++stackShapeIndex;
        return;
    }

    // Update cursor
    xyCursorSet(renderStack[stackShapeIndex].points[stackPointIndex].x + renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].points[stackPointIndex].y + renderStack[stackShapeIndex].positionY);
    ++stackPointIndex;
}

void rendererEntrypoint()
{
    while(rendererActive)
    {
        // TODO: Need a timer here, not just a function call.
        // - Spec appropriate one, set at start, blocking call at end
        rendererInterrupt();
        // xyDelay(); // TODO: TIMERS
    }
}

void xyShapeCopy(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY)
{
    // Copy point values from source
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index].x = source[index].x + originX;
        destination[index].y = source[index].y + originY;
    }
}

void xyShapeAppend(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, uint16_t destinationIndex, xyCoord_t originX, xyCoord_t originY)
{
    // Copy point values from source starting from destination index
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index + destinationIndex].x = source[index].x + originX;
        destination[index + destinationIndex].y = source[index].y + originY;
    }
}

void xyShapeTranslate(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t offsetX, xyCoord_t offsetY, float scalarX, float scalarY, float theta)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        // Offset
        xyCoordLong_t x = (xyCoordLong_t)source[index].x + offsetX - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y + offsetY - originY;

        // Scale
        x *= scalarX;
        y *= scalarY;

        // Rotation
        xyCoordLong_t xPrime = round(x * cosf(theta) - y * sinf(theta));
        xyCoordLong_t yPrime = round(x * sinf(theta) + y * cosf(theta));

        destination[index].x = (xyCoord_t)(xPrime + originX);
        destination[index].y = (xyCoord_t)(yPrime + originY);
    }
}

void xyShapeRotate(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, float theta)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong_t x = (xyCoordLong_t)source[index].x - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y - originY;

        xyCoordLong_t xPrime = round(x * cosf(theta) - y * sinf(theta));
        xyCoordLong_t yPrime = round(x * sinf(theta) + y * cosf(theta));

        destination[index].x = (xyCoord_t)(xPrime + originX);
        destination[index].y = (xyCoord_t)(yPrime + originY);
    }
}

void xyShapeRotateInt(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, uint8_t theta)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong_t x = (xyCoordLong_t)source[index].x - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y - originY;

        xyCoordLong_t xPrime = round((x * cos256x256Signed[theta] - y * sin256x256Signed[theta]) / 127.0f);
        xyCoordLong_t yPrime = round((x * sin256x256Signed[theta] + y * cos256x256Signed[theta]) / 127.0f);

        destination[index].x = (xyCoord_t)(xPrime + originX);
        destination[index].y = (xyCoord_t)(yPrime + originY);
    }
}

void xyShapeScale(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, float scalarX, float scalarY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong_t x = (xyCoordLong_t)source[index].x - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y - originY;

        destination[index].x = round((xyCoord_t)(x * scalarX + originX));
        destination[index].y = round((xyCoord_t)(y * scalarY + originY));
    }
}

void xyShapeMultiply(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t scalarX, xyCoord_t scalarY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong_t x = (xyCoordLong_t)source[index].x - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y - originY;

        destination[index].x = (xyCoord_t)(x * scalarX + originX);
        destination[index].y = (xyCoord_t)(y * scalarY + originY);
    }
}

void xyShapeDivide(volatile xyPoint_t* source, volatile xyPoint_t* destination, uint16_t sourceSize, xyCoord_t originX, xyCoord_t originY, xyCoord_t divisorX, xyCoord_t divisorY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong_t x = (xyCoordLong_t)source[index].x - originX;
        xyCoordLong_t y = (xyCoordLong_t)source[index].y - originY;

        destination[index].x = (xyCoord_t)(x / divisorX + originX);
        destination[index].y = (xyCoord_t)(y / divisorY + originY);
    }
}
