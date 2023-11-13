#ifndef ASTEROID_H
#define ASTEROID_H

// Asteroid -------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the asteroid object and the asteroid buffer.
//
// To do:
// - Make the generateModel function operate on a raw model rather than an object.
// - Update the asteroids to work on fixed radius sizes.
// - Move the setting of physics parameters outside the generateModel function.
// - Make a generic 'spawnAsteroid' function and move the responsibility out of the buffer functions.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_ASTEROID_MODEL    17        // Size of each asteroid model

// Objects --------------------------------------------------------------------------------------------------------------------

// Asteroid Object
// - Object containing all properties related to a single asteroid.
struct asteroid_t
{
    bool active;                         // Marks whether this asteroid is active or not, (inactive asteroids are skipped).

    float positionX;                     // X position of the asteroid in pixels.
    float positionY;                     // Y position of the asteroid in pixels.
    float velocityX;                     // X velocity of the asteroid in pixels per 30ms.
    float velocityY;                     // Y velocity of the asteroid in pixels per 30ms.
    float rotation;                      // Rotation of the asteroid in radians.
    float angularVelocity;               // Angular velocity of the asteroid in radians per 30ms.
    float centerOfMassX;                 // X offset of the center of the asteroid in pixels (rotation pivot).
    float centerOfMassY;                 // Y offset of the center of the asteroid in pixels (rotation pivot).

    float colliderRadius;                // Radius of the asteroid's collider (approximates collider as a circle).

    volatile struct xyShape* model;      // Shape handler of the asteroid model.

    // Buffer for the un-translated asteroid model (not rendered).
    struct xyPoint modelBase[SIZE_ASTEROID_MODEL];
    // Buffer for the translated copy of 'modelBase' (is rendered).
    struct xyPoint modelBuffer[SIZE_ASTEROID_MODEL];
};

// Asteroid Functions ---------------------------------------------------------------------------------------------------------

// Initialize Asteroid
// - Call to initialize the asteroid to its default values and put the model in the render stack.
// - Must be called before the asteroid will be rendered.
void asteroidInitialize(struct asteroid_t* asteroid);

// Update Asteroid
// - Call to update the properties of the asteroid by one time step (30ms).
void asteroidUpdate(struct asteroid_t* asteroid);

// Render Asteroid
// - Call to update the model of the asteroid based on its current state.
void asteroidRender(struct asteroid_t* asteroid);

// Generate Asteroid Model
// - Call to create a random model for the asteroid.
// - Use the radius to specify the size of the model in pixels.
void asteroidModelGenerate(struct asteroid_t* asteroid, uint16_t radius);

// Asteroid Buffer Functions --------------------------------------------------------------------------------------------------

// Initialize Asteroid Buffer
// - Call to initialize all of the asteroids in the buffer to their default parameters.
// - Will reserve a spot in the render stack for every model, but not render them until an insertion is made.
void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize);

// Insert Asteroid Buffer
// - Call to insert an asteroid into the buffer.
// - TODO: Should this take parameters? (yes, but have spawn function with defaults)
int16_t asteroidBufferInsert(struct asteroid_t* asteroids, uint16_t bufferSize, float positionX, float positionY, uint16_t radius);

// Remove Asteroid Buffer
// - Call to remove the specified asteroid from the buffer.
// - Will mark the asteroid as inactive and stop rendering its model.
void asteroidBufferRemove(struct asteroid_t* asteroids, uint16_t bufferSize, uint16_t index);

// Update Asteroid Buffer
// - Call to update all active asteroids in the buffer.
void asteroidBufferUpdate(struct asteroid_t* asteroids, uint16_t bufferSize);

// Render Asteroid Buffer
// - Call to render all active asteroids in the buffer.
void asteroidBufferRender(struct asteroid_t* asteroids, uint16_t bufferSize);

#endif // ASTEROID_H
