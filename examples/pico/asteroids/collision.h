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

// Object Functions -----------------------------------------------------------------------------------------------------------

// Ship to Asteroid Collision
// - Check to see if the specified ship is intersecting the specified asteroid.
// - Returns true if a collision has occured, false otherwise.
bool collideShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroid);

// Bullet to Asteroid Collision
// - Check to see if the specified bullet is intersecting the specified asteroid.
// - Returns true if a collision has occured, false otherwise.
bool collideBulletAsteroid(struct bullet_t* bullet, struct asteroid_t* asteroid);

// Buffer Functions -----------------------------------------------------------------------------------------------------------

//
bool collideBufferShipAsteroid(struct ship_t* ship, struct asteroid_t* asteroids, uint16_t asteroidBufferSize);

//
void collideBuffersBulletAsteroid(struct bullet_t* bullets, uint16_t bulletBufferSize, struct asteroid_t* asteroids, uint16_t asteroidBufferSize);

#endif // COLLISION_H
