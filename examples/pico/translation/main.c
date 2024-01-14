// Translation Demo -----------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Example program to demonstrate the translation of models.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>
#include <xy_shapes.h>

// Pico Standard Library
#include <pico/stdlib.h>

// C Standard Library
#include <math.h>

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

// Models ---------------------------------------------------------------------------------------------------------------------
// - Data for each shape to render. Each array consists of coordinate pairs to render in the specified order.

// Square Model
#define SIZE_SQUARE_MODEL 9
xyPoint_t squareModel[SIZE_SQUARE_MODEL] =
{
    {0, 0}, {16, 0}, {32, 0}, {32, 16}, {32, 32}, {16, 32}, {0, 32}, {0, 16}, {0, 0}
};
#define X_CENTER_SQUARE_MODEL 16
#define Y_CENTER_SQUARE_MODEL 16

// Diamond Model
#define SIZE_DIAMOND_MODEL 9
xyPoint_t diamondModel[SIZE_DIAMOND_MODEL] =
{
    {8, 0}, {12, 4}, {16, 8}, {12, 12}, {8, 16}, {4, 12}, {0, 8}, {4, 4}, {8, 0}
};

// Circle Model
// - The circle is generated procedurally.
#define SIZE_CIRCLE_MODEL   17
#define RADIUS_CIRCLE_MODEL 32.0f

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

    // Generate circle model
    xyPoint_t circleModel[SIZE_CIRCLE_MODEL];
    for(uint16_t index = 0; index < SIZE_CIRCLE_MODEL - 1; ++index)
    {
        float theta = 2.0f * M_PI * index / (SIZE_CIRCLE_MODEL - 1);

        circleModel[index].x = RADIUS_CIRCLE_MODEL * cosf(theta) + RADIUS_CIRCLE_MODEL;
        circleModel[index].y = RADIUS_CIRCLE_MODEL * sinf(theta) + RADIUS_CIRCLE_MODEL;
    }
    circleModel[SIZE_CIRCLE_MODEL - 1] = circleModel[0];

    // Rendering --------------------------------------------------------------------------------------------------------------

    // Render rotating square 1
    // - The shape is rotating, therefore a buffer is required. A translated copy of the original model is copied into the
    //   buffer, which is what is actually rendered. The result of the render function is disregarded, as this shaped doesn't
    //   need moved.
    xyPoint_t square1Buffer[SIZE_SQUARE_MODEL];
    xyRenderShape(square1Buffer, SIZE_SQUARE_MODEL, 8, 8, true);

    // Render rotating square 2
    xyPoint_t square2Buffer[SIZE_SQUARE_MODEL];
    xyRenderShape(square2Buffer, SIZE_SQUARE_MODEL, 200, 8, true);

    // Render moving diamond
    // - This shape is not being translated, so no buffer is needed. The shape handler ('diamond') is stored so it may be
    //   used to manipulate the position.
    volatile xyShape_t* diamond = xyRenderShape(diamondModel, SIZE_DIAMOND_MODEL, 0, 0, true);

    // Render scaling coin
    // - The coin consists of 2 shapes, each of which are moved in unison. Because both models are being translated, 2 buffers
    //   are required. The circle buffer contains a copy of the procedurally generated circle model. The sign buffer contains a
    //   copy of the dollar sign symbol ('$') after the same translation is applied.
    xyPoint_t coinCircleBuffer[SIZE_CIRCLE_MODEL];
    xyPoint_t coinSignBuffer[xyShapeSize16x16Ascii['$']];
    xyRenderShape(coinCircleBuffer, SIZE_CIRCLE_MODEL, 128 - RADIUS_CIRCLE_MODEL, 128 - RADIUS_CIRCLE_MODEL, true);
    xyRenderShape(coinSignBuffer, xyShapeSize16x16Ascii['$'], 128 - 9, 128 - 12, true);

    // Animation --------------------------------------------------------------------------------------------------------------

    // Time parameter
    float time = 0;

    while(true)
    {
        // Update rotating square 1
        // - Copies the translated square model into its buffer.
        xyShapeRotate(squareModel, square1Buffer, SIZE_SQUARE_MODEL, X_CENTER_SQUARE_MODEL, Y_CENTER_SQUARE_MODEL, time);

        // Update rotating square 1
        xyShapeRotate(squareModel, square2Buffer, SIZE_SQUARE_MODEL, X_CENTER_SQUARE_MODEL, Y_CENTER_SQUARE_MODEL, -2.0f * time);

        // Update moving diamond
        // - Updating the position here moves the model on-screen, as they operate on shared memory.
        diamond->positionX = roundf(cos(time) * 96.0f + 120.0f);
        diamond->positionY = roundf(sin(2.0 * time) * 12.0f + 200.0f);

        // Update scaling coin
        // - Scales both models in unison. The source model of the sign comes from the built-in ASCII table.
        xyShapeScale(circleModel, coinCircleBuffer, SIZE_CIRCLE_MODEL, RADIUS_CIRCLE_MODEL, RADIUS_CIRCLE_MODEL, cos(time), 1.0f);
        xyShapeTranslate(xyShape16x16Ascii['$'], coinSignBuffer, xyShapeSize16x16Ascii['$'], 9, 12, 3, 4, 1.5f * cos(time), 1.5f, 0);

        // Short delay
        sleep_ms(1);
        time += 0.00314f;
    }
}
