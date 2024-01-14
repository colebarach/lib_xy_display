// Header
#include "xy_renderer.h"

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_math.h"
#include "xy_shapes.h"

// Compilation Flags ----------------------------------------------------------------------------------------------------------

// #define RENDERER_DEBUG

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Libraries
#include <pico/stdlib.h>
#include <pico/multicore.h>

// C Standard Libraries
#include <stdlib.h>
#include <math.h>

// Debugging Libraries
#ifdef RENDERER_DEBUG
#include <stdio.h>
#endif // RENDERER_DEBUG

// Constants ------------------------------------------------------------------------------------------------------------------

#define RENDER_STACK_SIZE 256            // Maximum number of shapes being rendered in a single frame, may be modified.

// Global Memory --------------------------------------------------------------------------------------------------------------

volatile bool      rendererActive  = false;                    // Indicates whether or not to run the renderer.

volatile xyShape_t renderStack[RENDER_STACK_SIZE];             // Stack of shapes to be rendered
volatile uint16_t  stackTop        = 0;                        // Index of the top of the stack (next empty index)

uint16_t           stackShapeIndex = 0;                        // Index of the current shape being rendered (index in stack)
uint16_t           stackPointIndex = 0;                        // Index of the current point being rendered (index in shape)

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Renderer Entrypoint
// - Infinite loop for rendering.
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

    int index = 0;
    while(*data != '\0')
    {
        if(positionX + 0x0C >= upperBoundX || *data == '\n')
        {
            if(positionY - 0x14 < lowerBoundY) break;

            positionX = lowerBoundX;
            positionY -= 0x14;

            if(*data == '\n')
            {
                ++data;
                continue;
            }
        }

        if(index == 0)
        {
            string.characters = xyRenderChar(*data, positionX, positionY);
            if(string.characters == NULL) break;
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
        ++index;
    }

    return string;
}

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
    // Set flag to stop core 1
    rendererActive = false;

    // Delay long enough to cross the entire screen (waits until renderer is done moving)
    uint16_t delayUs = xyGetMoveDelayUs(0, 0, xyScreenWidth(), xyScreenHeight());
    sleep_us(delayUs);

    // Reset cursor
    xyCursorMove(0, 0);
    xyCursorColor(0, 0, 0);
}

void rendererEntrypoint()
{
    while(rendererActive)
    {
        #ifdef RENDERER_DEBUG
        printf("[libxy renderer] Shape Index: %3i, Point Index: %3i, ", stackShapeIndex, stackPointIndex);
        #endif // RENDERER_DEBUG

        // Check for empty stack
        if(stackTop == 0)
        {
            xyCursorColor(0, 0, 0);
            continue;
        }

        bool shapeValid = renderStack[stackShapeIndex].pointCount != 0 && renderStack[stackShapeIndex].points != NULL & renderStack[stackShapeIndex].visible;

        // Render shapes
        if(shapeValid)
        {
            xyCoord_t x = renderStack[stackShapeIndex].points[stackPointIndex].x + renderStack[stackShapeIndex].positionX;
            xyCoord_t y = renderStack[stackShapeIndex].points[stackPointIndex].y + renderStack[stackShapeIndex].positionY;

            uint16_t delayUs = xyGetCursorDelayUs(x, y);

            #ifdef RENDERER_DEBUG
            printf("Current Position: (%3i, %3i), Next Position: (%3i, %3i) => Delay: %4i\r\n  ", xyCursorX(), xyCursorY(), x, y, delayUs);
            #endif // RENDERER_DEBUG

            #ifdef RENDERER_DEBUG
            printf("Move()  =>  ");
            #endif // RENDERER_DEBUG

            xyCursorMove(x, y);

            #ifdef RENDERER_DEBUG
            printf("Delay()  =>  ");
            #endif // RENDERER_DEBUG

            sleep_us(delayUs);

            if(stackPointIndex == renderStack[stackShapeIndex].pointCount - 1)
            {
                #ifdef RENDERER_DEBUG
                printf("Beam Off()  =>  ");
                #endif // RENDERER_DEBUG

                xyCursorColor(0, 0, 0);
            }

            if(stackPointIndex == 0)
            {
                #ifdef RENDERER_DEBUG
                printf("Beam On()  =>  ");
                #endif // RENDERER_DEBUG

                xyCursorColor(renderStack[stackShapeIndex].colorRed, renderStack[stackShapeIndex].colorGreen, renderStack[stackShapeIndex].colorBlue);
            }
        }
        else
        {
            #ifdef RENDERER_DEBUG
            printf("Shape invalid.");
            #endif // RENDERER_DEBUG

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

        #ifdef RENDERER_DEBUG
        printf("\r\n");
        #endif // RENDERER_DEBUG
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
