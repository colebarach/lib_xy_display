// Header
#include "bullet.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Models ---------------------------------------------------------------------------------------------------------------------

struct xyPoint bulletModel[SIZE_BULLET_MODEL] =
{
    {0x00, 0x02}, {0x03, 0x02}, {0x06, 0x02}, {0x06, 0x03}, {0x03, 0x03}, {0x00, 0x03}, {0x00, 0x02}
};

// Bullet Functions -----------------------------------------------------------------------------------------------------------

void bulletInitialize(bullet_t* bullet)
{
    bullet->active          = false;
    bullet->positionX       = 0.0f;
    bullet->positionY       = 0.0f;
    bullet->velocityX       = 0.0f;
    bullet->velocityY       = 0.0f;
    bullet->rotation        = 0.0f;

    // Put model in the render stack
    bullet->model = xyRendererRenderShape(bullet->modelBuffer, 0, 0x00, 0x00);
    bullet->model->visible = false;
}

void bulletSpawn(bullet_t* bullet, float positionX, float positionY, float rotation, float velocity)
{
    // Calculate tail (to offset position)
    float bulletTailX = -(BULLET_SIZE_X / 2.0f - BULLET_CENTER_OF_MASS_X) * cosf(rotation) + BULLET_CENTER_OF_MASS_X;
    float bulletTailY = -(BULLET_SIZE_X / 2.0f - BULLET_CENTER_OF_MASS_X) * sinf(rotation) + BULLET_CENTER_OF_MASS_Y;

    // Set properties
    bullet->positionX = positionX - bulletTailX;
    bullet->positionY = positionY - bulletTailY;
    bullet->velocityX = velocity * cosf(rotation);
    bullet->velocityY = velocity * sinf(rotation);
    bullet->rotation  = rotation;

    // Calculate collider
    bullet->colliderHeadX = (BULLET_SIZE_X / 2.0f - BULLET_CENTER_OF_MASS_X) * cosf(rotation) + BULLET_CENTER_OF_MASS_X;
    bullet->colliderHeadY = (BULLET_SIZE_X / 2.0f - BULLET_CENTER_OF_MASS_X) * sinf(rotation) + BULLET_CENTER_OF_MASS_Y;

    // Translate model
    xyShapeRotate(bulletModel, bullet->modelBuffer, SIZE_BULLET_MODEL, BULLET_CENTER_OF_MASS_X, BULLET_CENTER_OF_MASS_Y, roundf(bullet->rotation * 255.0f / (2 * M_PI)));
    bullet->model->pointCount = SIZE_BULLET_MODEL;

    // Update model properties and enable rendering
    bulletRender(bullet);
    bullet->model->visible = true;

    // Activate object
    bullet->active = true;
}

void bulletUpdate(bullet_t* bullet)
{
    bullet->positionX += bullet->velocityX;
    bullet->positionY += bullet->velocityY;

    if(bullet->positionX < 0.0f || bullet->positionX >= 256.0f || bullet->positionY < 0.0f || bullet->positionY >= 256.0f)
    {
        bullet->active = false;
        bullet->model->visible = false;
    }
}

void bulletRender(bullet_t* bullet)
{
    // Update model position
    bullet->model->positionX = roundf(bullet->positionX);
    bullet->model->positionY = roundf(bullet->positionY);
}

// Bullet Buffer Functions ----------------------------------------------------------------------------------------------------

void bulletBufferInitialize(bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        bulletInitialize(&bullets[index]);
    }
}

int16_t bulletBufferSpawn(bullet_t* bullets, uint16_t bufferSize, float positionX, float positionY, float rotation, float velocity)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(!bullets[index].active)
        {
            bulletSpawn(&bullets[index], positionX, positionY, rotation, velocity);
            return index;
        }
    }

    return -1;
}

void bulletBufferRemove(bullet_t* bullets, uint16_t bufferSize, uint16_t index)
{
    bullets[index].active = false;
    bullets[index].model->visible = false;
}

void bulletBufferUpdate(bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(bullets[index].active)
        {
            bulletUpdate(&bullets[index]);
        }
    }
}

void bulletBufferRender(bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(bullets[index].active)
        {
            bulletRender(&bullets[index]);
        }
    }
}
