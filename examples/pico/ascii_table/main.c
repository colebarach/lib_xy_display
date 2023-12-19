// ASCII Table Demo -----------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Draws a static 'ASCII' table on the screen, demonstrating the method of drawing characters and the available
//   symbols.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>
#include <xy_shapes.h>

// I/O ------------------------------------------------------------------------------------------------------------------------

#define X_PORT_OFFSET  0       // X port starts at GPIO 0
#define X_PORT_SIZE    8       // X port spans GPIO 0 to GPIO 7
#define Y_PORT_OFFSET  8       // Y port starts at GPIO 8
#define Y_PORT_SIZE    8       // Y port spans GPIO 8 to GPIO 15
#define Z_PIN          16      // Z output is GPIO 16

#define SCREEN_WIDTH  0x100    // Coordinates range [0, 255]
#define SCREEN_HEIGHT 0x100    // Coordinates range [0, 255]

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xySetupXy(X_PORT_OFFSET, X_PORT_SIZE, Y_PORT_OFFSET, Y_PORT_SIZE);
    xySetupZ(Z_PIN);
    xySetupScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false);

    xyRendererStart();

    for(uint16_t row = 0; row < 8; ++row)
    {
        for(uint16_t column = 0; column < 16; ++column)
        {
            volatile xyShape_t* shape = xyRenderChar(row * 0x10 + column, column * 0x10, 0x8C - row * 0x14);
            if(column == 0) shape->delayUs = 160;
        }
    }

    // Spin
    while(1);
}
