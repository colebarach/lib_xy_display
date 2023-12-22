// Animation Demo -------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: TODO: Unfinished example.

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

// Frames ---------------------------------------------------------------------------------------------------------------------

#define SIZE_SIN 13
xyPoint_t sin0[SIZE_SIN] =
{
    { 96,  48}, {109,  36}, {121,  25}, {134,  18}, {146,  16}, {159,  18}, {171,  25}, {184,  36},
    {197,  48}, {209,  60}, {222,  71}, {234,  78}, {247,  80}
};

#define SIZE_COS 13
xyPoint_t sin1[SIZE_SIN] =
{
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
};

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
