#include "xy.h"

#include <math.h>

int main()
{
    xyRendererInitialize();

    // Models -----------------------------------------------------------------------------------------------------------------

    #define SIZE_PADDLE_MODEL 5
    uint16_t paddleModel[SIZE_PADDLE_MODEL] =
    {
        0x0000, 0x0004, 0x1004, 0x1000, 0x0000
    };

    #define SIZE_BALL_MODEL 5
    uint16_t ballModel[SIZE_BALL_MODEL] =
    {
        0x0000, 0x0004, 0x0404, 0x0400, 0x0000
    };

    // Model Collision --------------------------------------------------------------------------------------------------------

    uint8_t paddleHeight = 0x10;
    uint8_t paddleWidth  = 0x04;
    uint8_t ballSize     = 0x04;

    // Rendering --------------------------------------------------------------------------------------------------------------

                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0x00, 0xFF);
    volatile struct xyShape* paddle0  = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, 0x04, 0x78);
                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0x00, 0xFF);
    volatile struct xyShape* score01  = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0x32, 0xE0);
    volatile struct xyShape* score00  = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0x42, 0xE0);
                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0x80, 0xFF);
    volatile struct xyShape* ball     = xyRendererRenderShape(ballModel,   SIZE_BALL_MODEL,   0x80, 0x80);
                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0x80, 0xFF);
    volatile struct xyShape* score11  = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0xB2, 0xE0);
    volatile struct xyShape* score10  = xyRendererRenderShape(xyShape16x16Ascii['0'], xyShapeSize16x16Ascii['0'], 0xC2, 0xE0);
                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0xFF, 0xFF);
    volatile struct xyShape* paddle1  = xyRendererRenderShape(paddleModel, SIZE_PADDLE_MODEL, 0xF8, 0x78);
                                        xyRendererRenderShape(xyShapePoint, XY_SHAPE_SIZE_POINT, 0xFF, 0xFF);

    // Object Properties ------------------------------------------------------------------------------------------------------

    float ballVelocityX    = 2;
    float ballVelocityY    = 0;
    int16_t paddleVelocity = 2;

    // Game State -------------------------------------------------------------------------------------------------------------

    uint8_t paddle0Wins = 0;
    uint8_t paddle1Wins = 0;

    // Game Rules -------------------------------------------------------------------------------------------------------------

    float ballSpeedup = 1.2f;
    float paddleWeight = 0.1f;

    // Controls ---------------------------------------------------------------------------------------------------------------

    gpio_init(18); gpio_set_dir(18, GPIO_IN); gpio_pull_up(18); // Paddle 0 up
    gpio_init(19); gpio_set_dir(19, GPIO_IN); gpio_pull_up(19); // Paddle 0 down
    gpio_init(20); gpio_set_dir(20, GPIO_IN); gpio_pull_up(20); // Paddle 1 up
    gpio_init(21); gpio_set_dir(21, GPIO_IN); gpio_pull_up(21); // Paddle 1 down

    // Event Loop -------------------------------------------------------------------------------------------------------------

    while(1)
    {
        // Update ball position
        ball->xPosition = roundf((float)ball->xPosition + ballVelocityX);
        ball->yPosition = roundf((float)ball->yPosition + ballVelocityY);

        // Check ball collision with top & bottom
        if((float)ball->yPosition + ballVelocityY < 0.0f)
        {
            ballVelocityY = -ballVelocityY;
        }
        else if(ball->yPosition + ballSize + ballVelocityY >= 255.0f && ballVelocityY > 0.0f)
        {
            ballVelocityY = -ballVelocityY;
        }

        // Check ball collision with paddles
        if(ball->xPosition + ballVelocityX <= paddle0->xPosition + paddleWidth && ball->yPosition + ballSize > paddle0->yPosition && ball->yPosition < paddle0->yPosition + paddleHeight)
        {
            // Paddle 0 hit
            ballVelocityX = -ballSpeedup * ballVelocityX;
            ballVelocityY = ballVelocityY + paddleWeight * (ball->yPosition + 0.5f * ballSize - paddle0->yPosition - 0.5f * paddleHeight);
        }
        else if(ball->xPosition + ballVelocityX >= paddle1->xPosition - ballSize && ball->yPosition + ballSize > paddle1->yPosition && ball->yPosition < paddle1->yPosition + paddleHeight)
        {
            // Paddle 1 hit
            ballVelocityX = -ballSpeedup * ballVelocityX;
            ballVelocityY = ballVelocityY + paddleWeight * (ball->yPosition + 0.5f * ballSize - paddle1->yPosition - 0.5f * paddleHeight);
        }

        // Check ball collision with left & right (win states)
        if(ball->xPosition + ballVelocityX <= 0)
        {
            // Paddle 1 win

            // Reset ball
            ball->xPosition = 0x80;
            ball->yPosition = 0x80;
            ballVelocityX = 1;
            ballVelocityY = 0;

            // Update score
            ++paddle1Wins;

            uint8_t digit1 = paddle1Wins - paddle1Wins % 10;
            uint8_t digit0 = paddle1Wins - digit1;
            digit1 /= 10;
            score11->points     = xyShape16x16Ascii    [digit1 + '0'];
            score11->pointCount = xyShapeSize16x16Ascii[digit1 + '0'];
            score10->points     = xyShape16x16Ascii    [digit0 + '0'];
            score10->pointCount = xyShapeSize16x16Ascii[digit0 + '0'];
        }
        else if(ball->xPosition + ballVelocityX >= 255)
        {
            // Paddle 0 win

            // Reset ball
            ball->xPosition = 0x80;
            ball->yPosition = 0x80;
            ballVelocityX = -1;
            ballVelocityY = 0;

            // Update score
            ++paddle0Wins;

            uint8_t digit1 = paddle0Wins - paddle0Wins % 10;
            uint8_t digit0 = paddle0Wins - digit1;
            digit1 /= 10;
            score01->points     = xyShape16x16Ascii    [digit1 + '0'];
            score01->pointCount = xyShapeSize16x16Ascii[digit1 + '0'];
            score00->points     = xyShape16x16Ascii    [digit0 + '0'];
            score00->pointCount = xyShapeSize16x16Ascii[digit0 + '0'];
        }

        // Update paddle 0 position
        if(!gpio_get(18))
        {
            if(paddle0->yPosition + paddleHeight + paddleVelocity < 255) paddle0->yPosition += paddleVelocity;
        }
        else if(!gpio_get(19))
        {
            if(paddle0->yPosition - paddleVelocity >= 0) paddle0->yPosition -= paddleVelocity;
        }

        // Update paddle 1 position
        if(!gpio_get(20))
        {
            if(paddle1->yPosition + paddleHeight + paddleVelocity < 255) paddle1->yPosition += paddleVelocity;
        }
        else if(!gpio_get(21))
        {
            if(paddle1->yPosition - paddleVelocity >= 0) paddle1->yPosition -= paddleVelocity;
        }

        // Event loop period
        sleep_ms(30);
    }
}