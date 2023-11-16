// Asteroids Programming Example ----------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Implementation of the videogame 'asteroids' using the X-Y rendering library.
//
// To do:
// - Total number of models in buffer cannot exceed 23, why?
// - The insert functions are getting complex, should there be a dedicated 'bulletCreate' function?
// - Give player invincibility frames
// - Asteroids clipping offscreen can only be hit from one side

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "collision.h"

// Inputs ---------------------------------------------------------------------------------------------------------------------

#define BUTTON_PIN_UP    16              // GPIO pin number of the up button.
#define BUTTON_PIN_LEFT  18              // GPIO pin number of the left button.
#define BUTTON_PIN_RIGHT 19              // GPIO pin number of the right button.
#define BUTTON_PIN_SHOOT 17              // GPIO pin number of the down button.

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define SIZE_BULLET_BUFFER        8      // Maximum number of bullet objects.
#define SIZE_ASTEROID_BUFFER      12     // Maximum number of asteroid objects.

#define SHIP_DEFAULT_LIFE_COUNT   4      // Number of starting lives for the ship.
#define ASTEROID_SPAWN_COUNT      8      // Number of asteroids to spawn in a wave.

// I/O ------------------------------------------------------------------------------------------------------------------------

// Initialize Input
// - Call to setup the inputs
// - Required call before inputGet is called
void inputInitialize();

// Get Input
// - Call to update the movement of the player ship based on current input.
void inputGet(struct ship_t* playerShip, struct bullet_t* bulletBuffer, uint16_t bulletBufferSize);

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // I/O --------------------------------------------------------------------------------------------------------------------

    inputInitialize();

    // Play Loop --------------------------------------------------------------------------------------------------------------

    while(true)
    {
        // Game Data ----------------------------------------------------------------------------------------------------------

        int8_t asteroidSpeed = 1;
        int8_t playerLives   = SHIP_DEFAULT_LIFE_COUNT;

        // Objects ------------------------------------------------------------------------------------------------------------

        struct ship_t ship;
        shipInitialize(&ship, xyWidth() / 2.0f - SHIP_CENTER_OF_MASS_X, xyHeight() / 2.0f - SHIP_CENTER_OF_MASS_Y);

        struct bullet_t bullets[SIZE_BULLET_BUFFER];
        bulletBufferInitialize(bullets, SIZE_BULLET_BUFFER);

        struct asteroid_t asteroids[SIZE_ASTEROID_BUFFER];
        asteroidBufferInitialize(asteroids, SIZE_ASTEROID_BUFFER);

        // Spawn initial asteroids
        for(uint16_t index = 0; index < ASTEROID_SPAWN_COUNT; ++index)
        {
            asteroidBufferSpawn(asteroids, SIZE_ASTEROID_BUFFER, -1, -1, 0.0f, xyWidth(), 0.0f, xyHeight());
        }

        // Event Loop ---------------------------------------------------------------------------------------------------------

        while(true)
        {
            // Get input
            inputGet(&ship, bullets, SIZE_BULLET_BUFFER);

            // Update objects
            shipUpdate(&ship);
            bulletBufferUpdate(bullets, SIZE_BULLET_BUFFER);
            asteroidBufferUpdate(asteroids, SIZE_ASTEROID_BUFFER);

            // Check collision
            collideBuffersBulletAsteroid(bullets, SIZE_BULLET_BUFFER, asteroids, SIZE_ASTEROID_BUFFER);
            bool playerHit = collideBufferShipAsteroid(&ship, asteroids, SIZE_ASTEROID_BUFFER);

            // Check player lives
            if(playerHit)
            {
                --playerLives;

                // Reset game if out of lives
                if(playerLives < 0) break;

                shipRespawn(&ship);
            }

            // Check for no remaining asteroids
            if(asteroidBufferCountActive(asteroids, SIZE_ASTEROID_BUFFER) == 0)
            {
                for(uint16_t index = 0; index < ASTEROID_SPAWN_COUNT; ++index)
                {
                    if(asteroidSpeed < 8) ++asteroidSpeed;
                    asteroidBufferSpawn(asteroids, SIZE_ASTEROID_BUFFER, -1, asteroidSpeed, 0.0f, xyWidth(), 0.0f, xyHeight());
                }
            }

            // Render objects
            shipRender(&ship);
            bulletBufferRender(bullets, SIZE_BULLET_BUFFER);
            asteroidBufferRender(asteroids, SIZE_ASTEROID_BUFFER);

            // Event loop period
            sleep_ms(30);
        }

        // Clear the render stack for reset
        xyRendererClearStack();
    }
}

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

void inputGet(struct ship_t* playerShip, struct bullet_t* bulletBuffer, uint16_t bulletBufferSize)
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
