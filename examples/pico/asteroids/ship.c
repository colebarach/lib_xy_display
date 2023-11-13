// Header
#include "ship.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Models ---------------------------------------------------------------------------------------------------------------------

struct xyPoint shipModelIdle[SIZE_SHIP_MODEL_IDLE] =
{
    {0x00, 0x00}, {0x03, 0x01}, {0x03, 0x03}, {0x03, 0x05}, {0x03, 0x07}, {0x03, 0x03}, {0x03, 0x01}, {0x09, 0x03},
    {0x0F, 0x05}, {0x12, 0x06}, {0x0F, 0x07}, {0x09, 0x09}, {0x03, 0x0B}, {0x03, 0x09}, {0x03, 0x07}, {0x03, 0x0B},
    {0x00, 0x0C}
};

struct xyPoint shipModelAccelerating[SIZE_SHIP_MODEL_ACCELERATING] =
{
    {0x00, 0x00}, {0x03, 0x01}, {0x03, 0x03}, {0x00, 0x06}, {0x03, 0x03}, {0x03, 0x05}, {0x02, 0x06}, {0x03, 0x05},
    {0x03, 0x07}, {0x03, 0x03}, {0x03, 0x01}, {0x09, 0x03}, {0x0F, 0x05}, {0x12, 0x06}, {0x0F, 0x07}, {0x09, 0x09},
    {0x03, 0x0B}, {0x03, 0x09}, {0x00, 0x06}, {0x03, 0x09}, {0x03, 0x07}, {0x02, 0x06}, {0x03, 0x07}, {0x03, 0x0B},
    {0x00, 0x0C}
};

// Functions ------------------------------------------------------------------------------------------------------------------

void shipInitialize(struct ship_t* ship, float positionX, float positionY)
{
    ship->lives           = SHIP_DEFAULT_LIFE_COUNT;

    ship->positionX       = positionX;
    ship->positionY       = positionY;
    ship->velocityX       = 0.0f;
    ship->velocityY       = 0.0f;
    ship->rotation        = 0.0f;
    ship->angularVelocity = 0.0f;
    ship->accelerating    = false;
    ship->reloaded        = true;

    // Initialize remaining parameters
    shipUpdate(ship);

    // Put ship in the render stack
    ship->model = xyRendererRenderShape(ship->modelBuffer, 0, 0x00, 0x00);
    shipRender(ship);
}

void shipUpdate(struct ship_t* ship)
{
    ship->positionX += ship->velocityX;
    ship->positionY += ship->velocityY;

    if(ship->positionX < 0.0f)    ship->positionX += 256.0f;
    if(ship->positionX >= 256.0f) ship->positionX -= 256.0f;
    if(ship->positionY < 0.0f)    ship->positionY += 256.0f;
    if(ship->positionY >= 256.0f) ship->positionY -= 256.0f;

    ship->velocityX *= SHIP_VELOCITY_DRAG;
    ship->velocityY *= SHIP_VELOCITY_DRAG;

    ship->rotation += ship->angularVelocity;
    if(ship->rotation < 0)       ship->rotation += 2*M_PI;
    if(ship->rotation >= 2*M_PI) ship->rotation -= 2*M_PI;

    ship->angularVelocity *= SHIP_ANGULAR_DRAG;

    ship->colliderGunX          = (SHIP_COLLIDER_GUN_X          - SHIP_CENTER_OF_MASS_X) * cosf(ship->rotation) - (SHIP_COLLIDER_GUN_Y         - SHIP_CENTER_OF_MASS_Y) * sinf(ship->rotation) + SHIP_CENTER_OF_MASS_X;
    ship->colliderGunY          = (SHIP_COLLIDER_GUN_X          - SHIP_CENTER_OF_MASS_X) * sinf(ship->rotation) + (SHIP_COLLIDER_GUN_Y         - SHIP_CENTER_OF_MASS_Y) * cosf(ship->rotation) + SHIP_CENTER_OF_MASS_Y;
    ship->colliderBottomLeftX   = (SHIP_COLLIDER_BOTTOM_LEFT_X  - SHIP_CENTER_OF_MASS_X) * cosf(ship->rotation) - (SHIP_COLLIDER_BOTTOM_LEFT_Y  - SHIP_CENTER_OF_MASS_Y) * sinf(ship->rotation) + SHIP_CENTER_OF_MASS_X;
    ship->colliderBottomLeftY   = (SHIP_COLLIDER_BOTTOM_LEFT_X  - SHIP_CENTER_OF_MASS_X) * sinf(ship->rotation) + (SHIP_COLLIDER_BOTTOM_LEFT_Y  - SHIP_CENTER_OF_MASS_Y) * cosf(ship->rotation) + SHIP_CENTER_OF_MASS_Y;
    ship->colliderBottomRightX  = (SHIP_COLLIDER_BOTTOM_RIGHT_X - SHIP_CENTER_OF_MASS_X) * cosf(ship->rotation) - (SHIP_COLLIDER_BOTTOM_RIGHT_Y - SHIP_CENTER_OF_MASS_Y) * sinf(ship->rotation) + SHIP_CENTER_OF_MASS_X;
    ship->colliderBottomRightY  = (SHIP_COLLIDER_BOTTOM_RIGHT_X - SHIP_CENTER_OF_MASS_X) * sinf(ship->rotation) + (SHIP_COLLIDER_BOTTOM_RIGHT_Y - SHIP_CENTER_OF_MASS_Y) * cosf(ship->rotation) + SHIP_CENTER_OF_MASS_Y;
}

void shipRender(struct ship_t* ship)
{
    // Update model position
    ship->model->positionX = roundf(ship->positionX);
    ship->model->positionY = roundf(ship->positionY);

    // Determine which model to render
    if(ship->accelerating)
    {
        // Translate model into buffer
        xyShapeRotate(shipModelAccelerating, ship->modelBuffer, SIZE_SHIP_MODEL_ACCELERATING, SHIP_CENTER_OF_MASS_X, SHIP_CENTER_OF_MASS_Y, roundf(ship->rotation * 255.0f / (2 * M_PI)));
        ship->model->pointCount = SIZE_SHIP_MODEL_ACCELERATING;
    }
    else
    {
        // Translate model into buffer
        xyShapeRotate(shipModelIdle, ship->modelBuffer, SIZE_SHIP_MODEL_IDLE, SHIP_CENTER_OF_MASS_X, SHIP_CENTER_OF_MASS_Y, roundf(ship->rotation * 255.0f / (2 * M_PI)));
        ship->model->pointCount = SIZE_SHIP_MODEL_IDLE;
    }
}

void shipRespawn(struct ship_t* ship)
{
    ship->positionX       = 128.0f - SHIP_CENTER_OF_MASS_X;
    ship->positionY       = 128.0f - SHIP_CENTER_OF_MASS_Y;
    ship->velocityX       = 0.0f;
    ship->velocityY       = 0.0f;
    ship->rotation        = 0.0f;
    ship->angularVelocity = 0.0f;
    ship->accelerating    = false;
    ship->reloaded        = true;

    // Reset remaining parameters
    shipUpdate(ship);
}
