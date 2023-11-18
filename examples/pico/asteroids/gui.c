// Header
#include "gui.h"

// Models ---------------------------------------------------------------------------------------------------------------------

struct xyPoint lifeIconModel[SIZE_LIFE_ICON_MODEL] =
{
    {0x00, 0x00}, {0x01, 0x03}, {0x03, 0x03}, {0x06, 0x03}, {0x09, 0x03}, {0x0B, 0x03}, {0x09, 0x03}, {0x06, 0x03},
    {0x03, 0x03}, {0x01, 0x03}, {0x03, 0x08}, {0x06, 0x10}, {0x09, 0x08}, {0x0B, 0x03}, {0x0C, 0x00}
};

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Binary to Digits
// - Call to convert a binary value into a set of digits.
// - Populates the 'digits' array with 0 being the least significant and 'digitCount - 1' being the most.
void binaryToDigits(uint32_t value, uint32_t* digits, uint16_t digitCount, uint16_t numericBase);

// Function Definitions -------------------------------------------------------------------------------------------------------

void scoreInitialize(scoreCounter_t* scoreCounter, xyCoord positionX, xyCoord positionY)
{
    // Add digits to render stack
    for(uint16_t index = 0; index < SCORE_COUNTER_SIZE; ++index)
    {
        scoreCounter->digits[index] = xyRendererRenderChar('0', positionX + (SCORE_COUNTER_SIZE - index - 1) * 0x10, positionY);
    }
}

void scoreUpdate(scoreCounter_t* score, uint32_t scoreValue)
{
    // Get digit values
    uint32_t digits[SCORE_COUNTER_SIZE];
    binaryToDigits(scoreValue, digits, SCORE_COUNTER_SIZE, 10);

    // Update models
    for(uint16_t index = 0; index < SCORE_COUNTER_SIZE; ++index)
    {
        score->digits[index]->points     = xyShape16x16Ascii[    digits[index] + '0'];
        score->digits[index]->pointCount = xyShapeSize16x16Ascii[digits[index] + '0'];
    }
}

void lifeInitialize(lifeCounter_t* lifeCounter, xyCoord positionX, xyCoord positionY)
{
    // Add icons to render stack
    for(uint16_t index = 0; index < LIFE_COUNTER_SIZE; ++index)
    {
        xyCoord iconPositionX = positionX + ((LIFE_COUNTER_SIZE - index - 1) % 6) * 0x10;
        xyCoord iconPositionY = positionY - (index / 6) * 0x14;

        lifeCounter->lives[index] = xyRendererRenderShape(lifeIconModel, SIZE_LIFE_ICON_MODEL, iconPositionX, iconPositionY);
        lifeCounter->lives[index]->visible = false;
    }
}

void lifeUpdate(lifeCounter_t* lifeCounter, int8_t lifeCount)
{
    // Display remaining icons
    for(uint16_t index = 0; index < LIFE_COUNTER_SIZE; ++index)
    {
        lifeCounter->lives[index]->visible = (index < lifeCount);
    }
}

void binaryToDigits(uint32_t value, uint32_t* digits, uint16_t digitCount, uint16_t numericBase)
{
    // Iterate each digit, starting at most significant.
    for(int16_t index = digitCount - 1; index >= 0; --index)
    {
        uint32_t exponent = 1;
        for(uint32_t exponentIndex = 0; exponentIndex < index; ++exponentIndex) exponent *= numericBase;

        // Get weighted digit value (I.E abcd => a000).
        digits[index] = value - value % exponent;

        // Remove higher significance digits.
        for(uint32_t subIndex = index + 1; subIndex < digitCount; ++subIndex)
        {
            digits[index] -= digits[subIndex];
        }
    }

    // Scale digits down to equal significance.
    for(int32_t index = digitCount - 1; index >= 0; --index)
    {
        uint32_t exponent = 1;
        for(uint32_t exponentIndex = 0; exponentIndex < index; ++exponentIndex) exponent *= numericBase;

        digits[index] /= exponent;
    }
}
