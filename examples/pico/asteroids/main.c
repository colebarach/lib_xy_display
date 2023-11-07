// Asteroids Programming Example ----------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Implementation of the videogame 'asteroids' using the X-Y rendering library.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Pico Standard Library
#include <pico/stdlib.h>

// C Standatd Libraries
#include <math.h>

// Inputs ---------------------------------------------------------------------------------------------------------------------

#define BUTTON_PIN_UP    18    // GPIO pin number of the up button
#define BUTTON_PIN_DOWN  19    // GPIO pin number of the down button
#define BUTTON_PIN_LEFT  20    // GPIO pin number of the left button
#define BUTTON_PIN_RIGHT 21    // GPIO pin number of the right button
#define BUTTON_PIN_SHOOT 22    // GPIO pin number of the shoot button

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define SHIP_LIVES_START 4

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_SHIP_MODEL_IDLE 17
struct xyPoint shipModelIdle[SIZE_SHIP_MODEL_IDLE] =
{
    {0x00, 0x00}, {0x01, 0x03}, {0x03, 0x03}, {0x05, 0x03}, {0x07, 0x03}, {0x03, 0x03}, {0x01, 0x03}, {0x03, 0x09},
    {0x05, 0x0F}, {0x06, 0x12}, {0x07, 0x0F}, {0x09, 0x09}, {0x0B, 0x03}, {0x09, 0x03}, {0x07, 0x03}, {0x0B, 0x03},
    {0x0C, 0x00}
};

#define SIZE_SHIP_MODEL_MOVING 25
struct xyPoint shipModelMoving[SIZE_SHIP_MODEL_MOVING] =
{
    {0x00, 0x00}, {0x01, 0x03}, {0x03, 0x03}, {0x06, 0x00}, {0x03, 0x03}, {0x05, 0x03}, {0x06, 0x02}, {0x05, 0x03}, 
    {0x07, 0x03}, {0x03, 0x03}, {0x01, 0x03}, {0x03, 0x09}, {0x05, 0x0F}, {0x06, 0x12}, {0x07, 0x0F}, {0x09, 0x09},
    {0x0B, 0x03}, {0x09, 0x03}, {0x06, 0x00}, {0x09, 0x03}, {0x07, 0x03}, {0x06, 0x02}, {0x07, 0x03}, {0x0B, 0x03},
    {0x0C, 0x00}
};

#define SIZE_SHIP_BUFFER 25 // Max size of all ship models

#define SHIP_CENTER_OF_MASS_X 0x06
#define SHIP_CENTER_OF_MASS_Y 0x09

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // Object Properties ------------------------------------------------------------------------------------------------------

    struct xyPoint shipBuffer[SIZE_SHIP_BUFFER];               // Buffer of points to render, contains a translated copy of one
                                                               // of the ship models.

    float shipPositionX = 128.0f;        // X position of the ship in pixels
    float shipPositionY = 128.0f;        // Y position of the ship in pixels

    float shipVelocityX = 0.0f;          // X velocity of the ship in pixels per 30ms
    float shipVelocityY = 0.0f;          // Y velocity of the ship in pixels per 30ms

    float shipRotation  = 0.0f;          // Rotation of the ship, [0, 256) mapped to [0 to 2PI)
    float shipAnglularVelocity = 0.0f;   // Angular velocity of the ship in radians per 30ms. (same mapping as above)

    // Game State -------------------------------------------------------------------------------------------------------------

    uint16_t shipLives = SHIP_LIVES_START;                     // Number of remaining extra lives.

    // Inputs -----------------------------------------------------------------------------------------------------------------

    gpio_init(BUTTON_PIN_UP);
    gpio_set_dir(BUTTON_PIN_UP, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_UP);
    
    gpio_init(BUTTON_PIN_DOWN);
    gpio_set_dir(BUTTON_PIN_DOWN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_DOWN);

    gpio_init(BUTTON_PIN_LEFT);
    gpio_set_dir(BUTTON_PIN_LEFT, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_LEFT);

    gpio_init(BUTTON_PIN_RIGHT);
    gpio_set_dir(BUTTON_PIN_RIGHT, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_RIGHT);

    // Object Rendering -------------------------------------------------------------------------------------------------------
    
    xyShapeRotate(shipModelIdle, shipBuffer, SIZE_SHIP_MODEL_IDLE, SHIP_CENTER_OF_MASS_X, SHIP_CENTER_OF_MASS_Y, shipRotation);
    volatile struct xyShape* ship = xyRendererRenderShape(shipBuffer, SIZE_SHIP_MODEL_IDLE, round(shipPositionX), round(shipPositionY));

    // Event Loop -------------------------------------------------------------------------------------------------------------

    while(true)
    {
        // Update ship position
        shipPositionX += shipVelocityX;
        shipPositionY += shipVelocityY;
        ship->positionX = round(shipPositionX);
        ship->positionY = round(shipPositionY);

        // Get vertical input
        if(!gpio_get(BUTTON_PIN_UP))
        {
            
        }
        else if(!gpio_get(BUTTON_PIN_DOWN))
        {
            
        }

        // Get horizontal input
        if(!gpio_get(BUTTON_PIN_LEFT))
        {
            
        }
        else if(!gpio_get(BUTTON_PIN_RIGHT))
        {
            
        }

        // Event loop period
        sleep_ms(30);
    }
}
