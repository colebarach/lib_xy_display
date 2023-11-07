// Pong Programming Example ---------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Implementation of the videogame 'pong' using the X-Y rendering library.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

// Pico Standard Library
#include <pico/stdlib.h>

// C Standatd Libraries
#include <math.h>

// Inputs ---------------------------------------------------------------------------------------------------------------------

#define BUTTON_PIN_PADDLE_0_UP   18      // GPIO pin number of paddle 0's up button 
#define BUTTON_PIN_PADDLE_0_DOWN 19      // GPIO pin number of paddle 0's down button
#define BUTTON_PIN_PADDLE_1_UP   20      // GPIO pin number of paddle 1's up button
#define BUTTON_PIN_PADDLE_1_DOWN 21      // GPIO pin number of paddle 1's down button

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define PADDLE_VELOCITY_Y        4       // Speed of the moving paddle in pixels per 30ms
#define PADDLE_CURVATURE         0.2f    // Slope of the paddle surface, affects ball after hit
#define PADDLE_BALL_SPEEDUP      1.05f   // Ball velocity multiplier from paddle hit

#define BALL_START_VELOCITY_X    2.0f    // Ball x velocity at start of game
#define BALL_START_VELOCITY_Y    0.0f    // Ball y velocity at start of game

#define PADDLE_WIDTH             0x04    // Width of the paddles in pixels
#define PADDLE_HEIGHT            0x14    // Height of the paddles in pixels

#define BALL_SIZE                0x04    // Diameter of the ball in pixels

// Models ---------------------------------------------------------------------------------------------------------------------

#define SIZE_PADDLE_MODEL 29
struct xyPoint paddleModel[SIZE_PADDLE_MODEL] =
{
    {0x00, 0x00}, {0x01, 0x00}, {0x02, 0x00}, {0x03, 0x00}, {0x04, 0x00}, {0x04, 0x02}, {0x04, 0x04}, {0x04, 0x06}, 
    {0x04, 0x08}, {0x04, 0x0A}, {0x04, 0x0C}, {0x04, 0x0E}, {0x04, 0x10}, {0x04, 0x12}, {0x04, 0x14}, {0x03, 0x14}, 
    {0x02, 0x14}, {0x01, 0x14}, {0x00, 0x14}, {0x00, 0x12}, {0x00, 0x10}, {0x00, 0x0E}, {0x00, 0x0C}, {0x00, 0x0A}, 
    {0x00, 0x08}, {0x00, 0x06}, {0x00, 0x04}, {0x00, 0x02}, {0x00, 0x00}
};

#define SIZE_BALL_MODEL 9
struct xyPoint ballModel[SIZE_BALL_MODEL] =
{
    {0x01, 0x00}, {0x02, 0x00}, {0x03, 0x01}, {0x03, 0x02}, {0x02, 0x03}, {0x01, 0x03}, {0x00, 0x02}, {0x00, 0x01},
    {0x01, 0x00} 
};

#define SIZE_SCREEN_PART_1 13
struct xyPoint screenPart1[SIZE_SCREEN_PART_1] =
{
    {0x00, 0x80}, {0x00, 0x90}, {0x00, 0xA0}, {0x00, 0xB0}, {0x00, 0xC0}, {0x00, 0xD0}, {0x00, 0xE0}, {0x00, 0xF0}, 
    {0x00, 0xFF}, {0x10, 0xFF}, {0x20, 0xFF}, {0x30, 0xFF}, {0x40, 0xFF}
};

#define SIZE_SCREEN_PART_2 37
struct xyPoint screenPart2[SIZE_SCREEN_PART_2] =
{
    {0x40, 0xFF}, {0x50, 0xFF}, {0x60, 0xFF}, {0x70, 0xFF}, {0x80, 0xFF}, {0x84, 0xFC}, {0x80, 0xF8}, {0x84, 0xF4}, 
    {0x80, 0xF0}, {0x84, 0xEC}, {0x80, 0xE8}, {0x84, 0xE4}, {0x80, 0xE0}, {0x84, 0xDC}, {0x80, 0xD8}, {0x84, 0xD4}, 
    {0x80, 0xD0}, {0x84, 0xCC}, {0x80, 0xC8}, {0x84, 0xC4}, {0x80, 0xC0}, {0x84, 0xBC}, {0x80, 0xB8}, {0x84, 0xB4}, 
    {0x80, 0xB0}, {0x84, 0xAC}, {0x80, 0xA8}, {0x84, 0xA4}, {0x80, 0xA0}, {0x84, 0x9C}, {0x80, 0x98}, {0x84, 0x94}, 
    {0x80, 0x90}, {0x84, 0x8C}, {0x80, 0x88}, {0x84, 0x84}, {0x80, 0x80}
};

#define SIZE_SCREEN_PART_3 6
struct xyPoint screenPart3[SIZE_SCREEN_PART_3] =
{
    {0x80, 0x80}, {0x80, 0xFF}, {0x90, 0xFF}, {0xA0, 0xFF}, {0xB0, 0xFF}, {0xC0, 0xFF}
};

#define SIZE_SCREEN_PART_4 13
struct xyPoint screenPart4[SIZE_SCREEN_PART_4] =
{
    {0xC0, 0xFF}, {0xD0, 0xFF}, {0xE0, 0xFF}, {0xF0, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xF0}, {0xFF, 0xE0}, {0xFF, 0xD0}, 
    {0xFF, 0xC0}, {0xFF, 0xB0}, {0xFF, 0xA0}, {0xFF, 0x90}, {0xFF, 0x80}
};

#define SIZE_SCREEN_PART_5 66
struct xyPoint screenPart5[SIZE_SCREEN_PART_5] =
{
    {0xFF, 0x80}, {0xFF, 0x70}, {0xFF, 0x60}, {0xFF, 0x50}, {0xFF, 0x40}, {0xFF, 0x30}, {0xFF, 0x20}, {0xFF, 0x10}, 
    {0xFF, 0x00}, {0xF0, 0x00}, {0xE0, 0x00}, {0xD0, 0x00}, {0xC0, 0x00}, {0xB0, 0x00}, {0xA0, 0x00}, {0x90, 0x00}, 
    {0x80, 0x00}, {0x84, 0x04}, {0x80, 0x08}, {0x84, 0x0C}, {0x80, 0x10}, {0x84, 0x14}, {0x80, 0x18}, {0x84, 0x1C}, 
    {0x80, 0x20}, {0x84, 0x24}, {0x80, 0x28}, {0x84, 0x2C}, {0x80, 0x30}, {0x84, 0x34}, {0x80, 0x38}, {0x84, 0x3C}, 
    {0x80, 0x40}, {0x84, 0x44}, {0x80, 0x48}, {0x84, 0x4C}, {0x80, 0x50}, {0x84, 0x54}, {0x80, 0x58}, {0x84, 0x5C}, 
    {0x80, 0x60}, {0x84, 0x64}, {0x80, 0x68}, {0x84, 0x6C}, {0x80, 0x70}, {0x84, 0x74}, {0x80, 0x78}, {0x84, 0x7C}, 
    {0x80, 0x80}, {0x80, 0x00}, {0x70, 0x00}, {0x60, 0x00}, {0x50, 0x00}, {0x40, 0x00}, {0x30, 0x00}, {0x20, 0x00}, 
    {0x10, 0x00}, {0x00, 0x00}, {0x00, 0x10}, {0x00, 0x20}, {0x00, 0x30}, {0x00, 0x40}, {0x00, 0x50}, {0x00, 0x60}, 
    {0x00, 0x70}, {0x00, 0x80}
};

#define SIZE_SCORE_UNDERLINE 5
struct xyPoint scoreUnderline[SIZE_SCORE_UNDERLINE] =
{
    {0x00, 0x00}, {0x10, 0x00}, {0x20, 0x00}, {0x10, 0x00}, {0x00, 0x00}
};

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // Object Properties ------------------------------------------------------------------------------------------------------

    // Ball
    float ballPositionX = xyWidth()  / 2.0f - BALL_SIZE * 0.5f;           // X position of the bottom left corner of the ball
    float ballPositionY = xyHeight() / 2.0f - BALL_SIZE * 0.5f;           // Y position of the bottom left corner of the ball

    float ballVelocityX = BALL_START_VELOCITY_X;               // Current x velocity of the ball
    float ballVelocityY = BALL_START_VELOCITY_Y;               // Current y velocity of the ball

    // Game State -------------------------------------------------------------------------------------------------------------

    uint8_t paddle0Wins = 0;                                   // Number of wins by paddle 0
    uint8_t paddle1Wins = 0;                                   // Number of wins by paddle 1

    // Inputs -----------------------------------------------------------------------------------------------------------------

    gpio_init(BUTTON_PIN_PADDLE_0_UP);
    gpio_set_dir(BUTTON_PIN_PADDLE_0_UP, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_PADDLE_0_UP);
    
    gpio_init(BUTTON_PIN_PADDLE_0_DOWN);
    gpio_set_dir(BUTTON_PIN_PADDLE_0_DOWN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_PADDLE_0_DOWN);

    gpio_init(BUTTON_PIN_PADDLE_1_UP);
    gpio_set_dir(BUTTON_PIN_PADDLE_1_UP, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_PADDLE_1_UP);

    gpio_init(BUTTON_PIN_PADDLE_1_DOWN);
    gpio_set_dir(BUTTON_PIN_PADDLE_1_DOWN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_PADDLE_1_DOWN);

    // Object Rendering -------------------------------------------------------------------------------------------------------
    // - Models are rendered in this order to minimize traces between them

    volatile struct xyShape* paddle0 = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, 0x08, xyHeight() / 2.0f - PADDLE_HEIGHT / 2.0f);

    xyRendererRenderShape(screenPart1, SIZE_SCREEN_PART_1, 0x00, 0x00);

    xyRendererRenderShape(scoreUnderline, SIZE_SCORE_UNDERLINE, 0x30, 0xDE);
    
    volatile struct xyShape* score01 = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0x32, 0xE0);
    volatile struct xyShape* score00 = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0x42, 0xE0);
    
    xyRendererRenderShape(screenPart2, SIZE_SCREEN_PART_2, 0x00, 0x00);
    
    volatile struct xyShape* ball = xyRendererRenderShape(ballModel, SIZE_BALL_MODEL, ballPositionX, ballPositionY);
    
    xyRendererRenderShape(screenPart3, SIZE_SCREEN_PART_3, 0x00, 0x00);
    
    xyRendererRenderShape(scoreUnderline, SIZE_SCORE_UNDERLINE, 0xB0, 0xDE);

    volatile struct xyShape* score11 = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0xB2, 0xE0);
    volatile struct xyShape* score10 = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0xC2, 0xE0);
    
    xyRendererRenderShape(screenPart4, SIZE_SCREEN_PART_4, 0x00, 0x00);
    
    volatile struct xyShape* paddle1 = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, xyWidth() - 0x08 - PADDLE_WIDTH, xyHeight() / 2.0f - PADDLE_HEIGHT / 2.0f);
    
    xyRendererRenderShape(screenPart5, SIZE_SCREEN_PART_5, 0x00, 0x00);

    // Event Loop -------------------------------------------------------------------------------------------------------------

    while(true)
    {
        // Update ball position
        ballPositionX += ballVelocityX;
        ballPositionY += ballVelocityY;
        ball->positionX = roundf(ballPositionX);
        ball->positionY = roundf(ballPositionY);

        // Check ball collision with top & bottom
        if(ballPositionY + ballVelocityY < 0.0f)
        {
            ballVelocityY = -ballVelocityY;
        }
        else if(ballPositionY + BALL_SIZE + ballVelocityY >= xyHeight() - 1)
        {
            ballVelocityY = -ballVelocityY;
        }

        // Check ball collision with paddles
        if(ballPositionX + ballVelocityX <= paddle0->positionX + PADDLE_WIDTH && ballPositionY + BALL_SIZE > paddle0->positionY && ballPositionY < paddle0->positionY + PADDLE_HEIGHT)
        {
            // Paddle 0 hit
            ballVelocityX = -PADDLE_BALL_SPEEDUP * ballVelocityX;
            ballVelocityY = ballVelocityY + PADDLE_CURVATURE * (ballPositionY + 0.5f * BALL_SIZE - paddle0->positionY - 0.5f * PADDLE_HEIGHT);
        }
        else if(ballPositionX + ballVelocityX + BALL_SIZE >= paddle1->positionX && ballPositionY + BALL_SIZE > paddle1->positionY && ballPositionY < paddle1->positionY + PADDLE_HEIGHT)
        {
            // Paddle 1 hit
            ballVelocityX = -PADDLE_BALL_SPEEDUP * ballVelocityX;
            ballVelocityY = ballVelocityY + PADDLE_CURVATURE * (ballPositionY + 0.5f * BALL_SIZE - paddle1->positionY - 0.5f * PADDLE_HEIGHT);
        }

        // Check ball collision with left & right (win states)
        if(ballPositionX + ballVelocityX <= 0)
        {
            // Paddle 1 win

            // Reset ball
            ballPositionX = xyWidth()  / 2.0f - BALL_SIZE / 2.0f;
            ballPositionY = xyHeight() / 2.0f - BALL_SIZE / 2.0f;
            ball->positionX = roundf(ballPositionX);
            ball->positionY = roundf(ballPositionY);
            ballVelocityX = BALL_START_VELOCITY_X;
            ballVelocityY = BALL_START_VELOCITY_Y;

            // Update score
            ++paddle1Wins;

            // Display score
            uint8_t digit1 = paddle1Wins - paddle1Wins % 10;
            uint8_t digit0 = paddle1Wins - digit1;
            digit1 /= 10;
            score11->points     = xyShape16x16Ascii    [digit1 + '0'];
            score11->pointCount = xyShapeSize16x16Ascii[digit1 + '0'];
            score10->points     = xyShape16x16Ascii    [digit0 + '0'];
            score10->pointCount = xyShapeSize16x16Ascii[digit0 + '0'];
        }
        else if(ballPositionX + ballVelocityX >= 255)
        {
            // Paddle 0 win

            // Reset ball
            ballPositionX = xyWidth()  / 2.0f - BALL_SIZE / 2.0f;
            ballPositionY = xyHeight() / 2.0f - BALL_SIZE / 2.0f;
            ball->positionX = roundf(ballPositionX);
            ball->positionY = roundf(ballPositionY);
            ballVelocityX = -BALL_START_VELOCITY_X;
            ballVelocityY = BALL_START_VELOCITY_Y;

            // Update score
            ++paddle0Wins;

            // Display score
            uint8_t digit1 = paddle0Wins - paddle0Wins % 10;
            uint8_t digit0 = paddle0Wins - digit1;
            digit1 /= 10;
            score01->points     = xyShape16x16Ascii    [digit1 + '0'];
            score01->pointCount = xyShapeSize16x16Ascii[digit1 + '0'];
            score00->points     = xyShape16x16Ascii    [digit0 + '0'];
            score00->pointCount = xyShapeSize16x16Ascii[digit0 + '0'];
        }
        
        // Update paddle 0 position
        if(!gpio_get(BUTTON_PIN_PADDLE_0_UP))
        {
            if((int16_t)paddle0->positionY + PADDLE_HEIGHT + PADDLE_VELOCITY_Y < xyHeight() - 1) paddle0->positionY += PADDLE_VELOCITY_Y;
        }
        else if(!gpio_get(BUTTON_PIN_PADDLE_0_DOWN))
        {
            if((int16_t)paddle0->positionY - PADDLE_VELOCITY_Y > 0) paddle0->positionY -= PADDLE_VELOCITY_Y;
        }

        // Update paddle 1 position
        if(!gpio_get(BUTTON_PIN_PADDLE_1_UP))
        {
            if((int16_t)paddle1->positionY + PADDLE_HEIGHT + PADDLE_VELOCITY_Y < xyHeight() - 1) paddle1->positionY += PADDLE_VELOCITY_Y;
        }
        else if(!gpio_get(BUTTON_PIN_PADDLE_1_DOWN))
        {
            if((int16_t)paddle1->positionY - PADDLE_VELOCITY_Y > 0) paddle1->positionY -= PADDLE_VELOCITY_Y;
        }

        // Event loop period
        sleep_ms(30);
    }
}