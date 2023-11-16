#ifndef ASTEROID_H
#define ASTEROID_H

// Asteroid -------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the asteroid object and the asteroid buffer.
//
// To do:
// - Consider min and max model details
// - Certain buffer functions could be written as macros, would that be worth it?
// - Asteroid position clamping should be variable for different screen sizes

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define ASTEROID_VELOCITY_MAX         1.0f     // Maximum starting velocity of an asteroid in pixels per 30ms.
#define ASTEROID_VELOCITY_MIN         0.15f    // Minimum starting velocity of an asteroid in pixels per 30ms.
#define ASTEROID_ANGULAR_VELOCITY_MAX 0.125f   // Maximum starting angular velocity in radians per 30ms.
#define ASTEROID_RADIUS_SCALAR_MIN    0.5f     // Minimum scalar to the radius noise.
#define ASTEROID_SPLIT_ANGLE_MIN      0.196f   // Minimum offset angle of a child from a split parent asteroid.
#define ASTEROID_SPLIT_ANGLE_MAX      0.785f   // Maximum offset angle of a child from a split parent asteroid.
#define ASTEROID_SPLIT_SPEEDUP        1.15f    // Gain in velocity of a child from a split parent asteroid.

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_ASTEROID_MODEL 17           // Size of each asteroid model

// Objects --------------------------------------------------------------------------------------------------------------------

// Asteroid Object
// - Object containing all properties related to a single asteroid.
struct asteroid_t
{
    // Properties
    bool active;                         // Marks whether this asteroid is active or not, (inactive asteroids are skipped).
    int8_t size;                         // Size of the asteroid, determines whether to split on death. (In range [0, 3]).

    // Physics
    float positionX;                     // X position of the asteroid in pixels.
    float positionY;                     // Y position of the asteroid in pixels.
    float velocityX;                     // X velocity of the asteroid in pixels per 30ms.
    float velocityY;                     // Y velocity of the asteroid in pixels per 30ms.
    float rotation;                      // Rotation of the asteroid in radians.
    float angularVelocity;               // Angular velocity of the asteroid in radians per 30ms.
    float centerOfMassX;                 // X offset of the center of the asteroid in pixels (rotation pivot).
    float centerOfMassY;                 // Y offset of the center of the asteroid in pixels (rotation pivot).

    // Collider
    float colliderRadius;                // Radius of the asteroid's collider (approximates collider as a circle).

    // Rendering
    uint16_t modelPointCount;                                  // Number of points in the model. (Based on size)
    volatile struct xyShape* model;                            // Shape handler of the asteroid model.
    struct xyPoint modelBase[SIZE_ASTEROID_MODEL];             // Buffer for the un-translated asteroid model (not rendered).
    struct xyPoint modelBuffer[SIZE_ASTEROID_MODEL];           // Buffer for the translated copy of 'modelBase' (is rendered).
};

// Asteroid Functions ---------------------------------------------------------------------------------------------------------

// Initialize Asteroid
// - Call to initialize the asteroid to its default values and put the model in the render stack.
// - Must be called before the asteroid will be rendered.
void asteroidInitialize(struct asteroid_t* asteroid);

// Activate Asteroid
// - Call to activate the asteroid with the specified properties
// - Note that this function is not necessary, as toggling the active flag will suffice. This exists as to enforce updating of
//   the asteroid's properties.
void asteroidActivate(struct asteroid_t* asteroid, int8_t size, float positionX, float positionY, float velocityX, float velocityY, float rotation, float angularVelocity);

// Spawn Asteroid
// - Call to activate the asteroid and spawn it within the given bounds (only spawns on edges).
// - Size should be in domain [0, 3] (use -1 for default)
// - Speed should be in domain [0, 8] (use -1 for default)
void asteroidSpawn(struct asteroid_t* asteroid, int8_t size, int8_t speed, float xLowerBound, float xUpperBound, float yLowerBound, float yUpperBound);

// Split Asteroid
// - Call to split the asteroid into two childern.
// - Replaces the parent asteroid with the first child, activates the second child, if it exists.
void asteroidSplit(struct asteroid_t* parent, struct asteroid_t* child1);

// Update Asteroid
// - Call to update the properties of the asteroid by one time step (30ms).
void asteroidUpdate(struct asteroid_t* asteroid);

// Render Asteroid
// - Call to update the model of the asteroid based on its current state.
void asteroidRender(struct asteroid_t* asteroid);

// Generate Asteroid Model
// - Call to create a new random model for an asteroid.
// - 'model' should be an array no smaller than 'modelSize'.
// - Use 'radius' to specify the maximum radius of the model in pixels.
void asteroidModelGenerate(struct xyPoint* model, uint16_t modelSize, float radius);

// Asteroid Buffer Functions --------------------------------------------------------------------------------------------------

// Initialize Asteroid Buffer
// - Call to initialize the asteroid buffer and place models in the render stack.
// - Must be called before any asteroids will be rendered.
void asteroidBufferInitialize(struct asteroid_t* asteroids, uint16_t bufferSize);

// Spawn Asteroid into Buffer
// - Call to spawn an asteroid within the given bounds (only spawns on edges).
// - Size should be in domain [0, 3] (use -1 for default)
// - Speed should be in domain [0, 8] (use -1 for default)
// - Returns the index of the new asteroid, if created. Returns -1 otherwise.
int16_t asteroidBufferSpawn(struct asteroid_t* asteroids, uint16_t bufferSize, int8_t size, int8_t speed, float xLowerBound, float xUpperBound, float yLowerBound, float yUpperBound);

// Split Asteroid into Buffer
// - Call to split an asteroid in the buffer into 2 children.
// - The parent asteroid is replaced by the first child
// - The index of the second child is returned, if it is created. Returns -1 otherwise.
int16_t asteroidBufferSplit(struct asteroid_t* asteroids, uint16_t bufferSize, int16_t parentIndex);

// Remove Asteroid from Buffer
// - Call to remove the specified asteroid from the buffer.
// - Will mark the asteroid as inactive and stop rendering its model.
void asteroidBufferRemove(struct asteroid_t* asteroids, uint16_t bufferSize, int16_t index);

// Update Asteroid Buffer
// - Call to update all active asteroids in the buffer.
void asteroidBufferUpdate(struct asteroid_t* asteroids, uint16_t bufferSize);

// Render Asteroid Buffer
// - Call to render all active asteroids in the buffer.
void asteroidBufferRender(struct asteroid_t* asteroids, uint16_t bufferSize);

// Count Active Asteroids in Buffer
// - Call to get the number of active asteroids in an asteroid buffer.
uint16_t asteroidBufferCountActive(struct asteroid_t* asteroids, uint16_t bufferSize);

#endif // ASTEROID_H
