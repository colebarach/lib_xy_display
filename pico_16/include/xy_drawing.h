// #ifndef XY_DRAWING_H
// #define XY_DRAWING_H

// // X-Y Drawing ----------------------------------------------------------------------------------------------------------------
// // 
// // Author: Cole Barach
// // 
// // Description: Macros and functions responsible for synchronously drawing symbols. Draw in this context means for the CPU to
// // be in direct control of the output. This should only be done in minimal applications, see xy_rendering.h for a more robust
// // method of displaying data.

// // Includes -------------------------------------------------------------------------------------------------------------------

// #include "xy_hardware.h"

// // Macros ---------------------------------------------------------------------------------------------------------------------

// #define XY_DRAW_CHAR_16x16_NULL()                   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR -= 0x0806; XY_DELAY(); /*  -6,  -8 */   \
//   XY_CURSOR -= 0x0806; XY_DELAY(); /*  -6,  -8 */   \
//   XY_CURSOR += 0x1000; XY_DELAY(); /*   0,  16 */   \
//   XY_CURSOR += 0x000C; XY_DELAY(); /*  12,   0 */   \
//   XY_CURSOR -= 0x1000; XY_DELAY(); /*   0, -16 */   \
//   XY_CURSOR -= 0x000C; XY_DELAY(); /* -12,   0 */   \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_SPACE()                  \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*   0,  16 */   \

// #define XY_DRAW_CHAR_16x16_A()                      \
//   XY_CURSOR += 0x0803; XY_DELAY(); /*   3,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0803; XY_DELAY(); /*   3,   8 */   \
//   XY_CURSOR += 0xF803; XY_DELAY(); /*   3,  -8 */   \
//   XY_CURSOR += 0xF803; XY_DELAY(); /*   3,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_B()                      \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4.   4 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4.   4 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR -= 0x1000; XY_DELAY(); /*   0, -16 */   \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_C()                      \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x000C; XY_DELAY(); /*  12,   0 */   \

// #define XY_DRAW_CHAR_16x16_D()                      \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_E()                      \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x1000; XY_DELAY(); /*   0, -16 */   \
//   XY_CURSOR += 0x0016; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_F()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x1000; XY_DELAY(); /*   0, -16 */   \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_G()                      \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0200; XY_DELAY(); /*   0,   2 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR -= 0x0200; XY_DELAY(); /*   0,  -2 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x000C; XY_DELAY(); /*  12,   0 */   \

// #define XY_DRAW_CHAR_16x16_H()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_I()                      \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_J()                      \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0C00; XY_DELAY(); /*   0,  12 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR -= 0x0C00; XY_DELAY(); /*   0, -12 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR += 0x000C; XY_DELAY(); /*  12,   0 */   \

// #define XY_DRAW_CHAR_16x16_K()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0406; XY_DELAY(); /*   6,   4 */   \
//   XY_CURSOR += 0x0406; XY_DELAY(); /*   6,   4 */   \
//   XY_CURSOR -= 0x0406; XY_DELAY(); /*  -6,  -4 */   \
//   XY_CURSOR -= 0x0406; XY_DELAY(); /*  -6,  -4 */   \
//   XY_CURSOR += 0xFC06; XY_DELAY(); /*   6,  -4 */   \
//   XY_CURSOR += 0xFC06; XY_DELAY(); /*   6,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_L()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_M()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_N()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_O()                      \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x000C; XY_DELAY(); /*  12,   0 */   \

// #define XY_DRAW_CHAR_16x16_P()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0010; XY_DELAY(); /*  16,   0 */   \

// #define XY_DRAW_CHAR_16x16_Q()                      \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_R()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0008; XY_DELAY(); /*  -8,   0 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0xFC06; XY_DELAY(); /*   6,  -4 */   \
//   XY_CURSOR += 0xFC06; XY_DELAY(); /*   6,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_S()                      \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR -= 0x0004; XY_DELAY(); /*  -4,   0 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \

// #define XY_DRAW_CHAR_16x16_T()                      \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x000A; XY_DELAY(); /*  10,   0 */   \

// #define XY_DRAW_CHAR_16x16_U()                      \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x03FC; XY_DELAY(); /*  -4,   4 */   \
//   XY_CURSOR += 0x0600; XY_DELAY(); /*   0,   6 */   \
//   XY_CURSOR += 0x0600; XY_DELAY(); /*   0,   6 */   \
//   XY_CURSOR -= 0x0600; XY_DELAY(); /*   0,  -6 */   \
//   XY_CURSOR -= 0x0600; XY_DELAY(); /*   0,  -6 */   \
//   XY_CURSOR += 0xFC04; XY_DELAY(); /*   4,  -4 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \
//   XY_CURSOR += 0x0404; XY_DELAY(); /*   4,   4 */   \
//   XY_CURSOR += 0x0600; XY_DELAY(); /*   0,   6 */   \
//   XY_CURSOR += 0x0600; XY_DELAY(); /*   0,   6 */   \
//   XY_CURSOR -= 0x0600; XY_DELAY(); /*   0,  -6 */   \
//   XY_CURSOR -= 0x0600; XY_DELAY(); /*   0,  -6 */   \
//   XY_CURSOR -= 0x0404; XY_DELAY(); /*  -4,  -4 */   \
//   XY_CURSOR += 0x0008; XY_DELAY(); /*   8,   0 */   \

// #define XY_DRAW_CHAR_16x16_V()                      \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x07FD; XY_DELAY(); /*  -3,   8 */   \
//   XY_CURSOR += 0x07FD; XY_DELAY(); /*  -3,   8 */   \
//   XY_CURSOR += 0xF803; XY_DELAY(); /*   3,  -8 */   \
//   XY_CURSOR += 0xF803; XY_DELAY(); /*   3,  -8 */   \
//   XY_CURSOR += 0x0803; XY_DELAY(); /*   3,   8 */   \
//   XY_CURSOR += 0x0803; XY_DELAY(); /*   3,   8 */   \
//   XY_CURSOR -= 0x0803; XY_DELAY(); /*  -3,  -8 */   \
//   XY_CURSOR -= 0x0803; XY_DELAY(); /*  -3,  -8 */   \
//   XY_CURSOR += 0x000A; XY_DELAY(); /*  10,   0 */   \

// #define XY_DRAW_CHAR_16x16_W()                      \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR += 0x0800; XY_DELAY(); /*   0,   8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR -= 0x0800; XY_DELAY(); /*   0,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_X()                      \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR -= 0x0806; XY_DELAY(); /*  -6,  -8 */   \
//   XY_CURSOR += 0x07FA; XY_DELAY(); /*  -6,   8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0xF806; XY_DELAY(); /*   6,  -8 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #define XY_DRAW_CHAR_16x16_Y()                      \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0A00; XY_DELAY(); /*   0,  10 */   \
//   XY_CURSOR += 0x05FA; XY_DELAY(); /*  -6,   6 */   \
//   XY_CURSOR += 0xFA06; XY_DELAY(); /*   6,  -6 */   \
//   XY_CURSOR += 0x0606; XY_DELAY(); /*   6,   6 */   \
//   XY_CURSOR -= 0x0606; XY_DELAY(); /*  -6,  -6 */   \
//   XY_CURSOR -= 0x0A00; XY_DELAY(); /*   0, -10 */   \
//   XY_CURSOR += 0x000A; XY_DELAY(); /*  10,   0 */   \

// #define XY_DRAW_CHAR_16x16_Z()                      \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR += 0x0806; XY_DELAY(); /*   6,   8 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR -= 0x0006; XY_DELAY(); /*  -6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR -= 0x0806; XY_DELAY(); /*  -6,  -8 */   \
//   XY_CURSOR -= 0x0806; XY_DELAY(); /*  -6,  -8 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0006; XY_DELAY(); /*   6,   0 */   \
//   XY_CURSOR += 0x0004; XY_DELAY(); /*   4,   0 */   \

// #endif // XY_DRAWING_H