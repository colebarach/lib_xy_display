// Procedural Model Generation Demo -------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Example program to demonstrate the runtime generation of models. Generates and renders a Hilbert Curve fractal.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

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

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Generate Hilbert Curve
// - Call to populate the given model with a representation of the spacing-filling Hilbert curve.
// - Depth represents number of iterations to perform, (0 => single point, 1 => 'C' shaped curve)
// - Scale represents the length of the smallest conneting line, measured in pixels.
int generateHilbertCurve(volatile xyPoint_t* model, uint16_t modelSize, int depth, int scale);

// Populate Hilbert Curve
// - Call to populate the model with a representation of the Hilbert curve.
// - Requires the first element in the model be defined.
// - Point index must refer to a valid integer.
// - Rotation must be in the domain [0, 3] inclusive, mapping to [0, 90, 180, 270] degrees respectively.
// - Direction must be either 1 or -1.
void populateHilbertCurve(volatile xyPoint_t* model, uint16_t pointCount, uint16_t* pointIndex, int depth, int scale, int rotation, int direction);

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

    // Generate model
    #define MODEL_SIZE 512
    xyPoint_t model[MODEL_SIZE];
    int modelSize = generateHilbertCurve(model, MODEL_SIZE, 4, 16);

    // Render model
    volatile xyShape_t* shape = xyRenderShape(model, modelSize, 0, 0, true);

    while(true);
}

// Function Definitions -------------------------------------------------------------------------------------------------------

int generateHilbertCurve(volatile xyPoint_t* model, uint16_t modelSize, int depth, int scale)
{
    model[0].x = 0;
    model[0].y = 0;

    uint16_t pointIndex = 0;
    populateHilbertCurve(model, modelSize, &pointIndex, depth, scale, 0, 1);

    return pointIndex + 1;
}

void populateHilbertCurve(volatile xyPoint_t* model, uint16_t pointCount, uint16_t* pointIndex, int depth, int scale, int rotation, int direction)
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
    populateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, (rotation + 2 - direction) % 4, -direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x + scale * cosf(M_PI_2 * rotation);
    model[*pointIndex + 1].y = model[*pointIndex].y + scale * sinf(M_PI_2 * rotation);
    ++(*pointIndex);

    // Render subcurve 1
    populateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, rotation, direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x - scale * sinf(M_PI_2 * rotation) * direction;
    model[*pointIndex + 1].y = model[*pointIndex].y + scale * cosf(M_PI_2 * rotation) * direction;
    ++(*pointIndex);

    // Render subcurve 2
    populateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, rotation, direction);

    // Draw connecting line
    if(*pointIndex + 1 >= pointCount) return;
    model[*pointIndex + 1].x = model[*pointIndex].x - scale * cosf(M_PI_2 * rotation);
    model[*pointIndex + 1].y = model[*pointIndex].y - scale * sinf(M_PI_2 * rotation);
    ++(*pointIndex);

    // Render subcurve 3
    populateHilbertCurve(model, pointCount, pointIndex, depth - 1, scale, (rotation + 2 + direction) % 4, -direction);
}
