// Header
#include "xy_hardware.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Raspberry Pi Pico
#include <pico/stdlib.h>

// Global Data ----------------------------------------------------------------------------------------------------------------

volatile uint16_t xBitOffset;
volatile uint16_t yBitOffset;
volatile uint32_t xBitmask;
volatile uint32_t yBitmask;

volatile xyCoord_t xWidth;
volatile xyCoord_t yHeight;

// Functions ------------------------------------------------------------------------------------------------------------------

void xyInitialize(uint16_t xBitOffset_, uint16_t xBitLength, uint16_t yBitOffset_, uint16_t yBitLength, xyCoord_t xWidth_, xyCoord_t yHeight_)
{
    // Store output information
    xBitOffset = xBitOffset_;
    yBitOffset = yBitOffset_;
    xBitmask = 0;
    yBitmask = 0;

    xWidth  = xWidth_;
    yHeight = yHeight_;

    // Configure X parallel output
    for(uint16_t index = xBitOffset; index < xBitOffset + xBitLength; ++index)
    {
        xBitmask |= (0b1 << index);
        gpio_init(index);
        gpio_set_dir(index, GPIO_OUT);
    }

    // Configure Y parallel output
    for(uint16_t index = yBitOffset; index < yBitOffset + yBitLength; ++index)
    {
        yBitmask |= (0b1 << index);
        gpio_init(index);
        gpio_set_dir(index, GPIO_OUT);
    }
}

void xyCursorSet(xyCoord_t x, xyCoord_t y)
{
    // Clamp cursor
    if(x >= xWidth)  x = xWidth  - 1;
    if(y >= yHeight) y = yHeight - 1;

    // Update output
    uint32_t outputValue = ((uint32_t)x << xBitOffset) & xBitmask | ((uint32_t)y << yBitOffset) & yBitmask;
    uint32_t outputMask = xBitmask | yBitmask;
    gpio_put_masked(outputMask, outputValue);
}

xyCoord_t xyWidth()
{
    return xWidth;
}

xyCoord_t xyHeight()
{
    return yHeight;
}
