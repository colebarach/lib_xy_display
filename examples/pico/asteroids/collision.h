#ifndef COLLISION_H
#define COLLISION_H

// Collision ------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of functions for calculating collisions between objects.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "ship.h"
#include "bullet.h"
#include "asteroid.h"

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define ASTEROID_SPLIT_ANGLE_MIN  0.196f
#define ASTEROID_SPLIT_ANGLE_MAX  0.785f

#define ASTEROID_SPLIT_SPEEDUP    1.15f

// Object Functions -----------------------------------------------------------------------------------------------------------

//
bool collideShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroid);

//
bool collideBufferShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroids, uint16_t asteroidBufferSize);

// Buffer Functions -----------------------------------------------------------------------------------------------------------

//
bool collideBulletAsteroid(struct bullet_t* bullet, struct asteroid_t* asteroid);

//
void collideBuffersBulletAsteroid(struct bullet_t* bullets, uint16_t bulletBufferSize, struct asteroid_t* asteroids, uint16_t asteroidBufferSize);

#endif // COLLISION_H
