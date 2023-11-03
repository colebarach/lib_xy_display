// Pong Programming Example ---------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Implementation of the videogame 'pong' using the X-Y rendering library.

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include "xy.h"

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
uint16_t paddleModel[SIZE_PADDLE_MODEL] =
{
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0204, 0x0404, 0x0604,
    0x0804, 0x0A04, 0x0C04, 0x0E04, 0x1004, 0x1204, 0x1404, 0x1403,
    0x1402, 0x1401, 0x1400, 0x1200, 0x1000, 0x0E00, 0x0C00, 0x0A00,
    0x0800, 0x0600, 0x0400, 0x0200, 0x0000
};

#define SIZE_BALL_MODEL 9
uint16_t ballModel[SIZE_BALL_MODEL] =
{
    0x0001, 0x0002, 0x0103, 0x0203, 0x0302, 0x0301, 0x0200, 0x0100,
    0x0001
};

#define SIZE_SCREEN_PART_1 13
uint16_t screenPart1[SIZE_SCREEN_PART_1] =
{
    0x8000, 0x9000, 0xA000, 0xB000, 0xC000, 0xD000, 0xE000, 0xF000,
    0xFF00, 0xFF10, 0xFF20, 0xFF30, 0xFF40
};

#define SIZE_SCREEN_PART_2 37
uint16_t screenPart2[SIZE_SCREEN_PART_2] =
{
    0xFF40, 0xFF50, 0xFF60, 0xFF70, 0xFF80, 0xFC84, 0xF880, 0xF484,
    0xF080, 0xEC84, 0xE880, 0xE484, 0xE080, 0xDC84, 0xD880, 0xD484,
    0xD080, 0xCC84, 0xC880, 0xC484, 0xC080, 0xBC84, 0xB880, 0xB484,
    0xB080, 0xAC84, 0xA880, 0xA484, 0xA080, 0x9C84, 0x9880, 0x9484,
    0x9080, 0x8C84, 0x8880, 0x8484, 0x8080
};

#define SIZE_SCREEN_PART_3 6
uint16_t screenPart3[SIZE_SCREEN_PART_3] =
{
    0x8080, 0xFF80, 0xFF90, 0xFFA0, 0xFFB0, 0xFFC0
};

#define SIZE_SCREEN_PART_4 13
uint16_t screenPart4[SIZE_SCREEN_PART_4] =
{
    0xFFC0, 0xFFD0, 0xFFE0, 0xFFF0, 0xFFFF, 0xF0FF, 0xE0FF, 0xD0FF,
    0xC0FF, 0xB0FF, 0xA0FF, 0x90FF, 0x80FF
};

#define SIZE_SCREEN_PART_5 66
uint16_t screenPart5[SIZE_SCREEN_PART_5] =
{
    0x80FF, 0x70FF, 0x60FF, 0x50FF, 0x40FF, 0x30FF, 0x20FF, 0x10FF,
    0x00FF, 0x00F0, 0x00E0, 0x00D0, 0x00C0, 0x00B0, 0x00A0, 0x0090,
    0x0080, 0x0484, 0x0880, 0x0C84, 0x1080, 0x1484, 0x1880, 0x1C84,
    0x2080, 0x2484, 0x2880, 0x2C84, 0x3080, 0x3484, 0x3880, 0x3C84,
    0x4080, 0x4484, 0x4880, 0x4C84, 0x5080, 0x5484, 0x5880, 0x5C84,
    0x6080, 0x6484, 0x6880, 0x6C84, 0x7080, 0x7484, 0x7880, 0x7C84,
    0x8080, 0x0080, 0x0070, 0x0060, 0x0050, 0x0040, 0x0030, 0x0020,
    0x0010, 0x0000, 0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000,
    0x7000, 0x8000
};

#define SIZE_SCORE_UNDERLINE 5
uint16_t scoreUnderline[SIZE_SCORE_UNDERLINE] =
{
    0x0000, 0x0010, 0x0020, 0x0010, 0x0000
};

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // Object Properties ------------------------------------------------------------------------------------------------------

    // Ball
    float ballPositionX = 128.0f - BALL_SIZE * 0.5f;           // X position of the bottom left corner of the ball
    float ballPositionY = 128.0f - BALL_SIZE * 0.5f;           // Y position of the bottom left corner of the ball

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
    // - Models are rendered in this order to minimize traces between them, the points rendered are to keep traces to the edge
    //   of the screen

    volatile struct xyShape* paddle0 = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, 0x08, 0x80 - PADDLE_HEIGHT / 2);

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
    
    volatile struct xyShape* paddle1 = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, 0xF8 - PADDLE_WIDTH, 0x80 - PADDLE_HEIGHT / 2);
    
    xyRendererRenderShape(screenPart5, SIZE_SCREEN_PART_5, 0x00, 0x00);

    // Event Loop -------------------------------------------------------------------------------------------------------------

    while(1)
    {
        // Update ball position
        ballPositionX += ballVelocityX;
        ballPositionY += ballVelocityY;
        ball->xPosition = roundf(ballPositionX);
        ball->yPosition = roundf(ballPositionY);

        // Check ball collision with top & bottom
        if(ballPositionY + ballVelocityY < 0.0f)
        {
            ballVelocityY = -ballVelocityY;
        }
        else if(ballPositionY + BALL_SIZE + ballVelocityY >= 255.0f)
        {
            ballVelocityY = -ballVelocityY;
        }

        // Check ball collision with paddles
        if(ballPositionX + ballVelocityX <= paddle0->xPosition + PADDLE_WIDTH && ballPositionY + BALL_SIZE > paddle0->yPosition && ballPositionY < paddle0->yPosition + PADDLE_HEIGHT)
        {
            // Paddle 0 hit
            ballVelocityX = -PADDLE_BALL_SPEEDUP * ballVelocityX;
            ballVelocityY = ballVelocityY + PADDLE_CURVATURE * (ballPositionY + 0.5f * BALL_SIZE - paddle0->yPosition - 0.5f * PADDLE_HEIGHT);
        }
        else if(ballPositionX + ballVelocityX + BALL_SIZE >= paddle1->xPosition && ballPositionY + BALL_SIZE > paddle1->yPosition && ballPositionY < paddle1->yPosition + PADDLE_HEIGHT)
        {
            // Paddle 1 hit
            ballVelocityX = -PADDLE_BALL_SPEEDUP * ballVelocityX;
            ballVelocityY = ballVelocityY + PADDLE_CURVATURE * (ballPositionY + 0.5f * BALL_SIZE - paddle1->yPosition - 0.5f * PADDLE_HEIGHT);
        }

        // Check ball collision with left & right (win states)
        if(ballPositionX + ballVelocityX <= 0)
        {
            // Paddle 1 win

            // Reset ball
            ballPositionX = 128.0f - BALL_SIZE * 0.5f;
            ballPositionY = 128.0f - BALL_SIZE * 0.5f;
            ball->xPosition = roundf(ballPositionX);
            ball->yPosition = roundf(ballPositionY);
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
            ballPositionX = 128.0f - BALL_SIZE * 0.5f;
            ballPositionY = 128.0f - BALL_SIZE * 0.5f;
            ball->xPosition = roundf(ballPositionX);
            ball->yPosition = roundf(ballPositionY);
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
            if((int16_t)paddle0->yPosition + PADDLE_HEIGHT + PADDLE_VELOCITY_Y < 255) paddle0->yPosition += PADDLE_VELOCITY_Y;
        }
        else if(!gpio_get(BUTTON_PIN_PADDLE_0_DOWN))
        {
            if((int16_t)paddle0->yPosition - PADDLE_VELOCITY_Y > 0) paddle0->yPosition -= PADDLE_VELOCITY_Y;
        }

        // Update paddle 1 position
        if(!gpio_get(BUTTON_PIN_PADDLE_1_UP))
        {
            if((int16_t)paddle1->yPosition + PADDLE_HEIGHT + PADDLE_VELOCITY_Y < 255) paddle1->yPosition += PADDLE_VELOCITY_Y;
        }
        else if(!gpio_get(BUTTON_PIN_PADDLE_1_DOWN))
        {
            if((int16_t)paddle1->yPosition - PADDLE_VELOCITY_Y > 0) paddle1->yPosition -= PADDLE_VELOCITY_Y;
        }

        // Event loop period
        sleep_ms(30);
    }
}