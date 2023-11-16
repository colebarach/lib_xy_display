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
    asteroid->size             = -1;
    asteroid->modelPointCount  = 0;

    // Put model in the render stack
    asteroid->model = xyRendererRenderShape(asteroid->modelBuffer, 0, 0x00, 0x00);
    asteroid->model->visible = false;
}

void asteroidActivate(struct asteroid_t* asteroid, int8_t size, float positionX, float positionY, float velocityX, float velocityY, float rotation, float angularVelocity)
{
    // Set default size, range [2, 3]
    if(size <= -1) size = (get_rand_32() % 2) + 2;

    // Map size to radius
    float radius = (size + 1) * 4.0f;

    asteroid->size = size;

    asteroid->positionX       = positionX;
    asteroid->positionY       = positionY;
    asteroid->velocityX       = velocityX;
    asteroid->velocityY       = velocityY;
    asteroid->rotation        = rotation;
    asteroid->angularVelocity = angularVelocity;
    asteroid->centerOfMassX   = radius;
    asteroid->centerOfMassY   = radius;
    asteroid->colliderRadius  = radius;

    // Map size to model detail
    asteroid->modelPointCount = (size + 1) * 2 + 9;

    // Generate asteroid model
    asteroid->modelPointCount = (size + 1) * 2 + 9;
    asteroidModelGenerate(asteroid->modelBase, asteroid->modelPointCount, radius);

    // Update model properties and enable rendering
    asteroidRender(asteroid);
    asteroid->model->visible = true;

    // Activate object
    asteroid->active = true;
}

void asteroidSpawn(struct asteroid_t* asteroid, int8_t size, int8_t speed, float xLowerBound, float xUpperBound, float yLowerBound, float yUpperBound)
{
    // Set default size, range [2, 3]
    if(size <= -1) size = (get_rand_32() % 2) + 2;

    // Set default speed
    if(speed == -1) speed = 1;

    // Map size to radius
    float radius = (size + 1) * 4.0f;

    float positionX = 0.0f;
    float positionY = 0.0f;
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    // Determine what size of screen to spawn from
    uint16_t side = (uint16_t)(get_rand_32() % 4);
    if(side == 0)
    {
        // Left side
        positionX = xLowerBound;
        positionY = (get_rand_32() % 32) / 32.0f * (yUpperBound - yLowerBound - 2 * radius - 1) + yLowerBound;

        velocityX = (get_rand_32() % 32) / 32.0f * speed / 8.0f * (ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MIN) + ASTEROID_VELOCITY_MIN;
        velocityY = ((get_rand_32() % 32) / 16.0f * ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MAX) * speed / 8.0f;
    }
    else if(side == 1)
    {
        // Right side
        positionX = xUpperBound - 2 * radius - 1;
        positionY = (get_rand_32() % 32) / 32.0f * (yUpperBound - yLowerBound - 2 * radius - 1) + yLowerBound;

        velocityX = - ((get_rand_32() % 32) / 32.0f * speed / 8.0f * (ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MIN) + ASTEROID_VELOCITY_MIN);
        velocityY = ((get_rand_32() % 32) / 16.0f * ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MAX) * speed / 8.0f;
    }
    else if(side == 2)
    {
        // Bottom side
        positionX = (get_rand_32() % 32) / 32.0f * (xUpperBound - xLowerBound - 2 * radius - 1) + xLowerBound;
        positionY = yLowerBound;

        velocityX = ((get_rand_32() % 32) / 16.0f * ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MAX) * speed / 8.0f;
        velocityY = (get_rand_32() % 32) / 32.0f * speed / 8.0f * (ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MIN) + ASTEROID_VELOCITY_MIN;
    }
    else
    {
        // Top side
        positionX = (get_rand_32() % 32) / 32.0f * (xUpperBound - xLowerBound - 2 * radius - 1) + xLowerBound;
        positionY = yUpperBound - 2 * radius - 1;

        velocityX = ((get_rand_32() % 32) / 16.0f * ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MAX) * speed / 8.0f;
        velocityY = - ((get_rand_32() % 32) / 32.0f * speed / 8.0f * (ASTEROID_VELOCITY_MAX - ASTEROID_VELOCITY_MIN) + ASTEROID_VELOCITY_MIN);
    }

    // Choose random angular velocity
    float rotation        = 0.0f;
    float angularVelocity = ((get_rand_32() % 32) / 16.0f * ASTEROID_ANGULAR_VELOCITY_MAX - ASTEROID_ANGULAR_VELOCITY_MAX) * speed / 8.0f;

    // Activate asteroid
    asteroidActivate(asteroid, size, positionX, positionY, velocityX, velocityY, rotation, angularVelocity);
}

void asteroidSplit(struct asteroid_t* parent, struct asteroid_t* child1)
{
    // Block small asteroids
    if(parent->size <= 0) return;

    // Calculate child 1 properties
    if(child1 != NULL)
    {
        float angleDelta = - ((get_rand_32() % 32) / 32.0f * (ASTEROID_SPLIT_ANGLE_MAX - ASTEROID_SPLIT_ANGLE_MIN) + ASTEROID_SPLIT_ANGLE_MIN);

        float child1VelocityX       = ASTEROID_SPLIT_SPEEDUP * (parent->velocityX * cosf(angleDelta) - parent->velocityY * sinf(angleDelta));
        float child1VelocityY       = ASTEROID_SPLIT_SPEEDUP * (parent->velocityX * sinf(angleDelta) + parent->velocityY * cosf(angleDelta));
        float child1PositionX       = parent->positionX + child1VelocityX;
        float child1PositionY       = parent->positionY + child1VelocityY;
        float child1AngularVelocity = - (get_rand_32() % 32) / 32.0f * ASTEROID_ANGULAR_VELOCITY_MAX;

        asteroidActivate(child1, parent->size - 1, child1PositionX, child1PositionY, child1VelocityX, child1VelocityY, 0.0f, child1AngularVelocity);
    }

    // Calculate child 0 properties
    float angleDelta = (get_rand_32() % 32) / 32.0f * (ASTEROID_SPLIT_ANGLE_MAX - ASTEROID_SPLIT_ANGLE_MIN) + ASTEROID_SPLIT_ANGLE_MIN;

    float child0VelocityX       = ASTEROID_SPLIT_SPEEDUP * (parent->velocityX * cosf(angleDelta) - parent->velocityY * sinf(angleDelta));
    float child0VelocityY       = ASTEROID_SPLIT_SPEEDUP * (parent->velocityX * sinf(angleDelta) + parent->velocityY * cosf(angleDelta));
    float child0PositionX       = parent->positionX + child0VelocityX;
    float child0PositionY       = parent->positionY + child0VelocityY;
    float child0AngularVelocity = (get_rand_32() % 32) / 32.0f * ASTEROID_ANGULAR_VELOCITY_MAX;

    // Replace parent with child 0
    asteroidActivate(parent, parent->size - 1, child0PositionX, child0PositionY, child0VelocityX, child0VelocityY, 0.0f, child0AngularVelocity);
}

void asteroidBufferRemove(struct asteroid_t* asteroids, uint16_t bufferSize, int16_t index)
{
    asteroids[index].active = false;
    asteroids[index].model->visible = false;
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
    xyShapeRotate(asteroid->modelBase, asteroid->modelBuffer, asteroid->modelPointCount, asteroid->centerOfMassX, asteroid->centerOfMassY, roundf(asteroid->rotation * 255.0f / (2 * M_PI)));
    asteroid->model->pointCount = asteroid->modelPointCount;
}

void asteroidModelGenerate(struct xyPoint* model, uint16_t modelSize, float radius)
{
    // Generate circle with random radius
    for(uint16_t index = 0; index < modelSize - 1; ++index)
    {
        float theta = index * 2 * M_PI / modelSize;

        float radiusScalar = (get_rand_32() % 32) / 32.0f * (1.0f - ASTEROID_RADIUS_SCALAR_MIN) + ASTEROID_RADIUS_SCALAR_MIN;
        model[index].x = roundf(radiusScalar * radius * cosf(theta) + radius);
        model[index].y = roundf(radiusScalar * radius * sinf(theta) + radius);
    }

    // Complete loop
    model[modelSize - 1].x = model[0].x;
    model[modelSize - 1].y = model[0].y;
}

void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        asteroidInitialize(&asteroids[index]);
    }
}

int16_t asteroidBufferSpawn(struct asteroid_t* asteroids, uint16_t bufferSize, int8_t size, int8_t speed, float xLowerBound, float xUpperBound, float yLowerBound, float yUpperBound)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(!asteroids[index].active)
        {
            asteroidSpawn(&asteroids[index], size, speed, xLowerBound, xUpperBound, yLowerBound, yUpperBound);
            return index;
        }
    }

    return -1;
}

int16_t asteroidBufferSplit(struct asteroid_t* asteroids, uint16_t bufferSize, int16_t parentIndex)
{
    // Check asteroid size
    if(asteroids[parentIndex].size <= 0)
    {
        // Destroy small asteroids
        asteroidBufferRemove(asteroids, bufferSize, parentIndex);
        return -1;
    }
    else
    {
        // Scan for empty slot
        for(uint16_t index = 0; index < bufferSize; ++index)
        {
            if(!asteroids[index].active)
            {
                // Split using child 1
                asteroidSplit(&asteroids[parentIndex], &asteroids[index]);
                return index;
            }
        }

        // Split without child 1
        asteroidSplit(&asteroids[parentIndex], NULL);
        return -1;
    }
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

uint16_t asteroidBufferCountActive(struct asteroid_t* asteroids, uint16_t bufferSize)
{
    uint16_t activeCount = 0;

    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(asteroids[index].active)
        {
            ++activeCount;
        }
    }

    return activeCount;
}
