// ASCII Table Demo -----------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Writes the text 'Hello, World!' in the center of the screen. Used to test hardware setup and output quality.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

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

    xyRenderString("HELLO,WORLD!", xyScreenWidth() / 2 - 0x30, xyScreenHeight() / 2 - 0x14, xyScreenWidth() / 2 + 0x30, xyScreenHeight() / 2 + 0x14);

    // Spin
    while(1);
}
