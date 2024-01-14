// String Demo ----------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Example demonstrating how to render strings using the library.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

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

    // Render top paragraph
    // - The string is rendered within the bounds of (0, 128) (lower-left corner) to (256, 256) (upper-right corner).
    // - The block is 16 characters wide ((256 - 0) / 16) and 6 characters tall ((256 - 128) / 20).
    xyRenderString(
        "The X-Y library "
        "can render stri-"
        "ngs like this!\n"
        "\"I'm in the top "
        "paragraph\"\n"
        "----------------", 0x00, 0x80, 0x100, 0x100);

    // Render bottom-left block
    // - The string is rendered within the bounds of (0, 0) (lower-left corner) to (128, 128) (upper-right corner).
    // - The block is 8 characters wide ((128 - 0) / 16) and 6 characters tall ((128 - 0) / 20).
    xyRenderString(
        "Here's  "
        "the bot-"
        "tom left"
        "block!  ", 0x00, 0x00, 0x80, 0x80);

    // Render bottom-right block
    // - The string is rendered within the bounds of (144, 0) (lower-left corner) to (256, 128) (upper-right corner).
    // - The block is 7 characters wide ((256 - 144) / 16) and 6 characters tall ((128 - 0) / 20).
    xyRenderString(
        "And the"
        "bottom "
        "right  "
        "block! ", 0x90, 0x00, 0x100, 0x80);

    // Spin
    while(1);
}
