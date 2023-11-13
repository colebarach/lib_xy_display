#ifndef BULLET_H
#define BULLET_H

// Bullet ---------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the bullet object and the bullet buffer.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Models ---------------------------------------------------------------------------------------------------------------------

#define BULLET_CENTER_OF_MASS_X 0x03     //
#define BULLET_CENTER_OF_MASS_Y 0x01     //
#define BULLET_SIZE_X           0x07     //
#define BULLET_SIZE_Y           0x03     //

//
#define SIZE_BULLET_MODEL 7
extern struct xyPoint bulletModel[SIZE_BULLET_MODEL];

// Objects --------------------------------------------------------------------------------------------------------------------

struct bullet_t
{
    bool active;                         //

    float positionX;                     //
    float positionY;                     //
    float velocityX;                     //
    float velocityY;                     //
    float rotation;                      //

    float colliderHeadX;                 //
    float colliderHeadY;                 //

    volatile struct xyShape* model;      //

    //
    struct xyPoint modelBuffer[SIZE_BULLET_MODEL];
};

// Bullet Functions -----------------------------------------------------------------------------------------------------------

//
void bulletInitialize(struct bullet_t* bullet);

//
void bulletUpdate(struct bullet_t* bullet);

//
void bulletRender(struct bullet_t* bullet);

// Bullet Buffer Functions ----------------------------------------------------------------------------------------------------

//
void bulletBufferInitialize(struct bullet_t* bullets, uint16_t bufferSize);

//
void bulletBufferInsert(struct bullet_t* bullets, uint16_t bufferSize, float positionX, float positionY, float rotation, float velocity);

//
void bulletBufferRemove(struct bullet_t* bullets, uint16_t bufferSize, uint16_t index);

//
void bulletBufferUpdate(struct bullet_t* bullets, uint16_t bufferSize);

//
void bulletBufferRender(struct bullet_t* bullets, uint16_t bufferSize);

#endif // BULLET_H