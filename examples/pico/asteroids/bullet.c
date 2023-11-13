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
    {0x00, 0x00}, {0x03, 0x00}, {0x06, 0x00}, {0x06, 0x01}, {0x03, 0x01}, {0x00, 0x01}, {0x00, 0x00}
};

// Bullet Functions -----------------------------------------------------------------------------------------------------------

void bulletInitialize(struct bullet_t* bullet)
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

void bulletUpdate(struct bullet_t* bullet)
{
    bullet->positionX += bullet->velocityX;
    bullet->positionY += bullet->velocityY;

    if(bullet->positionX < 0.0f || bullet->positionX >= 256.0f || bullet->positionY < 0.0f || bullet->positionY >= 256.0f)
    {
        bullet->active = false;
        bullet->model->visible = false;
    }
}

void bulletRender(struct bullet_t* bullet)
{
    // Update model position
    bullet->model->positionX = roundf(bullet->positionX);
    bullet->model->positionY = roundf(bullet->positionY);
}

// Bullet Buffer Functions ----------------------------------------------------------------------------------------------------

void bulletBufferInitialize(struct bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        bulletInitialize(&bullets[index]);
    }
}

void bulletBufferInsert(struct bullet_t* bullets, uint16_t bufferSize, float positionX, float positionY, float rotation, float velocity)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(!bullets[index].active)
        {
            bullets[index].active = true;
            bullets[index].positionX = positionX;
            bullets[index].positionY = positionY;
            bullets[index].velocityX = velocity * cosf(rotation);
            bullets[index].velocityY = velocity * sinf(rotation);
            bullets[index].rotation  = rotation;

            bullets[index].colliderHeadX = (BULLET_SIZE_X - BULLET_CENTER_OF_MASS_X) * cosf(rotation) + BULLET_CENTER_OF_MASS_X;
            bullets[index].colliderHeadY = (BULLET_SIZE_X - BULLET_CENTER_OF_MASS_X) * sinf(rotation) + BULLET_CENTER_OF_MASS_Y;

            xyShapeRotate(bulletModel, bullets[index].modelBuffer, SIZE_BULLET_MODEL, BULLET_CENTER_OF_MASS_X, BULLET_CENTER_OF_MASS_Y, roundf(bullets[index].rotation * 255.0f / (2 * M_PI)));
            bullets[index].model->pointCount = SIZE_BULLET_MODEL;

            bullets[index].model->visible = true;

            return;
        }
    }

    // TODO: Buffer is full, what to do here?
}

void bulletBufferRemove(struct bullet_t* bullets, uint16_t bufferSize, uint16_t index)
{
    bullets[index].active = false;
    bullets[index].model->visible = false;
}

void bulletBufferUpdate(struct bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(bullets[index].active)
        {
            bulletUpdate(&bullets[index]);
        }
    }
}

void bulletBufferRender(struct bullet_t* bullets, uint16_t bufferSize)
{
    for(uint16_t index = 0; index < bufferSize; ++index)
    {
        if(bullets[index].active)
        {
            bulletRender(&bullets[index]);
        }
    }
}
