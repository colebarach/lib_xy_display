// Header
#include "collision.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Object Functions -----------------------------------------------------------------------------------------------------------

bool collideShipAsteroid(ship_t* ship, asteroid_t* asteroid)
{
    float distanceX = ship->colliderGunX + ship->positionX - asteroid->centerOfMassX - asteroid->positionX;
    float distanceY = ship->colliderGunY + ship->positionY - asteroid->centerOfMassY - asteroid->positionY;

    if(distanceX * distanceX + distanceY * distanceY < asteroid->colliderRadius * asteroid->colliderRadius) return true;

    distanceX = ship->colliderBottomLeftX + ship->positionX - asteroid->centerOfMassX - asteroid->positionX;
    distanceY = ship->colliderBottomLeftY + ship->positionY - asteroid->centerOfMassY - asteroid->positionY;

    if(distanceX * distanceX + distanceY * distanceY < asteroid->colliderRadius * asteroid->colliderRadius) return true;

    distanceX = ship->colliderBottomRightX + ship->positionX - asteroid->centerOfMassX - asteroid->positionX;
    distanceY = ship->colliderBottomRightY + ship->positionY - asteroid->centerOfMassY - asteroid->positionY;

    if(distanceX * distanceX + distanceY * distanceY < asteroid->colliderRadius * asteroid->colliderRadius) return true;

    return false;
}

bool collideBulletAsteroid(bullet_t* bullet, asteroid_t* asteroid)
{
    // Check if head of bullet intersects radius of asteroid

    float distanceX = bullet->positionX + bullet->colliderHeadX - asteroid->positionX - asteroid->centerOfMassX;
    float distanceY = bullet->positionY + bullet->colliderHeadX - asteroid->positionY - asteroid->centerOfMassY;

    return (distanceX * distanceX + distanceY * distanceY < asteroid->colliderRadius * asteroid->colliderRadius);
}

// Buffer Functions -----------------------------------------------------------------------------------------------------------

bool collideBufferShipAsteroid(ship_t* ship, asteroid_t* asteroids, uint16_t asteroidBufferSize, int16_t* asteroidIndex)
{
    for(uint16_t index = 0; index < asteroidBufferSize; ++index)
    {
        if(!asteroids[index].active) continue;

        if(collideShipAsteroid(ship, &asteroids[index]))
        {
            asteroidBufferRemove(asteroids, asteroidBufferSize, index);
            return true;
        }
    }

    return false;
}

bool collideBuffersBulletAsteroid(bullet_t* bullets, uint16_t bulletBufferSize, asteroid_t* asteroids, uint16_t asteroidBufferSize, int16_t* bulletIndex, int16_t* asteroidIndex)
{
    // Compare all bullets and all asteroids for collisions
    for(uint16_t bulletScanIndex = *bulletIndex; bulletScanIndex < bulletBufferSize; ++bulletScanIndex)
    {
        // Skip inactive bullets
        if(!bullets[bulletScanIndex].active) continue;

        for(uint16_t asteroidScanIndex = *asteroidIndex; asteroidScanIndex < asteroidBufferSize; ++asteroidScanIndex)
        {
            // Skip inactive asteroids
            if(!asteroids[asteroidScanIndex].active) continue;

            // Check for hit
            if(collideBulletAsteroid(&bullets[bulletScanIndex], &asteroids[asteroidScanIndex]))
            {
                // Update output and return
                *bulletIndex   = bulletScanIndex;
                *asteroidIndex = asteroidScanIndex;

                return true;
            }
        }
    }

    return false;
}
