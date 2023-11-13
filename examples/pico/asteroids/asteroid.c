// Header
#include "asteroid.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Asteroid Functions ---------------------------------------------------------------------------------------------------------

void asteroidInitialize(struct asteroid_t* asteroid)
{
    asteroid->active           = false;
    asteroid->positionX        = 0.0f;
    asteroid->positionY        = 0.0f;
    asteroid->velocityX        = 0.0f;
    asteroid->velocityY        = 0.0f;
    asteroid->rotation         = 0.0f;
    asteroid->angularVelocity  = 0.0f;

    // Put model in the render stack
    asteroid->model = xyRendererRenderShape(asteroid->modelBuffer, 0, 0x00, 0x00);
    asteroid->model->visible = false;
}

void asteroidUpdate(struct asteroid_t* asteroid)
{
    asteroid->positionX += asteroid->velocityX;
    asteroid->positionY += asteroid->velocityY;

    if(asteroid->positionX < 0.0f)    asteroid->positionX += 256.0f;
    if(asteroid->positionX >= 256.0f) asteroid->positionX -= 256.0f;
    if(asteroid->positionY < 0.0f)    asteroid->positionY += 256.0f;
    if(asteroid->positionY >= 256.0f) asteroid->positionY -= 256.0f;

    asteroid->rotation += asteroid->angularVelocity;
    if(asteroid->rotation < 0)       asteroid->rotation += 2*M_PI;
    if(asteroid->rotation >= 2*M_PI) asteroid->rotation -= 2*M_PI;
}

void asteroidRender(struct asteroid_t* asteroid)
{
    // Update model position
    asteroid->model->positionX = roundf(asteroid->positionX);
    asteroid->model->positionY = roundf(asteroid->positionY);

    // Translate model into buffer
    xyShapeRotate(asteroid->modelBase, asteroid->modelBuffer, SIZE_ASTEROID_MODEL, asteroid->centerOfMassX, asteroid->centerOfMassY, roundf(asteroid->rotation * 255.0f / (2 * M_PI)));
    asteroid->model->pointCount = SIZE_ASTEROID_MODEL;
}

void asteroidModelGenerate(struct asteroid_t* asteroid, uint16_t radius)
{
    asteroid->centerOfMassX = radius;
    asteroid->centerOfMassY = radius;
    asteroid->colliderRadius = radius;

    // Generate circle
    for(uint16_t index = 0; index < SIZE_ASTEROID_MODEL - 1; ++index)
    {
        float theta = index * 2 * M_PI / SIZE_ASTEROID_MODEL;
        asteroid->modelBase[index].x = roundf((radius * (get_rand_32() % 8 + 8) / 16.0f) * cosf(theta) + asteroid->centerOfMassX);
        asteroid->modelBase[index].y = roundf((radius * (get_rand_32() % 8 + 8) / 16.0f) * sinf(theta) + asteroid->centerOfMassY);
    }

    // Close loop
    asteroid->modelBase[SIZE_ASTEROID_MODEL - 1].x = asteroid->modelBase[0].x;
    asteroid->modelBase[SIZE_ASTEROID_MODEL - 1].y = asteroid->modelBase[0].y;

    asteroidRender(asteroid);
}

// Asteroid Buffer Functions --------------------------------------------------------------------------------------------------

void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        asteroidInitialize(&asteroids[index]);
    }
}

int16_t asteroidBufferInsert(struct asteroid_t* asteroids, uint16_t bufferSize, float positionX, float positionY, uint16_t radius)
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

            return index;
        }
    }

    return -1;
}

void asteroidBufferRemove(struct asteroid_t* asteroids, uint16_t bufferSize, uint16_t index)
{
    asteroids[index].active = false;
    asteroids[index].model->visible = false;
}

void asteroidBufferUpdate(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(asteroids[index].active)
        {
            asteroidUpdate(&asteroids[index]);
        }
    }
}

void asteroidBufferRender(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(asteroids[index].active)
        {
            asteroidRender(&asteroids[index]);
        }
    }
}
