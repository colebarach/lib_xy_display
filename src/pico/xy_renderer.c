// Header
#include "xy_renderer.h"

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_math.h"
#include "xy_shapes.h"

// Compilation Flags ----------------------------------------------------------------------------------------------------------

// #define DEBUG_MODE

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Libraries
#include <pico/stdlib.h>
#include <pico/multicore.h>

// C Standard Libraries
#include <stdlib.h>
#include <math.h>

// Debugging Libraries
#ifdef DEBUG_MODE
#include <stdio.h>
#endif // DEBUG_MODE

// Constants ------------------------------------------------------------------------------------------------------------------

#define RENDER_STACK_SIZE 256            // Maximum number of shapes being rendered in a single frame, may be modified.

// Global Memory --------------------------------------------------------------------------------------------------------------

volatile xyShape_t renderStack[RENDER_STACK_SIZE];             // Stack of shapes to be rendered

volatile uint16_t  stackTop        = 0;                        // Index of the top of the stack (next empty index)
volatile bool      rendererActive  = false;                    // Indicates whether or not to run the renderer.

uint16_t           stackShapeIndex = 0;                        // Index of the current shape being rendered (index in stack)
uint16_t           stackPointIndex = 0;                        // Index of the current point being rendered (index in shape)

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Renderer Interrupt
// - Call to render the next point in the stack.
void rendererInterrupt();

// Renderer Entrypoint
// - Infinite loop for rendering, calls rendererInterrupt() periodically.
// - Entrypoint for Pico core #1.
// - Does not return.
void rendererEntrypoint();

// Function Definitions -------------------------------------------------------------------------------------------------------

volatile xyShape_t* xyRenderShape(volatile xyPoint_t* points, uint16_t pointCount, xyCoord_t positionX, xyCoord_t positionY, bool visible)
{
    // Check for full stack
    if(stackTop >= RENDER_STACK_SIZE) return NULL;

    // Write shape to stack and update top
    renderStack[stackTop].points     = points;
    renderStack[stackTop].pointCount = pointCount;
    renderStack[stackTop].positionX  = positionX;
    renderStack[stackTop].positionY  = positionY;
    renderStack[stackTop].colorRed   = 255;
    renderStack[stackTop].colorGreen = 255;
    renderStack[stackTop].colorBlue  = 255;
    renderStack[stackTop].visible    = visible;
    renderStack[stackTop].delayUs    = 0;
    ++stackTop;

    // Return a reference to the new shape
    return &(renderStack[stackTop - 1]);
}

volatile xyShape_t* xyRenderChar(char data, xyCoord_t xPosition, xyCoord_t yPosition)
{
    // Fetch the character shape from the ASCII table, render, and return the reference
    return xyRenderShape(xyShape16x16Ascii[data], xyShapeSize16x16Ascii[data], xPosition, yPosition, true);
}

xyString_t xyRenderString(char* data, xyCoord_t lowerBoundX, xyCoord_t lowerBoundY, xyCoord_t upperBoundX, xyCoord_t upperBoundY)
{
    xyString_t string =
    {
        .characters     = NULL,
        .characterCount = 0
    };

    xyCoord_t positionX = lowerBoundX;
    xyCoord_t positionY = upperBoundY - 0x10;

    bool start = true;
    while(*data != '\0')
    {
        if(positionX + 0x0C >= upperBoundX || *data == '\n')
        {
            if(positionY - 0x14 < lowerBoundY) break;

            positionX = lowerBoundX;
            positionY -= 0x14;
        }

        if(start)
        {
            string.characters = xyRenderChar(*data, positionX, positionY);
            if(string.characters == NULL) break;
            start = false;
        }
        else
        {
            if(xyRenderChar(*data, positionX, positionY) == NULL)
            {
                break;
            }
        }

        positionX += 0x10;
        ++data;
    }

    return string;
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

void xyRendererClear()
{
    stackTop = 0;
}

void xyRendererStart()
{
    // Ignore repeated calls
    if(rendererActive) return;

    // Set flag
    rendererActive = true;

    // Start core 1
    multicore_launch_core1(rendererEntrypoint);
}

void xyRendererStop()
{
    // Reset cursor
    xyCursorMove(0, 0);
    xyCursorColor(0, 0, 0);

    // Set flag to stop core 1
    rendererActive = false;
}

void rendererInterrupt()
{
    #ifdef DEBUG_MODE
    printf("Renderer ISR: Shape Index: %i, Point Index: %i  =>  ", stackShapeIndex, stackPointIndex);
    #endif // DEBUG_MODE

    // Check for empty stack
    if(stackTop == 0) return;

    bool shapeValid = renderStack[stackShapeIndex].pointCount != 0 && renderStack[stackShapeIndex].points != NULL & renderStack[stackShapeIndex].visible;

    if(stackPointIndex == 0)
    {
        #ifdef DEBUG_MODE
        printf("Delay %i us  =>  ", renderStack[stackShapeIndex].delayUs);
        #endif // DEBUG_MODE

        // Delay to reach start of shape
        sleep_us(renderStack[stackShapeIndex].delayUs);
    }

    // Start drawing at start of shape
    if(stackPointIndex == 0 && shapeValid)
    {
        #ifdef DEBUG_MODE
        printf("Beam on  =>  ");
        #endif // DEBUG_MODE

        // Set shape color
        xyCursorColor(renderStack[stackShapeIndex].colorRed, renderStack[stackShapeIndex].colorGreen, renderStack[stackShapeIndex].colorBlue);
    }

    // Stop drawing at end of shape
    if(stackPointIndex >= renderStack[stackShapeIndex].pointCount - 1 && shapeValid)
    {
        #ifdef DEBUG_MODE
        printf("Beam off  =>  ");
        #endif // DEBUG_MODE

        // Disable cursor
        xyCursorColor(0, 0, 0);
    }

    // Update indices
    ++stackPointIndex;

    // Start new shape at end of current
    if(stackPointIndex >= renderStack[stackShapeIndex].pointCount)
    {
        stackPointIndex = 0;
        ++stackShapeIndex;

        // Keep shape index inside of stack
        if(stackShapeIndex >= stackTop)
        {
            stackShapeIndex = 0;
        }
    }

    shapeValid = renderStack[stackShapeIndex].pointCount != 0 && renderStack[stackShapeIndex].points != NULL & renderStack[stackShapeIndex].visible;

    // Skip invalid shapes
    if(!shapeValid)
    {
        #ifdef DEBUG_MODE
        printf("Shape invalid. Moving to origin (%i, %i).\n", renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].positionY);
        #endif // DEBUG_MODE

        // Move cursor to origin of shape in order to be ready for the next shape. (If an invalid shape follows a large jump,
        // the cursor still needs moved so the cursor is near the next valid shape.)
        xyCursorMove(renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].positionY);

        return;
    }

    #ifdef DEBUG_MODE
    printf("Drawing point (%i, %i).\n", renderStack[stackShapeIndex].points[stackPointIndex].x + renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].points[stackPointIndex].y + renderStack[stackShapeIndex].positionY);
    #endif // DEBUG_MODE

    // Move cursor to next point
    xyCursorMove(renderStack[stackShapeIndex].points[stackPointIndex].x + renderStack[stackShapeIndex].positionX, renderStack[stackShapeIndex].points[stackPointIndex].y + renderStack[stackShapeIndex].positionY);
}

void rendererEntrypoint()
{
    while(rendererActive)
    {
        // To do: Timers are weird, don't really want to do the blocking call here, but it seems fast interrupts like this are
        // weird on the pico, especially given the fact that its on the 2nd core, as that means the core will just sit there
        // and spin. This is not a final solution, but it works for now.
        rendererInterrupt();
        sleep_us(5);
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
