#ifndef VECTOR_XY_H
#define VECTOR_XY_H

// CMSIS Libraries
#include "stm32f3xx.h"

// Registers ------------------------------------------------------------------------------------------------------------------

#define XY_CURSOR GPIOB->ODR // Cursor Register, holds the XY position of the cursor.
// HI byte - Unsigned integer, represents y position
// LO byte - Unsigned integer, represents x position

// Adding to and subtracting from the same register in a single operation -----------------------------------------------------
// - The XY_CURSOR register allows the X and Y coordinates to be updated at the same time, although in effect this is only true if
// the operation is identical for the two. To performing different operations on the HI and LO words requires multiple
// instruction cycles, which is not ideal. To prevent this, the principles of the 2's complement may be leveraged. Adding a
// large integer has the same effect as subtracting a small one, due to overflow.
//
// - Adding X
// XY_CURSOR += N
//
// - Subtracting X
// XY_CURSOR += 2^16 - N
//
// - Adding Y
// XY_CURSOR += 2^8 * N
//
// - Subtracting Y
// XY_CURSOR += 2^16 - 2^8 * N

#define ADD_X(x) x
#define SUB_X(x) 0x0000 - x
#define ADD_Y(y) (y << 8)
#define SUB_Y(y) 0x0000 - (y << 8)

// Characters -----------------------------------------------------------------------------------------------------------------

#define XY_DRAW_CHAR_16x16_NULL()       \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR -= 0x0806; /*  -6,  -8 */   \
  XY_CURSOR -= 0x0806; /*  -6,  -8 */   \
  XY_CURSOR += 0x1000; /*   0,  16 */   \
  XY_CURSOR += 0x000C; /*  12,   0 */   \
  XY_CURSOR -= 0x1000; /*   0, -16 */   \
  XY_CURSOR -= 0x000C; /* -12,   0 */   \
  XY_CURSOR += 0x0010; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_SPACE()      \
  XY_CURSOR += 0x0010; /*   0,  16 */   \

#define XY_DRAW_CHAR_16x16_A()          \
  XY_CURSOR += 0x0803; /*   3,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0803; /*   3,   8 */   \
  XY_CURSOR += 0xF803; /*   3,  -8 */   \
  XY_CURSOR += 0xF803; /*   3,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_B()          \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x03FC; /*  -4.   4 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x03FC; /*  -4.   4 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR -= 0x1000; /*   0, -16 */   \
  XY_CURSOR += 0x0010; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_C()          \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x000C; /*  12,   0 */   \

#define XY_DRAW_CHAR_16x16_D()          \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0000; /*   0,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0010; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_E()          \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x1000; /*   0, -16 */   \
  XY_CURSOR += 0x0016; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_F()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x1000; /*   0, -16 */   \
  XY_CURSOR += 0x0010; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_G()          \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0200; /*   0,   2 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR -= 0x0200; /*   0,  -2 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x000C; /*  12,   0 */   \

#define XY_DRAW_CHAR_16x16_H()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_I()          \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_J()          \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0C00; /*   0,  12 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR -= 0x0C00; /*   0, -12 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR += 0x000C; /*  12,   0 */   \

#define XY_DRAW_CHAR_16x16_K()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0406; /*   6,   4 */   \
  XY_CURSOR += 0x0406; /*   6,   4 */   \
  XY_CURSOR -= 0x0406; /*  -6,  -4 */   \
  XY_CURSOR -= 0x0406; /*  -6,  -4 */   \
  XY_CURSOR += 0xFC06; /*   6,  -4 */   \
  XY_CURSOR += 0xFC06; /*   6,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_L()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_M()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_N()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_O()          \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x000C; /*  12,   0 */   \

#define XY_DRAW_CHAR_16x16_P()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0010; /*  16,   0 */   \

#define XY_DRAW_CHAR_16x16_Q()          \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_R()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0008; /*  -8,   0 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0xFC06; /*   6,  -4 */   \
  XY_CURSOR += 0xFC06; /*   6,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_S()          \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR -= 0x0004; /*  -4,   0 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \

#define XY_DRAW_CHAR_16x16_T()          \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x000A; /*  10,   0 */   \

#define XY_DRAW_CHAR_16x16_U()          \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x03FC; /*  -4,   4 */   \
  XY_CURSOR += 0x0600; /*   0,   6 */   \
  XY_CURSOR += 0x0600; /*   0,   6 */   \
  XY_CURSOR -= 0x0600; /*   0,  -6 */   \
  XY_CURSOR -= 0x0600; /*   0,  -6 */   \
  XY_CURSOR += 0xFC04; /*   4,  -4 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \
  XY_CURSOR += 0x0404; /*   4,   4 */   \
  XY_CURSOR += 0x0600; /*   0,   6 */   \
  XY_CURSOR += 0x0600; /*   0,   6 */   \
  XY_CURSOR -= 0x0600; /*   0,  -6 */   \
  XY_CURSOR -= 0x0600; /*   0,  -6 */   \
  XY_CURSOR -= 0x0404; /*  -4,  -4 */   \
  XY_CURSOR += 0x0008; /*   8,   0 */   \

#define XY_DRAW_CHAR_16x16_V()          \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x07FD; /*  -3,   8 */   \
  XY_CURSOR += 0x07FD; /*  -3,   8 */   \
  XY_CURSOR += 0xF803; /*   3,  -8 */   \
  XY_CURSOR += 0xF803; /*   3,  -8 */   \
  XY_CURSOR += 0x0803; /*   3,   8 */   \
  XY_CURSOR += 0x0803; /*   3,   8 */   \
  XY_CURSOR -= 0x0803; /*  -3,  -8 */   \
  XY_CURSOR -= 0x0803; /*  -3,  -8 */   \
  XY_CURSOR += 0x000A; /*  10,   0 */   \

#define XY_DRAW_CHAR_16x16_W()          \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR += 0x0800; /*   0,   8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR -= 0x0800; /*   0,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_X()          \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR -= 0x0806; /*   6,   8 */   \
  XY_CURSOR += 0x07FA; /*  -6,   8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0xF806; /*   6,  -8 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

#define XY_DRAW_CHAR_16x16_Y()          \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0A00; /*   0,  10 */   \
  XY_CURSOR += 0x05FA; /*  -6,   6 */   \
  XY_CURSOR += 0xFA06; /*   6,  -6 */   \
  XY_CURSOR += 0x0606; /*   6,   6 */   \
  XY_CURSOR -= 0x0606; /*  -6,  -6 */   \
  XY_CURSOR -= 0x0A00; /*   0, -10 */   \
  XY_CURSOR += 0x000A; /*  10,   0 */   \

#define XY_DRAW_CHAR_16x16_Z()          \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR += 0x0806; /*   6,   8 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR -= 0x0006; /*  -6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR -= 0x0806; /*  -6,  -8 */   \
  XY_CURSOR -= 0x0806; /*  -6,  -8 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0006; /*   6,   0 */   \
  XY_CURSOR += 0x0004; /*   4,   0 */   \

// Demos ----------------------------------------------------------------------------------------------------------------------

void xyDemoAlphabet()
{
	XY_CURSOR = 0x0000;

	XY_DRAW_CHAR_16x16_Y();
	XY_DRAW_CHAR_16x16_Z();

	XY_CURSOR -= 0x0020;
	XY_CURSOR += 0X1400;

	XY_DRAW_CHAR_16x16_S();
	XY_DRAW_CHAR_16x16_T();
	XY_DRAW_CHAR_16x16_U();
	XY_DRAW_CHAR_16x16_V();
	XY_DRAW_CHAR_16x16_W();
	XY_DRAW_CHAR_16x16_X();

	XY_CURSOR -= 0x0060;
	XY_CURSOR += 0X1400;

	XY_DRAW_CHAR_16x16_M();
	XY_DRAW_CHAR_16x16_N();
	XY_DRAW_CHAR_16x16_O();
	XY_DRAW_CHAR_16x16_P();
	XY_DRAW_CHAR_16x16_Q();
	XY_DRAW_CHAR_16x16_R();

	XY_CURSOR -= 0x0060;
	XY_CURSOR += 0X1400;

	XY_DRAW_CHAR_16x16_G();
	XY_DRAW_CHAR_16x16_H();
	XY_DRAW_CHAR_16x16_I();
	XY_DRAW_CHAR_16x16_J();
	XY_DRAW_CHAR_16x16_K();
	XY_DRAW_CHAR_16x16_L();

	XY_CURSOR -= 0x0060;
	XY_CURSOR += 0X1400;

	XY_DRAW_CHAR_16x16_A();
	XY_DRAW_CHAR_16x16_B();
	XY_DRAW_CHAR_16x16_C();
	XY_DRAW_CHAR_16x16_D();
	XY_DRAW_CHAR_16x16_E();
	XY_DRAW_CHAR_16x16_F();

	XY_CURSOR -= 0x0060;
	XY_CURSOR -= 0x5000;
}

void xyDemoGrid()
{
	XY_CURSOR = 0x0000;

	for(int x = 0; x < 16; ++x)
	{
		for(int y = 0; y < 16; ++y)
		{
			XY_CURSOR += 0x1000;
		}
		for(int y = 0; y < 0; ++y)
		{
			XY_CURSOR -= 0x1000;
		}

		XY_CURSOR += 0x0010;
	}

	for(int y = 0; y < 16; ++y)
		{
			for(int x = 0; x < 16; ++x)
			{
				XY_CURSOR += 0x0010;
			}
			for(int x = 0; x < 0; ++x)
			{
				XY_CURSOR -= 0x0010;
			}

			XY_CURSOR += 0x1000;
		}
}

void xyDemoHilbertCurve(int depth, int scale, int rotation, int direction)
{
	if(depth == 0) return;

	if(rotation == 0)
	{
		if(direction == 0)
		{
			xyDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 3, 1);
		}
		else
		{
			xyDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 1, 0);
		}
	}
	else if(rotation == 1)
	{
		if(direction == 0)
		{
			xyDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 0, 1);
		}
		else
		{
			xyDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 2, 0);
		}
	}
	else if(rotation == 2)
	{
		if(direction == 0)
		{
			xyDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 1, 1);
		}
		else
		{
			xyDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 3, 0);
		}
	}
	else
	{
		if(direction == 0)
		{
			xyDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale;
			xyDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 2, 1);
		}
		else
		{
			xyDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR -= scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR -= scale;
			xyDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR += scale << 8;
			xyDemoHilbertCurve(depth - 1, scale, 0, 0);
		}
	}
}

#endif // VECTOR_XY_H
