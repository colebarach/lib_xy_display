// Asteroids Programming Example ----------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Implementation of the videogame 'asteroids' using the X-Y rendering library.
//
// To do:

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Pico Standard Library
#include <pico/stdlib.h>

// C Standard Libraries
#include <math.h>

// Inputs ---------------------------------------------------------------------------------------------------------------------

#define BUTTON_PIN_UP    18              // GPIO pin number of the up button
#define BUTTON_PIN_LEFT  21              // GPIO pin number of the left button
#define BUTTON_PIN_RIGHT 20              // GPIO pin number of the right button
#define BUTTON_PIN_SHOOT 19              // GPIO pin number of the down button

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define SHIP_ACCELERATION_Y       0.1f   // Acceleration of the ship (forward / backward)
#define SHIP_ANGULAR_ACCELERATION 0.01f  // Angular acceleration of the ship (left / right)

#define SHIP_VELOCITY_DRAG        0.95f  // Percentage of the remaining ship velocity after 30ms
#define SHIP_ANGULAR_DRAG         0.95f  // Percentage of the remaining ship angular velocity after 30ms

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_SHIP_MODEL_IDLE 17
struct xyPoint shipModelIdle[SIZE_SHIP_MODEL_IDLE] =
{
    {0x00, 0x00}, {0x01, 0x03}, {0x03, 0x03}, {0x05, 0x03}, {0x07, 0x03}, {0x03, 0x03}, {0x01, 0x03}, {0x03, 0x09},
    {0x05, 0x0F}, {0x06, 0x12}, {0x07, 0x0F}, {0x09, 0x09}, {0x0B, 0x03}, {0x09, 0x03}, {0x07, 0x03}, {0x0B, 0x03},
    {0x0C, 0x00}
};

#define SIZE_SHIP_MODEL_ACCELERATING 25
struct xyPoint shipModelAccelerating[SIZE_SHIP_MODEL_ACCELERATING] =
{
    {0x00, 0x00}, {0x01, 0x03}, {0x03, 0x03}, {0x06, 0x00}, {0x03, 0x03}, {0x05, 0x03}, {0x06, 0x02}, {0x05, 0x03}, 
    {0x07, 0x03}, {0x03, 0x03}, {0x01, 0x03}, {0x03, 0x09}, {0x05, 0x0F}, {0x06, 0x12}, {0x07, 0x0F}, {0x09, 0x09},
    {0x0B, 0x03}, {0x09, 0x03}, {0x06, 0x00}, {0x09, 0x03}, {0x07, 0x03}, {0x06, 0x02}, {0x07, 0x03}, {0x0B, 0x03},
    {0x0C, 0x00}
};

#define SIZE_SHIP_POINT_BUFFER 25        // Max size of all ship models

#define SHIP_CENTER_OF_MASS_X  0x06      // Ship model center of mass (rotation point)
#define SHIP_CENTER_OF_MASS_Y  0x09      // Ship model center of mass (rotation point)

// Ship -----------------------------------------------------------------------------------------------------------------------

// Ship Object
// - Object containing all properties related to a ship.
struct shipObject
{
    float positionY;                     // Y position of the ship in pixels.
    float positionX;                     // X position of the ship in pixels.
    float velocityX;                     // X velocity of the ship in pixels per 30ms.
    float velocityY;                     // Y velocity of the ship in pixels per 30ms.
    float rotation;                      // Rotation of the ship in radians.
    float anglularVelocity;              // Angular velocity of the ship in radians per 30ms.
    bool  accelerating;                  // Indicates whether the ship is moving forward.

    struct xyPoint modelBuffer[SIZE_SHIP_POINT_BUFFER];        // Buffer of points to render, contains a translated copy of one
                                                               // of the ship models.
    volatile struct xyShape* model;                            // Handler of the model for the ship.
};

// Update Ship
// - Call to update the properties of the ship by one time step.
void shipUpdate(struct shipObject* ship);

// Render Ship
// - Call to update the model of the ship.
void shipRender(struct shipObject* ship);

// Asteroids ------------------------------------------------------------------------------------------------------------------

// I/O ------------------------------------------------------------------------------------------------------------------------

// Initialize Input
// - Call to setup the inputs
// - Required call before inputGet is called
void inputInitialize();

// Get Input
// - Call to update the movement of the player ship based on current input.
void inputGet(struct shipObject* playerShip);

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // I/O --------------------------------------------------------------------------------------------------------------------

    inputInitialize();

    // Objects ----------------------------------------------------------------------------------------------------------------

    struct shipObject ship =
    {
        .positionX        = 128.0f,
        .positionY        = 128.0f,
        .velocityX        = 0.0f,
        .velocityY        = 0.0f,
        .rotation         = 0.0f,
        .anglularVelocity = 0.0f,
        .accelerating     = false
    };

    // Rendering --------------------------------------------------------------------------------------------------------------
    
    // Put ship in the render stack
    ship.model = xyRendererRenderShape(xyShapeNull, XY_SHAPE_SIZE_NULL, 0x00, 0x00);
    shipRender(&ship);

    // Event Loop -------------------------------------------------------------------------------------------------------------

    while(true)
    {
        shipUpdate(&ship);

        shipRender(&ship);

        inputGet(&ship);

        // Event loop period
        sleep_ms(30);
    }
}

// Function Definitions -------------------------------------------------------------------------------------------------------

void shipUpdate(struct shipObject* ship)
{
    ship->positionX += ship->velocityX;
    ship->positionY += ship->velocityY;

    ship->velocityX *= SHIP_VELOCITY_DRAG;
    ship->velocityY *= SHIP_VELOCITY_DRAG;

    ship->rotation += ship->anglularVelocity;
    if(ship->rotation < 0)       ship->rotation += 2*M_PI;
    if(ship->rotation >= 2*M_PI) ship->rotation -= 2*M_PI;

    ship->anglularVelocity *= SHIP_ANGULAR_DRAG;
}

void shipRender(struct shipObject* ship)
{
    // Update model position
    ship->model->positionX = round(ship->positionX);
    ship->model->positionY = round(ship->positionY);

    // Determine which model to render
    if(ship->accelerating)
    {
        // Translate model into buffer
        xyShapeRotate(shipModelAccelerating, ship->modelBuffer, SIZE_SHIP_MODEL_ACCELERATING, SHIP_CENTER_OF_MASS_X, SHIP_CENTER_OF_MASS_Y, round(ship->rotation * 255.0f / (2 * M_PI)));
        ship->model->pointCount = SIZE_SHIP_MODEL_ACCELERATING;
    }
    else
    {
        // Translate model into buffer
        xyShapeRotate(shipModelIdle, ship->modelBuffer, SIZE_SHIP_MODEL_IDLE, SHIP_CENTER_OF_MASS_X, SHIP_CENTER_OF_MASS_Y, round(ship->rotation * 255.0f / (2 * M_PI)));
        ship->model->pointCount = SIZE_SHIP_MODEL_IDLE;
    }
}

void inputInitialize()
{
    gpio_init(BUTTON_PIN_UP);
    gpio_set_dir(BUTTON_PIN_UP, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_UP);

    gpio_init(BUTTON_PIN_LEFT);
    gpio_set_dir(BUTTON_PIN_LEFT, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_LEFT);

    gpio_init(BUTTON_PIN_RIGHT);
    gpio_set_dir(BUTTON_PIN_RIGHT, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_RIGHT);

    gpio_init(BUTTON_PIN_SHOOT);
    gpio_set_dir(BUTTON_PIN_SHOOT, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_SHOOT);
}

void inputGet(struct shipObject* playerShip)
{
    // Get vertical input
    if(!gpio_get(BUTTON_PIN_UP))
    {
        // Move forward
        playerShip->velocityX -= SHIP_ACCELERATION_Y * sin(playerShip->rotation);
        playerShip->velocityY += SHIP_ACCELERATION_Y * cos(playerShip->rotation);
        playerShip->accelerating = true;
    }
    else
    {
        playerShip->accelerating = false;
    }

    // Get horizontal input
    if(!gpio_get(BUTTON_PIN_LEFT))
    {
        // Turn left
        playerShip->anglularVelocity += SHIP_ANGULAR_ACCELERATION;
    }
    else if(!gpio_get(BUTTON_PIN_RIGHT))
    {
        // Turn right
        playerShip->anglularVelocity -= SHIP_ANGULAR_ACCELERATION;
    }
}
