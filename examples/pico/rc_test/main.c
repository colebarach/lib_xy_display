// RC Filter Test File --------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>
#include <xy_shapes.h>

#include <stdio.h>
#include <pico/stdlib.h>

// I/O ------------------------------------------------------------------------------------------------------------------------

#define X_PORT_OFFSET  0       // X port starts at GPIO 0
#define X_PORT_SIZE    8       // X port spans GPIO 0 to GPIO 7
#define Y_PORT_OFFSET  8       // Y port starts at GPIO 8
#define Y_PORT_SIZE    8       // Y port spans GPIO 8 to GPIO 15

#define PERIOD_US      100

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xySetupXy(X_PORT_OFFSET, X_PORT_SIZE, Y_PORT_OFFSET, Y_PORT_SIZE);

    while(true)
    {
        xyCursorMove(0, 0);
        sleep_us(PERIOD_US);
        xyCursorMove(255, 255);
        sleep_us(PERIOD_US);
    }

    // Spin
    while(1);
}
