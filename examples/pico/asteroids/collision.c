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
    for(uint16_t bulletIndex = 0; bulletIndex < bulletBufferSize; ++bulletIndex)
    {
        if(!bullets[bulletIndex].active) continue;

        for(uint16_t asteroidIndex = 0; asteroidIndex < asteroidBufferSize; ++asteroidIndex)
        {
            if(!asteroids[asteroidIndex].active) continue;

            if(collideBulletAsteroid(&bullets[bulletIndex], &asteroids[asteroidIndex]))
            {
                bulletBufferRemove(bullets, bulletBufferSize, bulletIndex);

                // Check asteroid size
                if(asteroids[asteroidIndex].colliderRadius >= 8)
                {
                    // Split large asteroids
                    float parentRadius    = asteroids[asteroidIndex].colliderRadius;
                    float parentPositionX = asteroids[asteroidIndex].positionX;
                    float parentPositionY = asteroids[asteroidIndex].positionY;
                    float parentVelocityX = asteroids[asteroidIndex].velocityX;
                    float parentVelocityY = asteroids[asteroidIndex].velocityY;

                    asteroidBufferRemove(asteroids, asteroidBufferSize, asteroidIndex);

                    int16_t child0 = asteroidBufferInsert(asteroids, asteroidBufferSize, parentPositionX, parentPositionY, parentRadius - 4);
                    int16_t child1 = asteroidBufferInsert(asteroids, asteroidBufferSize, parentPositionX, parentPositionY, parentRadius - 4);

                    if(child0 != -1)
                    {
                        float angle = (get_rand_32() % 16) / 16.0f * (ASTEROID_SPLIT_ANGLE_MAX - ASTEROID_SPLIT_ANGLE_MIN) + ASTEROID_SPLIT_ANGLE_MIN;
                        asteroids[child0].velocityX = ASTEROID_SPLIT_SPEEDUP * (parentVelocityX * cosf(angle) - parentVelocityY * sinf(angle));
                        asteroids[child0].velocityY = ASTEROID_SPLIT_SPEEDUP * (parentVelocityX * sinf(angle) + parentVelocityY * cosf(angle));
                        asteroids[child0].angularVelocity = (get_rand_32() % 16) / 64.0f;
                    }
                    if(child1 != -1)
                    {
                        float angle = -(get_rand_32() % 16) / 16.0f * (ASTEROID_SPLIT_ANGLE_MAX - ASTEROID_SPLIT_ANGLE_MIN) - ASTEROID_SPLIT_ANGLE_MIN;
                        asteroids[child1].velocityX = ASTEROID_SPLIT_SPEEDUP * (parentVelocityX * cosf(angle) - parentVelocityY * sinf(angle));
                        asteroids[child1].velocityY = ASTEROID_SPLIT_SPEEDUP * (parentVelocityX * sinf(angle) + parentVelocityY * cosf(angle));
                        asteroids[child1].angularVelocity = -(get_rand_32() % 16) / 64.0f;
                    }
                }
                else
                {
                    // Remove small asteroids
                    asteroidBufferRemove(asteroids, asteroidBufferSize, asteroidIndex);
                }

                continue;
            }
        }
    }
}
