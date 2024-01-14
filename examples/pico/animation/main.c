// Animation Demo -------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Descrption: Render of the "Bad Apple!!" music video, meant to demonstrate how pre-rendered animations may be played by the
// the library.
//
// Sources:
//  - https://youtube.com/watch?v=FtutLA63Cp8 - Original music video
//  - https://github.com/kevinjycui           - Video frames and edge detection algorithm

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

// Pico Library
#include <pico/stdlib.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "models.h"

// I/O & Timing ---------------------------------------------------------------------------------------------------------------

#define X_PORT_OFFSET  0       // X port starts at GPIO 0
#define X_PORT_SIZE    8       // X port spans GPIO 0 to GPIO 7
#define Y_PORT_OFFSET  8       // Y port starts at GPIO 8
#define Y_PORT_SIZE    8       // Y port spans GPIO 8 to GPIO 15
#define Z_PIN          16      // Z output is GPIO 16

#define RC_CONSTANT_US 4       // RC constant of the output filter
#define RC_PIXEL_THRES 1       // Threshold of the cursor's accuracy

#define Z_DELAY_US     20      // Time to wait for z-output update

#define SCREEN_WIDTH   0x100   // Coordinates range [0, 255]
#define SCREEN_HEIGHT  0x100   // Coordinates range [0, 255]

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xySetupXy(X_PORT_OFFSET, X_PORT_SIZE, Y_PORT_OFFSET, Y_PORT_SIZE);
    xySetupZ(Z_PIN);
    xySetupRcTiming(RC_CONSTANT_US, RC_PIXEL_THRES);
    xySetupRgbzDelay(Z_DELAY_US);
    xySetupScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false);

    // Start rendering
    xyRendererStart();

    volatile xyShape_t* frame = xyRenderShape(frames[0], frameSizes[0], 0, 0, true);

    // Time parameter
    uint16_t frameIndex = 0;

    while(true)
    {
        // Update models
        frame->points = frames[frameIndex];
        frame->pointCount = frameSizes[frameIndex];

        // 11 FPS
        sleep_ms(90);
        ++frameIndex;
        if(frameIndex >= FRAME_COUNT) frameIndex = 0;
    }
}
