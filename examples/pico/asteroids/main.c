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

#define SHIP_ACCELERATION_Y       0.2f   // Acceleration of the ship (forward / backward)
#define SHIP_ANGULAR_ACCELERATION 0.01f  // Angular acceleration of the ship (left / right)

#define SHIP_VELOCITY_DRAG        0.95f  // Percentage of the remaining ship velocity after 30ms
#define SHIP_ANGULAR_DRAG         0.95f  // Percentage of the remaining ship angular velocity after 30ms

#define SIZE_ASTEROID_BUFFER      20     // Maximum number of asteroid objects // TODO: Cannot exceed 22 why?

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

#define SIZE_SHIP_MODEL        25        // Max size of all ship models

#define SHIP_CENTER_OF_MASS_X  0x06      // Ship model center of mass (rotation point)
#define SHIP_CENTER_OF_MASS_Y  0x09      // Ship model center of mass (rotation point)

#define SIZE_ASTEROID_MODEL    16        // Size of each asteroid model

// Ship -----------------------------------------------------------------------------------------------------------------------

// Ship Object
// - Object containing all properties related to a ship.
struct ship_t
{
    float positionY;                     // Y position of the ship in pixels.
    float positionX;                     // X position of the ship in pixels.
    float velocityX;                     // X velocity of the ship in pixels per 30ms.
    float velocityY;                     // Y velocity of the ship in pixels per 30ms.
    float rotation;                      // Rotation of the ship in radians.
    float angularVelocity;               // Angular velocity of the ship in radians per 30ms.
    bool  accelerating;                  // Indicates whether the ship is moving forward.

    struct xyPoint modelBuffer[SIZE_SHIP_MODEL];               // Buffer of points to render, contains a translated copy of one
                                                               // of the ship models.
    volatile struct xyShape* model;                            // Handler of the model for the ship.
};

// Initialize Ship
void shipInitialize(struct ship_t* ship, float positionX, float positionY);

// Update Ship
// - Call to update the properties of the ship by one time step.
void shipUpdate(struct ship_t* ship);

// Render Ship
// - Call to update the model of the ship.
void shipRender(struct ship_t* ship);

// Asteroids ------------------------------------------------------------------------------------------------------------------

struct asteroid_t
{
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float rotation;
    float angularVelocity;

    uint16_t centerOfMassX;
    uint16_t centerOfMassY;

    bool active;

    struct xyPoint modelBase[SIZE_ASTEROID_MODEL];
    struct xyPoint modelBuffer[SIZE_ASTEROID_MODEL];

    volatile struct xyShape* model;
};

void asteroidInitialize(struct asteroid_t* asteroid);

void asteroidRender(struct asteroid_t* asteroid);

void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize);

void asteroidBufferInsert(struct asteroid_t* asteroids, uint16_t bufferSize, float positionX, float positionY, uint16_t radius);

// I/O ------------------------------------------------------------------------------------------------------------------------

// Initialize Input
// - Call to setup the inputs
// - Required call before inputGet is called
void inputInitialize();

// Get Input
// - Call to update the movement of the player ship based on current input.
void inputGet(struct ship_t* playerShip);

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // I/O --------------------------------------------------------------------------------------------------------------------

    inputInitialize();

    // Objects ----------------------------------------------------------------------------------------------------------------

    struct ship_t ship;
    shipInitialize(&ship, 128.0f, 128.0f);

    struct asteroid_t asteroids[SIZE_ASTEROID_BUFFER];
    asteroidBufferInitialize(asteroids, SIZE_ASTEROID_BUFFER);

    asteroidBufferInsert(asteroids, SIZE_ASTEROID_BUFFER, 64.0f, 64.0f, 8);

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

void shipInitialize(struct ship_t* ship, float positionX, float positionY)
{
    ship->positionX       = positionX;
    ship->positionY       = positionY;
    ship->velocityX       = 0.0f;
    ship->velocityY       = 0.0f;
    ship->rotation        = 0.0f;
    ship->angularVelocity = 0.0f;
    ship->accelerating    = false;

    // Put ship in the render stack
    ship->model = xyRendererRenderShape(ship->modelBuffer, 0, 0x00, 0x00);
    shipRender(ship);
}

void shipUpdate(struct ship_t* ship)
{
    ship->positionX += ship->velocityX;
    ship->positionY += ship->velocityY;

    ship->velocityX *= SHIP_VELOCITY_DRAG;
    ship->velocityY *= SHIP_VELOCITY_DRAG;

    ship->rotation += ship->angularVelocity;
    if(ship->rotation < 0)       ship->rotation += 2*M_PI;
    if(ship->rotation >= 2*M_PI) ship->rotation -= 2*M_PI;

    ship->angularVelocity *= SHIP_ANGULAR_DRAG;
}

void shipRender(struct ship_t* ship)
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

void asteroidInitialize(struct asteroid_t* asteroid)
{
    asteroid->positionX        = 0.0f;
    asteroid->positionY        = 0.0f;
    asteroid->velocityX        = 0.0f;
    asteroid->velocityY        = 0.0f;
    asteroid->rotation         = 0.0f;
    asteroid->angularVelocity  = 0.0f;
    asteroid->centerOfMassX    = 4;
    asteroid->centerOfMassY    = 4;
    asteroid->active           = false;

    // Put model in the render stack
    asteroid->model = xyRendererRenderShape(asteroid->modelBuffer, 0, 0x00, 0x00);
    asteroid->model->visible = false;
}

void asteroidRender(struct asteroid_t* asteroid)
{
    // Update model position
    asteroid->model->positionX = round(asteroid->positionX);
    asteroid->model->positionY = round(asteroid->positionY);

    // Translate model into buffer
    xyShapeRotate(asteroid->modelBase, asteroid->modelBuffer, SIZE_ASTEROID_MODEL, asteroid->centerOfMassX, asteroid->centerOfMassY, round(asteroid->rotation * 255.0f / (2 * M_PI)));
    asteroid->model->pointCount = SIZE_ASTEROID_MODEL;
}

void asteroidModelGenerate(struct asteroid_t* asteroid, uint16_t radius)
{
    asteroid->centerOfMassX = ceil(radius);
    asteroid->centerOfMassY = ceil(radius);

    for(uint16_t index = 0; index < SIZE_ASTEROID_MODEL; ++index)
    {
        float theta = index * 2 * M_PI / SIZE_ASTEROID_MODEL;
        asteroid->modelBase[index].x = round(radius * cos(theta) + asteroid->centerOfMassX);
        asteroid->modelBase[index].y = round(radius * sin(theta) + asteroid->centerOfMassY);
    }

    asteroidRender(asteroid);
}

void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        asteroidInitialize(&asteroids[index]);
    }
}

void asteroidBufferInsert(struct asteroid_t* asteroids, uint16_t bufferSize, float positionX, float positionY, uint16_t radius)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(!asteroids[index].active)
        {
            asteroids[index].active = true;
            asteroids[index].positionX = positionX;
            asteroids[index].positionY = positionY;

            asteroidModelGenerate(&asteroids[index], radius);

            asteroids[index].model->visible = true;

            return;
        }
    }

    // TODO: Buffer is full, what to do here?
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

void inputGet(struct ship_t* playerShip)
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
        playerShip->angularVelocity += SHIP_ANGULAR_ACCELERATION;
    }
    else if(!gpio_get(BUTTON_PIN_RIGHT))
    {
        // Turn right
        playerShip->angularVelocity -= SHIP_ANGULAR_ACCELERATION;
    }
}
