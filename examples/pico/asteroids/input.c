// Header
#include "input.h"

// Function Definitions -------------------------------------------------------------------------------------------------------

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

void inputGet(ship_t* playerShip, bullet_t* bulletBuffer, uint16_t bulletBufferSize)
{
    // Get vertical input
    if(!gpio_get(BUTTON_PIN_UP))
    {
        // Move forward
        playerShip->velocityX += SHIP_ACCELERATION_Y * cosf(playerShip->rotation);
        playerShip->velocityY += SHIP_ACCELERATION_Y * sinf(playerShip->rotation);
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

    // Get shoot input
    if(!gpio_get(BUTTON_PIN_SHOOT))
    {
        if(playerShip->reloaded)
        {
            playerShip->reloaded = false;
            bulletBufferSpawn(bulletBuffer, bulletBufferSize, playerShip->colliderGunX + playerShip->positionX, playerShip->colliderGunY + playerShip->positionY, playerShip->rotation, BULLET_VELOCITY);
        }
    }
    else
    {
        playerShip->reloaded = true;
    }
}
