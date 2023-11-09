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

volatile struct xyShape renderStack[RENDER_STACK_SIZE];        // Stack of shapes to be rendered
volatile uint16_t       stackTop = 0;                          // Index of the top of the stack (next empty index)
uint16_t                stackShapeIndex = 0;                   // Index of the current shape being rendered (index in stack)
uint16_t                stackPointIndex = 0;                   // Index of the current point being rendered (index in shape)

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

volatile struct xyShape* xyRendererRenderShape(struct xyPoint* points, uint16_t pointCount, xyCoord positionX, xyCoord positionY)
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

volatile struct xyShape* xyRendererRenderChar(char data, xyCoord xPosition, xyCoord yPosition)
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

void xyRendererInitialize()
{
    xyCursorInitialize();

    // Start core 1
    multicore_launch_core1(rendererEntrypoint);
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

        // Keep stack index within stack
        if(stackShapeIndex >= stackTop) stackShapeIndex = 0;
    }

    // Ignore null shape
    if(renderStack[stackShapeIndex].points == NULL || renderStack[stackShapeIndex].pointCount == 0) return;

    // Ignore hidden shapes
    if(!renderStack[stackShapeIndex].visible) return;

    // Update cursor
    xyCursorSet(renderStack[stackShapeIndex].points[stackPointIndex].x + renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].points[stackPointIndex].y + renderStack[stackShapeIndex].positionY);
    ++stackPointIndex;
}

void rendererEntrypoint()
{
    while(true)
    {
        // TODO: Need a timer here, not just a function call.
        // - Spec appropriate one, set at start, blocking call at end
        rendererInterrupt();
        xyDelay();
    }
}

struct xyPoint* xyShapeAllocate(uint16_t size)
{
    // Allocate memory for points
    struct xyPoint* destination = malloc(sizeof(struct xyPoint) * size);

    // Return shape
    return destination;
}

void xyShapeDeallocate(struct xyPoint* target)
{
    free(target);
}

void xyShapeCopy(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY)
{
    // Copy point values from source
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index].x = source[index].x + originX;
        destination[index].y = source[index].y + originY;
    }
}

void xyShapeAppend(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, uint16_t destinationIndex, xyCoord originX, xyCoord originY)
{
    // Copy point values from source starting from destination index
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index + destinationIndex].x = source[index].x + originX;
        destination[index + destinationIndex].y = source[index].y + originY;
    }
}

void xyShapeRotate(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, uint8_t theta)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong x = (xyCoordLong)source[index].x - originX;
        xyCoordLong y = (xyCoordLong)source[index].y - originY;

        xyCoordLong xPrime = round((x * cos256x256Signed[theta] - y * sin256x256Signed[theta]) / 127.0f);
        xyCoordLong yPrime = round((x * sin256x256Signed[theta] + y * cos256x256Signed[theta]) / 127.0f);

        destination[index].x = (xyCoord)(xPrime + originX);
        destination[index].y = (xyCoord)(yPrime + originY);
    }
}

void xyShapeScale(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, float scalarX, float scalarY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong x = (xyCoordLong)source[index].x - originX;
        xyCoordLong y = (xyCoordLong)source[index].y - originY;

        destination[index].x = round((xyCoord)(x * scalarX + originX));
        destination[index].y = round((xyCoord)(y * scalarY + originY));
    }
}

void xyShapeMultiply(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, xyCoord scalarX, xyCoord scalarY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong x = (xyCoordLong)source[index].x - originX;
        xyCoordLong y = (xyCoordLong)source[index].y - originY;

        destination[index].x = (xyCoord)(x * scalarX + originX);
        destination[index].y = (xyCoord)(y * scalarY + originY);
    }
}

void xyShapeDivide(struct xyPoint* source, struct xyPoint* destination, uint16_t sourceSize, xyCoord originX, xyCoord originY, xyCoord divisorX, xyCoord divisorY)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        xyCoordLong x = (xyCoordLong)source[index].x - originX;
        xyCoordLong y = (xyCoordLong)source[index].y - originY;

        destination[index].x = (xyCoord)(x / divisorX + originX);
        destination[index].y = (xyCoord)(y / divisorY + originY);
    }
}
