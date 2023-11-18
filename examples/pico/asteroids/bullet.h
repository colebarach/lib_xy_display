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

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define BULLET_VELOCITY         8.0f     // Speed of each bullet in pixels per 30ms.

// Models ---------------------------------------------------------------------------------------------------------------------

#define BULLET_CENTER_OF_MASS_X 0x03     // X offset of the center of the bullet model (rotation pivot).
#define BULLET_CENTER_OF_MASS_Y 0x03     // Y offset of the center of the bullet model (rotation pivot).
#define BULLET_SIZE_X           0x07     // X length of the bullet model.
#define BULLET_SIZE_Y           0x03     // Y length of the bullet model

// Model of a bullet (untranslated)
#define SIZE_BULLET_MODEL 7
extern struct xyPoint bulletModel[SIZE_BULLET_MODEL];

// Objects --------------------------------------------------------------------------------------------------------------------

// Bullet Object
// - Object containing all properties related to a single bullet.
struct bulletObject
{
    // Properties
    bool active;                         // Marks whether this object is active or not, (inactive objects are skipped).

    // Physics
    float positionX;                     // X position of the object in pixels.
    float positionY;                     // Y position of the object in pixels.
    float velocityX;                     // X velocity of the object in pixels per 30ms.
    float velocityY;                     // Y velocity of the object in pixels per 30ms.
    float rotation;                      // Rotation of the object in radians

    // Collision
    float colliderHeadX;                 // X offset of the head of the bullet in pixels
    float colliderHeadY;                 // Y offset of the head of the bullet in pixels

    // Rendering
    volatile struct xyShape* model;                            // Shape handler of the object model.
    struct xyPoint modelBuffer[SIZE_BULLET_MODEL];             // Buffer for the translated copy of the bullet model.
};

// Bullet Object Type
// - This must be volatile, as it modifies data used by the renderer.
typedef volatile struct bulletObject bullet_t;

// Bullet Functions -----------------------------------------------------------------------------------------------------------

// Initialize Bullet
// - Call to initialize the object to its default values and put the model in the render stack.
// - Must be called before the object will be rendered.
void bulletInitialize(bullet_t* bullet);

// Spawn Bullet
// - Call to activate the bullet object and spawn it with the given properties.
void bulletSpawn(bullet_t* bullet, float positionX, float positionY, float rotation, float velocity);

// Update Bullet
// - Call to update the properties of the bullet by one time step (30ms).
void bulletUpdate(bullet_t* bullet);

// Render Asteroid
// - Call to update the model of the bullet based on its current state.
void bulletRender(bullet_t* bullet);

// Bullet Buffer Functions ----------------------------------------------------------------------------------------------------

// Initialize Bullet Buffer
// - Call to initialize the object buffer and place models in the render stack.
// - Must be called before any objects will be rendered.
void bulletBufferInitialize(bullet_t* bullets, uint16_t bufferSize);

// Spawn Bullet into Buffer
// - Call to spawn a bullet at the given position and rotation
// - Returns the index of the new bullet, if created. Returns -1 otherwise
int16_t bulletBufferSpawn(bullet_t* bullets, uint16_t bufferSize, float positionX, float positionY, float rotation, float velocity);

// Remove Bullet from Buffer
// - Call to remove the specified object from the buffer.
// - Will mark the object as inactive and stop rendering its model.
void bulletBufferRemove(bullet_t* bullets, uint16_t bufferSize, uint16_t index);

// Update Bullet Buffer
// - Call to update all active objects in the buffer.
void bulletBufferUpdate(bullet_t* bullets, uint16_t bufferSize);

// Render Bullet Buffer
// - Call to render all active objects in the buffer.
void bulletBufferRender(bullet_t* bullets, uint16_t bufferSize);

#endif // BULLET_H
