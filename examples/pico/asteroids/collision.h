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
bool collideShipAsteroid(ship_t* ship, asteroid_t* asteroid);

// Bullet to Asteroid Collision
// - Check to see if the specified bullet is intersecting the specified asteroid.
// - Returns true if a collision has occured, false otherwise.
bool collideBulletAsteroid(bullet_t* bullet, asteroid_t* asteroid);

// Buffer Functions -----------------------------------------------------------------------------------------------------------

// Ship to Asteroid Buffer Collision
// - Call to check for collisions between a ship and an asteroid buffer.
// - Starts search from the value of 'asteroidIndex'
// - Returns true if a collision is detected and sets the value of 'asteroidIndex' to indicate the offendor.
// - Returns false if no collision is found.
bool collideBufferShipAsteroid(ship_t* ship, asteroid_t* asteroids, uint16_t asteroidBufferSize, int16_t* asteroidIndex);

// Bullet Buffer to Asteroid Buffer Collision
// - Call to check for collisions between objects of each buffer.
// - Starts search from the value of 'bulletIndex' and 'asteroidIndex'.
// - Returns true if a collision is detected and updates the values of 'bulletIndex' and 'asteroidIndex' to indicate the
//   offending objects.
// - Returns false if no collision is found.
bool collideBuffersBulletAsteroid(bullet_t* bullets, uint16_t bulletBufferSize, asteroid_t* asteroids, uint16_t asteroidBufferSize, int16_t* bulletIndex, int16_t* asteroidIndex);

#endif // COLLISION_H
