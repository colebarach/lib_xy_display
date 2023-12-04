// Translation Demo -----------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description:

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Pico Standard Library
#include <pico/stdlib.h>

// C Standard Library
#include <math.h>

// I/O ------------------------------------------------------------------------------------------------------------------------

#define X_PIN_OFFSET  0        // X port starts at GPIO 0
#define X_PIN_LENGTH  8        // X port spans GPIO 0 to GPIO 7
#define Y_PIN_OFFSET  8        // Y port starts at GPIO 8
#define Y_PIN_LENGTH  8        // Y port spans GPIO 8 to GPIO 15

#define SCREEN_WIDTH  0x100    // Coordinates range [0, 255]
#define SCREEN_HEIGHT 0x100    // Coordinates range [0, 255]

// Models ---------------------------------------------------------------------------------------------------------------------

// Square Model
// - Note the offset of the model (+8 on all values). When rotating a model, it is important to make sure none of the points
//   ever go below 0, as this will cause them to underflow.
#define SIZE_SQUARE_MODEL 9
xyPoint_t squareModel[SIZE_SQUARE_MODEL] =
{
    {8, 8}, {24, 8}, {40, 8}, {40, 24}, {40, 40}, {24, 40}, {8, 40}, {8, 24}, {8, 8}
};
#define X_CENTER_SQUARE_MODEL 24
#define Y_CENTER_SQUARE_MODEL 24

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
    // Start renderer
    xyRendererInitialize(X_PIN_OFFSET, X_PIN_LENGTH, Y_PIN_OFFSET, Y_PIN_LENGTH, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    // Draw rotating square 1
    xyPoint_t square1Buffer[SIZE_SQUARE_MODEL];
    xyRendererRenderShape(square1Buffer, SIZE_SQUARE_MODEL, 8, 8);

    // Draw rotating square 2
    xyPoint_t square2Buffer[SIZE_SQUARE_MODEL];
    xyRendererRenderShape(square2Buffer, SIZE_SQUARE_MODEL, 200, 8);

    // Draw moving diamond
    volatile xyShape_t* diamond = xyRendererRenderShape(diamondModel, SIZE_DIAMOND_MODEL, 0, 0);

    // Draw scaling coin
    xyPoint_t coinCircleBuffer[SIZE_CIRCLE_MODEL];
    xyPoint_t coinSignBuffer[xyShapeSize16x16Ascii['$']];
    xyRendererRenderShape(coinCircleBuffer, SIZE_CIRCLE_MODEL, 128 - RADIUS_CIRCLE_MODEL, 128 - RADIUS_CIRCLE_MODEL);
    xyRendererRenderShape(coinSignBuffer, xyShapeSize16x16Ascii['$'], 128 - 9, 128 - 12);

    // Animation --------------------------------------------------------------------------------------------------------------

    // Time parameter
    float t = 0;

    while(true)
    {
        // Update rotating square 1
        xyShapeRotate(squareModel, square1Buffer, SIZE_SQUARE_MODEL, X_CENTER_SQUARE_MODEL, Y_CENTER_SQUARE_MODEL, t);

        // Update rotating square 1
        xyShapeRotate(squareModel, square2Buffer, SIZE_SQUARE_MODEL, X_CENTER_SQUARE_MODEL, Y_CENTER_SQUARE_MODEL, -2.0f * t);

        // Update moving diamond
        diamond->positionX = roundf(cos(t) * 96.0f + 120.0f);
        diamond->positionY = roundf(sin(2.0 * t) * 12.0f + 200.0f);

        // Update scaling coin
        xyShapeScale(circleModel, coinCircleBuffer, SIZE_CIRCLE_MODEL, RADIUS_CIRCLE_MODEL, RADIUS_CIRCLE_MODEL, cos(t), 1.0f);
        xyShapeTranslate(xyShape16x16Ascii['$'], coinSignBuffer, xyShapeSize16x16Ascii['$'], 9, 12, 3, 4, 1.5f * cos(t), 1.5f, 0);

        // Short delay
        sleep_ms(1);
        t += 0.00314f;
    }
}
