// ASCII Table Demo -----------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Draws a static 'ASCII' table on the screen, demonstrating the method of drawing characters and the available
//   symbols.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// I/O ------------------------------------------------------------------------------------------------------------------------

#define X_PIN_OFFSET  0        // X port starts at GPIO 0
#define X_PIN_LENGTH  8        // X port spans GPIO 0 to GPIO 7
#define Y_PIN_OFFSET  8        // Y port starts at GPIO 8
#define Y_PIN_LENGTH  8        // Y port spans GPIO 8 to GPIO 15

#define SCREEN_WIDTH  0x100    // Coordinates range [0, 255]
#define SCREEN_HEIGHT 0x100    // Coordinates range [0, 255]

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Start renderer
    xyRendererInitialize(X_PIN_OFFSET, X_PIN_LENGTH, Y_PIN_OFFSET, Y_PIN_LENGTH, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Draw characters
    for(uint16_t index = 0; index < 0x80; ++index)
    {
        xyRendererRenderChar(index, (0x10 * index) % 0x100, 0x8C - 0x14 * (index / 0x10));
    }

    // Spin
    while(1);
}
