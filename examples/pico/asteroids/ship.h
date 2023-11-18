#ifndef SHIP_H
#define SHIP_H

// Ship -----------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the ship object.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define SHIP_ACCELERATION_Y       0.2f   // Acceleration of the ship (forward / backward) in pixels per (30ms)^2.
#define SHIP_ANGULAR_ACCELERATION 0.03f  // Angular acceleration of the ship (left / right) in pixels per (30ms)^2.

#define SHIP_VELOCITY_DRAG        0.95f  // Percentage of the remaining ship velocity after 30ms.
#define SHIP_ANGULAR_DRAG         0.80f  // Percentage of the remaining ship angular velocity after 30ms.

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_SHIP_MODEL              25        // Max size of all ship models (see options below).

#define SHIP_CENTER_OF_MASS_X        0x09      // X offset of the center of the ship (rotation pivot).
#define SHIP_CENTER_OF_MASS_Y        0x09      // Y offset of the center of the ship (rotation pivot).
#define SHIP_COLLIDER_GUN_X          0x12      // X offset of the top of the ship (gun).
#define SHIP_COLLIDER_GUN_Y          0x09      // Y offset of the top of the ship (gun).
#define SHIP_COLLIDER_BOTTOM_LEFT_X  0x00      // X offset of the bottom left corner of the ship (when viewed vertically).
#define SHIP_COLLIDER_BOTTOM_LEFT_Y  0x0F      // Y offset of the bottom left corner of the ship (when viewed vertically).
#define SHIP_COLLIDER_BOTTOM_RIGHT_X 0x00      // X offset of the bottom right corner of the ship (when viewed vertically).
#define SHIP_COLLIDER_BOTTOM_RIGHT_Y 0x03      // Y offset of the bottom right corner of the ship (when viewed vertically).

// Model to render when not moving
#define SIZE_SHIP_MODEL_IDLE 17
extern struct xyPoint shipModelIdle[SIZE_SHIP_MODEL_IDLE];

// Model to render when moving forward
#define SIZE_SHIP_MODEL_ACCELERATING 25
extern struct xyPoint shipModelAccelerating[SIZE_SHIP_MODEL_ACCELERATING];

// Objects --------------------------------------------------------------------------------------------------------------------

// Ship Object
// - Object containing all properties related to a ship.
struct shipObject
{
    float positionY;                     // Y position of the ship in pixels.
    float positionX;                     // X position of the ship in pixels.
    float velocityX;                     // X velocity of the ship in pixels per 30ms.
    float velocityY;                     // Y velocity of the ship in pixels per 30ms.
    float rotation;                      // Rotation of the ship in radians.
    float angularVelocity;               // Angular velocity of the ship in radians per 30ms.
    bool  accelerating;                  // Indicates whether the ship is moving forward.
    bool  reloaded;                      // Indicates whether the ship is able to shoot.

    float colliderGunX;                  // X offset of the top of the ship from the current position.
    float colliderGunY;                  // Y offset of the top of the ship from the current position.
    float colliderBottomLeftX;           // X offset of the bottom left corner of the ship from the current position.
    float colliderBottomLeftY;           // Y offset of the bottom left corner of the ship from the current position.
    float colliderBottomRightX;          // X offset of the bottom right corner of the ship from the current position.
    float colliderBottomRightY;          // Y offset of the bottom right corner of the ship from the current position.

    volatile struct xyShape* model;      // Shape handler of the model for the ship.

    // Buffer of points to render, contains a translated copy of one of the below ship models.
    struct xyPoint modelBuffer[SIZE_SHIP_MODEL];
};

typedef volatile struct shipObject ship_t;

// Functions ------------------------------------------------------------------------------------------------------------------

// Initialize Ship
// - Call to initialize the ship to its default values and put the model in the render stack.
// - Must be called before the ship will be rendered.
void shipInitialize(ship_t* ship, float positionX, float positionY);

// Update Ship
// - Call to update the properties of the ship by one time step (30ms).
void shipUpdate(ship_t* ship);

// Render Ship
// - Call to update the model of the ship based on its current state.
void shipRender(ship_t* ship);

// Respawn Ship
// - Call to reset the ship to the spawn position.
void shipRespawn(ship_t* ship);

#endif // SHIP_H
