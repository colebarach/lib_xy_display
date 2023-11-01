// Header
#include "xy_renderer.h"

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_shapes.h"
#include "xy_math.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Libraries
#include <pico/stdlib.h>
#include <pico/multicore.h>

// C Standard Libraries
#include <math.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define RENDER_PERIOD_US  1
#define RENDER_STACK_SIZE 256

// Global Memory --------------------------------------------------------------------------------------------------------------

volatile struct xyShape renderStack[RENDER_STACK_SIZE];        // Stack of shapes to be rendered
volatile uint16_t       stackTop = 0;                          // Index of the top of the stack (next empty index)
uint16_t                stackShapeIndex = 0;                   // Index of the current shape being rendered (index in stack)
uint16_t                stackPointIndex = 0;                   // Index of the current point being rendered (index in shape)

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Renderer Interrupt
// - Call to render the next point in the stack
void rendererInterrupt();

// Renderer Entrypointxy_shapes
// - Infinite loop for rendering, calls rendererInterrupt() periodically
// - Entrypoint for Pico core #1
// - Does not return
void rendererEntrypoint();

// Function Definitions -------------------------------------------------------------------------------------------------------

volatile struct xyShape* xyRendererRenderShape(uint16_t* points, uint16_t pointCount, uint8_t xPosition, uint8_t yPosition)
{
    // Check for full stack
    if(stackTop >= RENDER_STACK_SIZE) return NULL;

    // Ignore null shape
    if(points == NULL || pointCount == 0) return NULL;

    // Write shape to stack and update top
    renderStack[stackTop].points     = points;
    renderStack[stackTop].pointCount = pointCount;
    renderStack[stackTop].xPosition  = xPosition;
    renderStack[stackTop].yPosition  = yPosition;
    ++stackTop;

    // Return a reference to the new shape
    return &(renderStack[stackTop - 1]);
}

volatile struct xyShape* xyRendererRenderChar(char data, uint16_t xPosition, uint16_t yPosition)
{
    // Fetch the character shape from the ASCII table, render, and return the reference
    return xyRendererRenderShape(xyShape16x16Ascii[data], xyShapeSize16x16Ascii[data], xPosition, yPosition);
}

int16_t xyRendererRenderString(const char* data, uint16_t xPosition, uint16_t yPosition)
{
    uint16_t index = 0;

    uint16_t cursorXPosition = xPosition;
    uint16_t cursorYPosition = yPosition;

    while(data[index] != '\0')
    {
        // Check for control characters and screen bounds
        // - TODO: Hard coded values
        // - TODO: This code is weird, could be organized better
        if(data[index] == '\n' || cursorXPosition + 0x0C > 0xFF)
        {
            // Check y bounds
            if(cursorYPosition < 0x14)
            {
                return -1;
            }

            // Move to new line
            cursorXPosition = xPosition;
            cursorYPosition -= 0x14;

            if(data[index] == '\n')
            {
                ++index;
                continue;
            }
        }

        // Render character and check for error
        if(xyRendererRenderChar(data[index], cursorXPosition, cursorYPosition) == NULL)
        {
            return -1;
        }

        // Increment cursor and index
        // - TODO: Hard coded values
        cursorXPosition += 0x10;
        ++index;
    }

    return 0;
}

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

    // Update cursor
    // - TODO: Left-shifting for the y position does not work, it has to be '* 256'. I don't know why this is.
    XY_CURSOR = renderStack[stackShapeIndex].points[stackPointIndex] + renderStack[stackShapeIndex].xPosition + (uint16_t)renderStack[stackShapeIndex].yPosition * 256;
    ++stackPointIndex;
}

void rendererEntrypoint()
{
    while(true)
    {
        rendererInterrupt();
        sleep_us(RENDER_PERIOD_US);
    }
}

uint16_t* xyShapeAllocate(uint16_t size)
{
    // Allocate memory for points
    uint16_t* destination = malloc(sizeof(uint16_t) * size);

    // Return shape
    return destination;
}

void xyShapeDeallocate(uint16_t* target)
{
    free(target);
}

void xyShapeCopy(uint16_t* source, uint16_t* destination, uint16_t sourceSize)
{
    // Copy point values from source
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index] = source[index];
    }
}

void xyShapeAppend(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint16_t destinationOffset, uint8_t xOffset, uint8_t yOffset)
{
    // Copy point values from source into offset position
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        destination[index + destinationOffset] = source[index] + xOffset + yOffset * 256;
    }
}

void xyShapeRotate(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xPivot, uint8_t yPivot, uint8_t theta)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        int16_t x = (int16_t)(source[index] & 0x00FF)       - xPivot;
        int16_t y = (int16_t)(source[index] & 0xFF00) / 256 - yPivot;

        int16_t xPrime = (x * cosLut256x256Signed[theta] - y * sinLut256x256Signed[theta]) / 127;
        int16_t yPrime = (x * sinLut256x256Signed[theta] + y * cosLut256x256Signed[theta]) / 127;

        destination[index] = (uint8_t)(xPrime + xPivot) + (uint8_t)(yPrime + yPivot) * 256;
    }
}

void xyShapeScale(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, float xScale, float yScale)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        int16_t x = (int16_t)(source[index] & 0x00FF)         - xCenter;
        int16_t y = (int16_t)((source[index] & 0xFF00) / 256) - yCenter;

        destination[index] = (uint8_t)(x * xScale + xCenter) + (uint8_t)(y * yScale + yCenter) * 256;
    }
}

void xyShapeMultiply(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, int16_t xScale, int16_t yScale)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        int16_t x = (int16_t)(source[index] & 0x00FF)         - xCenter;
        int16_t y = (int16_t)((source[index] & 0xFF00) / 256) - yCenter;

        destination[index] = (uint8_t)(x * xScale + xCenter) + (uint8_t)(y * yScale + yCenter) * 256;
    }
}

void xyShapeDivide(uint16_t* source, uint16_t* destination, uint16_t sourceSize, uint8_t xCenter, uint8_t yCenter, int16_t xScale, int16_t yScale)
{
    for(uint16_t index = 0; index < sourceSize; ++index)
    {
        int16_t x = (int16_t)(source[index] & 0x00FF)         - xCenter;
        int16_t y = (int16_t)((source[index] & 0xFF00) / 256) - yCenter;

        destination[index] = (uint8_t)(x / xScale + xCenter) + (uint8_t)(y / yScale + yCenter) * 256;
    }
}