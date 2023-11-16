// Header
#include "collision.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Object Functions -----------------------------------------------------------------------------------------------------------

bool collideShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroid)
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

bool collideBulletAsteroid(struct bullet_t* bullet, struct asteroid_t* asteroid)
{
    // Check if head of bullet intersects radius of asteroid

    float distanceX = bullet->positionX + bullet->colliderHeadX - asteroid->positionX - asteroid->centerOfMassX;
    float distanceY = bullet->positionY + bullet->colliderHeadX - asteroid->positionY - asteroid->centerOfMassY;

    return (distanceX * distanceX + distanceY * distanceY < asteroid->colliderRadius * asteroid->colliderRadius);
}

// Buffer Functions -----------------------------------------------------------------------------------------------------------

bool collideBufferShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroids, uint16_t asteroidBufferSize)
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

void collideBuffersBulletAsteroid(struct bullet_t* bullets, uint16_t bulletBufferSize, struct asteroid_t* asteroids, uint16_t asteroidBufferSize)
{
    // Compare all bullets and all asteroids for collisions
    for(uint16_t bulletIndex = 0; bulletIndex < bulletBufferSize; ++bulletIndex)
    {
        // Skip inactive bullets
        if(!bullets[bulletIndex].active) continue;

        for(uint16_t asteroidIndex = 0; asteroidIndex < asteroidBufferSize; ++asteroidIndex)
        {
            // Skip inactive asteroids
            if(!asteroids[asteroidIndex].active) continue;

            // Check for hit
            if(collideBulletAsteroid(&bullets[bulletIndex], &asteroids[asteroidIndex]))
            {
                // Remove bullet and split asteroid
                bulletBufferRemove(bullets, bulletBufferSize, bulletIndex);
                asteroidBufferSplit(asteroids, asteroidBufferSize, asteroidIndex);
                continue;
            }
        }
    }
}
