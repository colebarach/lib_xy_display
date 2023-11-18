#ifndef GUI_H
#define GUI_H

// Score ----------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Set of objects, variables and functions related to the score counter object.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define SCORE_COUNTER_SIZE 6             // Number of digits in the score counter.
#define LIFE_COUNTER_SIZE  18            // Number of icons in the life counter.

// Models ---------------------------------------------------------------------------------------------------------------------

// Ship life icon model
#define SIZE_LIFE_ICON_MODEL 15
extern struct xyPoint lifeIconModel[SIZE_LIFE_ICON_MODEL];

// Objects --------------------------------------------------------------------------------------------------------------------

// Score Counter Object
// - Object containing all properties related to the score counter.
struct scoreCounterObject
{
    volatile struct xyShape* digits[SCORE_COUNTER_SIZE];       // Shape handlers for each digit of the counter.
};

typedef volatile struct scoreCounterObject scoreCounter_t;

// Live Counter Object
// - Object containing all properties related to the life counter.
struct lifeCounterObject
{
    volatile struct xyShape* lives[LIFE_COUNTER_SIZE];         // Shape handlers for each life icon.
};

typedef volatile struct lifeCounterObject lifeCounter_t;

// Score Counter Functions ----------------------------------------------------------------------------------------------------

// Initialize Score Counter
// - Call to initialize the score counter and put models in the render stack.
// - Must be called before the score will be rendered.
void scoreInitialize(scoreCounter_t* scoreCounter, xyCoord positionX, xyCoord positionY);

// Update Score Counter
// - Call to update the value of the score counter.
// - Updates the digit models to display the new score.
void scoreUpdate(scoreCounter_t* scoreCounter, uint32_t scoreValue);

// Life Counter Functions -----------------------------------------------------------------------------------------------------

// Initialize Life Counter
// - Call to initialize the life counter and put models in the render stack.
// - Must be called before the lives will be rendered.
void lifeInitialize(lifeCounter_t* lifeCounter, xyCoord positionX, xyCoord positionY);

// Update Life Counter
// - Call to update the value of the life counter.
// - Updates the number of icons display the remaining lives.
void lifeUpdate(lifeCounter_t* lifeCounter, int8_t lifeCount);

#endif // GUI_H
