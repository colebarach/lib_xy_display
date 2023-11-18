#ifndef GUI_H
#define GUI_H

// Score ----------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the score counter object.
//
// To do:
// - Score counter could just have an array for digits.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define LIFE_COUNTER_MAX_LIVES 16

// Objects --------------------------------------------------------------------------------------------------------------------

// Score Counter Object
// - Object containing all properties related to the score counter.
struct scoreObject
{
    volatile struct xyShape* digit0;     // Shape handler for digit 0.
    volatile struct xyShape* digit1;     // Shape handler for digit 1.
    volatile struct xyShape* digit2;     // Shape handler for digit 2.
    volatile struct xyShape* digit3;     // Shape handler for digit 3.
    volatile struct xyShape* digit4;     // Shape handler for digit 4.
    volatile struct xyShape* digit5;     // Shape handler for digit 5.
};

typedef volatile struct scoreObject score_t;

// Live Counter Object
// - Object containing all properties related to the life counter.
struct lifeObject
{
    volatile struct xyShape* lives;
};

typedef volatile struct lifeObject life_t;

// Score Counter Functions ----------------------------------------------------------------------------------------------------

// Initialize Score Counter
// - Call to initialize the score counter and put models in the render stack.
// - Must be called before the score will be rendered.
void scoreInitialize(score_t* score, xyCoord positionX, xyCoord positionY);

// Update Score Counter
// - Call to update the value of the score counter.
void scoreUpdate(score_t* score, uint32_t scoreValue);

// Life Counter Functions -----------------------------------------------------------------------------------------------------

// // Initialize Score Counter
// // - Call to initialize the score counter and put models in the render stack.
// // - Must be called before the score will be rendered.
// void lifeInitialize(life_t* score, xyCoord positionX, xyCoord positionY);
//
// // Update Score Counter
// // - Call to update the value of the score counter.
// void lifeUpdate(life_t* score, uint32_t scoreValue);

#endif // GUI_H
