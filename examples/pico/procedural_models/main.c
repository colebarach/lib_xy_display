// Procedural Model Generation Demo -------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Example program to demonstrate the runtime generation of models.

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

// Functions ------------------------------------------------------------------------------------------------------------------

// Generate Hilbert Curve
// - Call to populate the given model with a representation of the spacing-filling hilbert curve.
// - Depth represents number of iterations to perform, (0 => single point, 1 => 'C' shaped curve)
// - Scale represents the length of the smallest conneting line, measured in pixels.
// - TODO: Doesn't render last point.
// - TODO: Consider using return value for point count.
void generateHilbertCurve(volatile xyPoint_t* model, uint16_t pointCount, uint16_t* pointIndex, int depth, int scale, int rotation, int direction)
{
    // Fractal math:

    // | Rotation | Direction || Subrot 0 | Subdir 0 | Subrot 1 | Subdir 1 | Subrot 2 | Subdir 2 | Subrot 3 | Subdir 3 |
    // |----------|-----------||----------|----------|----------|----------|----------|----------|----------|----------|
    // |    0     |     1     ||    1     |   -1     |    0     |    1     |    0     |    1     |    3     |   -1     |
    // |    1     |     1     ||    2     |   -1     |    1     |    1     |    1     |    1     |    0     |   -1     |
    // |    2     |     1     ||    3     |   -1     |    2     |    1     |    2     |    1     |    1     |   -1     |
    // |    3     |     1     ||    0     |   -1     |    3     |    1     |    3     |    1     |    2     |   -1     |
    // |    0     |    -1     ||    3     |    1     |    0     |   -1     |    0     |   -1     |    1     |    1     |
    // |    1     |    -1     ||    0     |    1     |    1     |   -1     |    1     |   -1     |    2     |    1     |
    // |    2     |    -1     ||    1     |    1     |    2     |   -1     |    2     |   -1     |    3     |    1     |
    // |    3     |    -1     ||    2     |    1     |    3     |   -1     |    3     |   -1     |    0     |    1     |

    // | Rotation | Direction || Line 0 X | Line 0 Y | Line 1 X | Line 1 Y | Line 2 X | Line 2 Y |
    // |----------|-----------||----------|----------|----------|----------|----------|----------|
    // |    0     |     1     || + Scale  |     0    |     0    | + Scale  | - Scale  |     0    |
    // |    0     |    -1     || + Scale  |     0    |     0    | - Scale  | - Scale  |     0    |
    // |    1     |     1     ||     0    | + Scale  | - Scale  |     0    |     0    | - Scale  |
    // |    1     |    -1     ||     0    | + Scale  | + Scale  |     0    |     0    | - Scale  |
    // |    2     |     1     || - Scale  |     0    |     0    | - Scale  | + Scale  |     0    |
    // |    2     |    -1     || - Scale  |     0    |     0    | + Scale  | + Scale  |     0    |
    // |    3     |     1     ||     0    | - Scale  | + Scale  |     0    |     0    | + Scale  |
    // |    3     |    -1     ||     0    | - Scale  | - Scale  |     0    |     0    | + Scale  |

    // Subrotation 0 = (Rotation + 2 - Direction) % 4
    // Subrotation 1 = Rotation
    // Subrotation 2 = Rotation
    // Subrotation 0 = (Rotation + 2 + Direction) % 4

    // Subdirection 0 = -Direction
    // Subdirection 1 = Direction
    // Subdirection 2 = Direction
    // Subdirection 3 = -Direction

    // Line 0 X =  cos(PI/2 * Rotation)
    // Line 0 Y =  sin(PI/2 * Rotation)
    // Line 1 X = -sin(PI/2 * Rotation) * Direction
    // Line 1 Y =  cos(PI/2 * Rotation) * Direction
    // Line 2 X = -cos(PI/2 * Rotation)
    // Line 2 Y = -sin(PI/2 * Rotation)

    // Recursion base case
    if(depth == 0) return;

    // Render subcurve 0
    generateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, (rotation + 2 - direction) % 4, -direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x + scale * cos(M_PI_2 * rotation);
    model[*pointIndex + 1].y = model[*pointIndex].y + scale * sin(M_PI_2 * rotation);
    ++(*pointIndex);

    // Render subcurve 1
    generateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, rotation, direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x - scale * sin(M_PI_2 * rotation) * direction;
    model[*pointIndex + 1].y = model[*pointIndex].y + scale * cos(M_PI_2 * rotation) * direction;
    ++(*pointIndex);

    // Render subcurve 2
    generateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, rotation, direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x - scale * cos(M_PI_2 * rotation);
    model[*pointIndex + 1].y = model[*pointIndex].y - scale * sin(M_PI_2 * rotation);
    ++(*pointIndex);

    // Render subcurve 3
    generateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, (rotation + 2 + direction) % 4, -direction);
}

// void generate

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Start renderer
    // xyRendererInitialize(X_PIN_OFFSET, X_PIN_LENGTH, Y_PIN_OFFSET, Y_PIN_LENGTH, SCREEN_WIDTH, SCREEN_HEIGHT);

    #define MODEL_SIZE 512

    xyPoint_t model[MODEL_SIZE];
    model[0].x = 0;
    model[0].y = 0;

    uint16_t pointIndex = 0;

    // generateHilbertCurve(model, MODEL_SIZE, &pointIndex, 4, 16, 0, 1);

    // xyRendererRenderShape(model, pointIndex, 0, 0);

    while(true);
}




/* OLD CODE

void generateHilbertCurve(volatile xyPoint_t* model, uint16_t pointIndex, uint16_t modelSize, int depth, int scale, int rotation, int direction)
{
    if(depth == 0) return;

    if(rotation == 0)
    {
        if(direction == 0)
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
        }
        else
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
        }
    }
    else if(rotation == 1)
    {
        if(direction == 0)
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
        }
        else
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
        }
    }
    else if(rotation == 2)
    {
        if(direction == 0)
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
        }
        else
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
        }
    }
    else
    {
        if(direction == 0)
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
            XY_CURSOR += scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
        }
        else
        {
            xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
            XY_CURSOR -= scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
            XY_CURSOR -= scale;
            xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
            XY_CURSOR += scale << 8;
            xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
        }
    }
}

*/

