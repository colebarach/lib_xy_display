#ifndef INPUT_H
#define INPUT_H

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// C Standard Libraries
#include <math.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "ship.h"
#include "bullet.h"

// Pin Mapping ----------------------------------------------------------------------------------------------------------------

#define BUTTON_PIN_UP    16              // GPIO pin number of the up button.
#define BUTTON_PIN_LEFT  18              // GPIO pin number of the left button.
#define BUTTON_PIN_RIGHT 19              // GPIO pin number of the right button.
#define BUTTON_PIN_SHOOT 17              // GPIO pin number of the down button.

// Functions ------------------------------------------------------------------------------------------------------------------

// Initialize Input
// - Call to setup the inputs
// - Required call before inputGet is called
void inputInitialize();

// Get Input
// - Call to update the movement of the player ship based on current input.
void inputGet(ship_t* playerShip, bullet_t* bulletBuffer, uint16_t bulletBufferSize);

#endif // INPUT_H
