// Header
#include "gui.h"

// Function Prototypes --------------------------------------------------------------------------------------------------------

// Binary to Digits
// - Call to convert a binary value into a set of digits.
// - Populates the `digits` array with 0 being the least significant and 'digitCount - 1' being the most.
void binaryToDigits(uint32_t value, uint16_t* digits, uint16_t digitCount, uint16_t numericBase);

// Function Definitions -------------------------------------------------------------------------------------------------------

void scoreInitialize(score_t* score, xyCoord positionX, xyCoord positionY)
{
    score->digit0 = xyRendererRenderChar('0', positionX + 0x50, positionY);
    score->digit1 = xyRendererRenderChar('0', positionX + 0x40, positionY);
    score->digit2 = xyRendererRenderChar('0', positionX + 0x30, positionY);
    score->digit3 = xyRendererRenderChar('0', positionX + 0x20, positionY);
    score->digit4 = xyRendererRenderChar('0', positionX + 0x10, positionY);
    score->digit5 = xyRendererRenderChar('0', positionX + 0x00, positionY);
}

void scoreUpdate(score_t* score, uint32_t scoreValue)
{
    uint16_t digits[6];
    binaryToDigits(scoreValue, digits, 6, 10);

    score->digit0->points     = xyShape16x16Ascii[    digits[0] + '0'];
    score->digit0->pointCount = xyShapeSize16x16Ascii[digits[0] + '0'];
    score->digit1->points     = xyShape16x16Ascii[    digits[1] + '0'];
    score->digit1->pointCount = xyShapeSize16x16Ascii[digits[1] + '0'];
    score->digit2->points     = xyShape16x16Ascii[    digits[2] + '0'];
    score->digit2->pointCount = xyShapeSize16x16Ascii[digits[2] + '0'];
    score->digit3->points     = xyShape16x16Ascii[    digits[3] + '0'];
    score->digit3->pointCount = xyShapeSize16x16Ascii[digits[3] + '0'];
    score->digit4->points     = xyShape16x16Ascii[    digits[4] + '0'];
    score->digit4->pointCount = xyShapeSize16x16Ascii[digits[4] + '0'];
    score->digit5->points     = xyShape16x16Ascii[    digits[5] + '0'];
    score->digit5->pointCount = xyShapeSize16x16Ascii[digits[5] + '0'];
}

void binaryToDigits(uint32_t value, uint16_t* digits, uint16_t digitCount, uint16_t numericBase)
{
    // Iterate each digit, starting at most significant.
    for(int16_t index = digitCount - 1; index >= 0; --index)
    {
        uint16_t exponent = 1;
        for(uint16_t exponentIndex = 0; exponentIndex < index; ++exponentIndex) exponent *= numericBase;

        // Get weighted digit value (I.E abcd => a000).
        digits[index] = value - value % exponent;

        // Remove higher significance digits.
        for(uint16_t subIndex = index + 1; subIndex < digitCount; ++subIndex)
        {
            digits[index] -= digits[subIndex];
        }
    }

    // Scale digits down to equal significance.
    for(int16_t index = digitCount - 1; index >= 0; --index)
    {
        uint16_t exponent = 1;
        for(uint16_t exponentIndex = 0; exponentIndex < index; ++exponentIndex) exponent *= numericBase;

        digits[index] /= exponent;
    }
}
