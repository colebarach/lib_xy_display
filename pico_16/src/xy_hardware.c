// Header
#include "xy_hardware.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Raspberry Pi Pico
#include <pico/stdlib.h>

// Macros ---------------------------------------------------------------------------------------------------------------------

// XY Cursor
// - Parallel output register of the X & Y signals
#define XY_CURSOR sio_hw->gpio_out

// Cursor X
// - Maps an unsigned integer X to the cursor bitfield
#define XY_CURSOR_X(x) (x)

// Cursor Y
// - Maps an unsigned integer Y to the cursor bitfield
#define XY_CURSOR_Y(y) (y << 8)

// Update Delay
// - Function to block execution for 1 update period
#define XY_DELAY_UPDATE() sleep_us(1);

// Functions ------------------------------------------------------------------------------------------------------------------

void xyCursorSet(xyCoord x, xyCoord y)
{
    // TODO: Is a bitmask needed to protect other outputs?
    XY_CURSOR = (XY_CURSOR_X(x) | XY_CURSOR_Y(y));
}

void xyDelay()
{
    XY_DELAY_UPDATE();
}

void xyCursorInitialize()
{
    // X
    gpio_init(0);
    gpio_init(1);
    gpio_init(2);
    gpio_init(3);
    gpio_init(4);
    gpio_init(5);
    gpio_init(6);
    gpio_init(7);
    
    gpio_set_dir(0, GPIO_OUT);
    gpio_set_dir(1, GPIO_OUT);
    gpio_set_dir(2, GPIO_OUT);
    gpio_set_dir(3, GPIO_OUT);
    gpio_set_dir(4, GPIO_OUT);
    gpio_set_dir(5, GPIO_OUT);
    gpio_set_dir(6, GPIO_OUT);
    gpio_set_dir(7, GPIO_OUT);

    // Y
    gpio_init(8);
    gpio_init(9);
    gpio_init(10);
    gpio_init(11);
    gpio_init(12);
    gpio_init(13);
    gpio_init(14);
    gpio_init(15);

    gpio_set_dir(8, GPIO_OUT);
    gpio_set_dir(9, GPIO_OUT);
    gpio_set_dir(10, GPIO_OUT);
    gpio_set_dir(11, GPIO_OUT);
    gpio_set_dir(12, GPIO_OUT);
    gpio_set_dir(13, GPIO_OUT);
    gpio_set_dir(14, GPIO_OUT);
    gpio_set_dir(15, GPIO_OUT);
}

xyCoord xyWidth()
{
    return 0x100;
}

xyCoord xyHeight()
{
    return 0x100;
}