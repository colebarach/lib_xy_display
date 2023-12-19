// Animation Demo -------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Example program to demonstrate the translation of models.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

// I/O ------------------------------------------------------------------------------------------------------------------------

#define X_PIN_OFFSET  0        // X port starts at GPIO 0
#define X_PIN_LENGTH  8        // X port spans GPIO 0 to GPIO 7
#define Y_PIN_OFFSET  8        // Y port starts at GPIO 8
#define Y_PIN_LENGTH  8        // Y port spans GPIO 8 to GPIO 15

#define SCREEN_WIDTH  0x100    // Coordinates range [0, 255]
#define SCREEN_HEIGHT 0x100    // Coordinates range [0, 255]

// Models ---------------------------------------------------------------------------------------------------------------------



// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize library


    // Time parameter
    uint16_t frameIndex = 0;

    while(true)
    {


        sleep_ms(30); // 30 FPS
        ++frameIndex;
    }
}
