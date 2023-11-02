// Header
#include "xy_shapes.h"

// Primatives -----------------------------------------------------------------------------------------------------------------

uint16_t* const xyShapeNull = NULL;

uint16_t xyShapePoint[XY_SHAPE_SIZE_POINT] = 
{
    0x0000
};

// ASCII ----------------------------------------------------------------------------------------------------------------------

#define XY_SHAPE_SIZE_16X16_ASCII_0X00 13
uint16_t xyShape16x16Ascii0x00[XY_SHAPE_SIZE_16X16_ASCII_0X00] = 
{
    0x0000, 0x0806, 0x100C, 0x0806, 0x0000, 0x0800, 0x1000, 0x1006,
    0x100C, 0x080C, 0x000C, 0x0006, 0x0000,
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X20 0
uint16_t* const xyShape16x16Ascii0x20 = NULL;

#define XY_SHAPE_SIZE_16X16_ASCII_0X21 9
uint16_t xyShape16x16Ascii0x21[XY_SHAPE_SIZE_16X16_ASCII_0X21] =
{
    0x0005, 0x0205, 0x0207, 0x0007, 0x1008, 0x0407, 0x0405, 0x1004,
    0x1008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X22 10
uint16_t xyShape16x16Ascii0x22[XY_SHAPE_SIZE_16X16_ASCII_0X22] =
{
    0x0A02, 0x1001, 0x1005, 0x0A04, 0x0A02, 0x0A0A, 0x0A08, 0x1007,
    0x100B, 0x0A0A
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X23 25
uint16_t xyShape16x16Ascii0x23[XY_SHAPE_SIZE_16X16_ASCII_0X23] =
{
    0x0000, 0x0401, 0x0400, 0x0401, 0x0405, 0x0409, 0x0405, 0x0401,
    0x0802, 0x0C03, 0x0C00, 0x0C03, 0x1004, 0x0C03, 0x0C08, 0x0C0B,
    0x100C, 0x0C0B, 0x0C0C, 0x0C0B, 0x080A, 0x0409, 0x040C, 0x0409,
    0x0008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X24 17
uint16_t xyShape16x16Ascii0x24[XY_SHAPE_SIZE_16X16_ASCII_0X24] =
{
    0x0500, 0x0204, 0x0206, 0x0006, 0x0206, 0x0806, 0x1006, 0x0806,
    0x0206, 0x0208, 0x050C, 0x0808, 0x0804, 0x0B00, 0x0E04, 0x0E08,
    0x0B0C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X25 13
uint16_t xyShape16x16Ascii0x25[XY_SHAPE_SIZE_16X16_ASCII_0X25] =
{
    0x0000, 0x0806, 0x100C, 0x1003, 0x0D00, 0x0A03, 0x0D06, 0x1003,
    0x0009, 0x0306, 0x0609, 0x030C, 0x0009
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X26 12
uint16_t xyShape16x16Ascii0x26[XY_SHAPE_SIZE_16X16_ASCII_0X26] =
{
    0x040C, 0x0008, 0x0004, 0x0400, 0x0600, 0x0A04, 0x0E08, 0x1006,
    0x1004, 0x0E02, 0x0707, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X27 5
uint16_t xyShape16x16Ascii0x27[XY_SHAPE_SIZE_16X16_ASCII_0X27] =
{
    0x0A05, 0x1004, 0x1008, 0x0A07, 0x0A05
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X28 4
uint16_t xyShape16x16Ascii0x28[XY_SHAPE_SIZE_16X16_ASCII_0X28] =
{
    0x1008, 0x0C04, 0x0404, 0x0008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X29 4
uint16_t xyShape16x16Ascii0x29[XY_SHAPE_SIZE_16X16_ASCII_0X29] =
{
    0x1004, 0x0C08, 0x0408, 0x0004
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2A 9
uint16_t xyShape16x16Ascii0x2A[XY_SHAPE_SIZE_16X16_ASCII_0X2A] =
{
    0x0704, 0x0A06, 0x0B02, 0x0A06, 0x0E06, 0x0A06, 0x0B0A, 0x0A06,
    0x0708
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2B 7
uint16_t xyShape16x16Ascii0x2B[XY_SHAPE_SIZE_16X16_ASCII_0X2B] =
{
    0x0800, 0x0806, 0x0D06, 0x0806, 0x080C, 0x0806, 0x0206
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2C 5
uint16_t xyShape16x16Ascii0x2C[XY_SHAPE_SIZE_16X16_ASCII_0X2C] =
{
    0x0003, 0x0604, 0x0608, 0x0005, 0x0003
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2D 3
uint16_t xyShape16x16Ascii0x2D[XY_SHAPE_SIZE_16X16_ASCII_0X2D] =
{
    0x0800, 0x0806, 0x080C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2E 5
uint16_t xyShape16x16Ascii0x2E[XY_SHAPE_SIZE_16X16_ASCII_0X2E] =
{
    0x0005, 0x0205, 0x0207, 0x0007, 0x0005
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X2F 3
uint16_t xyShape16x16Ascii0x2F[XY_SHAPE_SIZE_16X16_ASCII_0X2F] =
{
    0x0003, 0x0806, 0x1009
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X30 14
uint16_t xyShape16x16Ascii0x30[XY_SHAPE_SIZE_16X16_ASCII_0X30] =
{
    0x0004, 0x0202, 0x0806, 0x0E0A, 0x0806, 0x0202, 0x0400, 0x0C00,
    0x1004, 0x1008, 0x0E0A, 0x0C0C, 0x040C, 0x0008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X31 7
uint16_t xyShape16x16Ascii0x31[XY_SHAPE_SIZE_16X16_ASCII_0X31] =
{
    0x0000, 0x0006, 0x000C, 0x0006, 0x0806, 0x1006, 0x0A00
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X32 8
uint16_t xyShape16x16Ascii0x32[XY_SHAPE_SIZE_16X16_ASCII_0X32] =
{
    0x000C, 0x0006, 0x0000, 0x0606, 0x0C0C, 0x1008, 0x1004, 0x0C00 
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X33 11
uint16_t xyShape16x16Ascii0x33[XY_SHAPE_SIZE_16X16_ASCII_0X33] =
{
    0x0400, 0x0004, 0x0008, 0x040C, 0x0808, 0x0804, 0x0808, 0x0C0C,
    0x1008, 0x1004, 0x0C00
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X34 7
uint16_t xyShape16x16Ascii0x34[XY_SHAPE_SIZE_16X16_ASCII_0X34] =
{
    0x0008, 0x0808, 0x1008, 0x0C04, 0x0800, 0x0806, 0x080C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X35 11
uint16_t xyShape16x16Ascii0x35[XY_SHAPE_SIZE_16X16_ASCII_0X35] =
{
    0x0400, 0x0004, 0x0008, 0x040C, 0x0808, 0x0804, 0x0800, 0x0C00,
    0x1000, 0x1006, 0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X36 11
uint16_t xyShape16x16Ascii0x36[XY_SHAPE_SIZE_16X16_ASCII_0X36] =
{
    0x0400, 0x0804, 0x0808, 0x040C, 0x0008, 0x0004, 0x0400, 0x0C00,
    0x1004, 0x1008, 0x0C0C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X37 5
uint16_t xyShape16x16Ascii0x37[XY_SHAPE_SIZE_16X16_ASCII_0X37] =
{
    0x0006, 0x0809, 0x100C, 0x1006, 0x1000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X38 12
uint16_t xyShape16x16Ascii0x38[XY_SHAPE_SIZE_16X16_ASCII_0X38] =
{
    0x0804, 0x0400, 0x0004, 0x0008, 0x040C, 0x0808, 0x0804, 0x0C00,
    0x1004, 0x1008, 0x0C0C, 0x0808
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X39 11
uint16_t xyShape16x16Ascii0x39[XY_SHAPE_SIZE_16X16_ASCII_0X39] =
{
    0x0400, 0x0004, 0x0008, 0x040C, 0x0C0C, 0x1008, 0x1004, 0x0C00,
    0x0804, 0x0808, 0x0C0C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X41 7
uint16_t xyShape16x16Ascii0x41[XY_SHAPE_SIZE_16X16_ASCII_0X41] =
{
    0x0000, 0x0803, 0x0809, 0x0803, 0x1006, 0x0809, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X42 11
uint16_t xyShape16x16Ascii0x42[XY_SHAPE_SIZE_16X16_ASCII_0X42] =
{
    0x0000, 0x0008, 0x040C, 0x0808, 0x0800, 0x0808, 0x0C0C, 0x1008,
    0x1000, 0x0800, 0x0000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X43 14
uint16_t xyShape16x16Ascii0x43[XY_SHAPE_SIZE_16X16_ASCII_0X43] =
{
    0x0008, 0x040C, 0x0008, 0x0004, 0x0400, 0x0C00, 0x1004, 0x1008,
    0x0C0C, 0x1008, 0x1004, 0x0C00, 0x0400, 0x0004
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X44 8
uint16_t xyShape16x16Ascii0x44[XY_SHAPE_SIZE_16X16_ASCII_0X44] =
{
    0x0000, 0x0008, 0x040C, 0x0C0C, 0x1008, 0x1000, 0x0800, 0x0000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X45 17
uint16_t xyShape16x16Ascii0x45[XY_SHAPE_SIZE_16X16_ASCII_0X45] =
{
    0x0000, 0x0006, 0x000C, 0x0006, 0x0000, 0x0800, 0x0806, 0x080C,
    0x0806, 0x0800, 0x1000, 0x1006, 0x100C, 0x1006, 0x1000, 0x0800,
    0x0000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X46 13
uint16_t xyShape16x16Ascii0x46[XY_SHAPE_SIZE_16X16_ASCII_0X46] =
{
    0x0000, 0x0800, 0x0806, 0x080C, 0x0806, 0x0800, 0x1000, 0x1006,
    0x100C, 0x1006, 0x1000, 0x0800, 0x0000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X47 18
uint16_t xyShape16x16Ascii0x47[XY_SHAPE_SIZE_16X16_ASCII_0X47] =
{
    0x0008, 0x040C, 0x060C, 0x0608, 0x060C, 0x040C, 0x0008, 0x0004,
    0x0400, 0x0C00, 0x1004, 0x1008, 0x0C0C, 0x1008, 0x1004, 0x0C00,
    0x0400, 0x0004
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X48 9
uint16_t xyShape16x16Ascii0x48[XY_SHAPE_SIZE_16X16_ASCII_0X48] =
{
    0x0000, 0x0800, 0x1000, 0x0800, 0x0806, 0x080C, 0x100C, 0x080C,
    0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X49 12
uint16_t xyShape16x16Ascii0x49[XY_SHAPE_SIZE_16X16_ASCII_0X49] =
{
    0x0000, 0x0006, 0x000C, 0x0006, 0x0806, 0x1006, 0x1000, 0x1006,
    0x100C, 0x1006, 0x0806, 0x0006
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4A 10
uint16_t xyShape16x16Ascii0x4A[XY_SHAPE_SIZE_16X16_ASCII_0X4A] =
{
    0x0004, 0x0400, 0x0004, 0x0408, 0x0808, 0x1008, 0x100C, 0x1008,
    0x1000, 0x1008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4B 10
uint16_t xyShape16x16Ascii0x4B[XY_SHAPE_SIZE_16X16_ASCII_0X4B] =
{
    0x0000, 0x0800, 0x1000, 0x0800, 0x0C06, 0x100C, 0x0C06, 0x0800,
    0x0406, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4C 7
uint16_t xyShape16x16Ascii0x4C[XY_SHAPE_SIZE_16X16_ASCII_0X4C] =
{
    0x0000, 0x0800, 0x1000, 0x0800, 0x0000, 0x0006, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4D 7
uint16_t xyShape16x16Ascii0x4D[XY_SHAPE_SIZE_16X16_ASCII_0X4D] =
{
    0x0000, 0x0800, 0x1000, 0x0806, 0x100C, 0x080C, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4E 9
uint16_t xyShape16x16Ascii0x4E[XY_SHAPE_SIZE_16X16_ASCII_0X4E] =
{
    0x0000, 0x0800, 0x1000, 0x0806, 0x000C, 0x080C, 0x100C, 0x080C,
    0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X4F 10
uint16_t xyShape16x16Ascii0x4F[XY_SHAPE_SIZE_16X16_ASCII_0X4F] =
{
    0x0004, 0x0008, 0x0004, 0x0400, 0x0C00, 0x1004, 0x1008, 0x0C0C,
    0x040C, 0x0008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X50 8
uint16_t xyShape16x16Ascii0x50[XY_SHAPE_SIZE_16X16_ASCII_0X50] =
{
    0x0000, 0x0800, 0x0808, 0x0C0C, 0x1008, 0x1000, 0x0800, 0x0000
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X51 14
uint16_t xyShape16x16Ascii0x51[XY_SHAPE_SIZE_16X16_ASCII_0X51] =
{
    0x0004, 0x0008, 0x0004, 0x0400, 0x0C00, 0x1004, 0x1008, 0x0C0C,
    0x040C, 0x020A, 0x0408, 0x000C, 0x020A, 0x0008
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X52 9
uint16_t xyShape16x16Ascii0x52[XY_SHAPE_SIZE_16X16_ASCII_0X52] =
{
    0x0000, 0x0800, 0x0808, 0x0C0C, 0x1008, 0x1000, 0x0800, 0x0406,
    0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X53 10
uint16_t xyShape16x16Ascii0x53[XY_SHAPE_SIZE_16X16_ASCII_0X53] =
{
    0x0400, 0x0004, 0x0008, 0x040C, 0x0808, 0x0804, 0x0C00, 0x1004,
    0x1008, 0x0C0C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X54 6
uint16_t xyShape16x16Ascii0x54[XY_SHAPE_SIZE_16X16_ASCII_0X54] =
{
    0x0006, 0x0806, 0x1006, 0x1000, 0x1006, 0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X55 11
uint16_t xyShape16x16Ascii0x55[XY_SHAPE_SIZE_16X16_ASCII_0X55] =
{
    0x0004, 0x0400, 0x0800, 0x1000, 0x0800, 0x0400, 0x0004, 0x0008,
    0x040C, 0x080C, 0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X56 7
uint16_t xyShape16x16Ascii0x56[XY_SHAPE_SIZE_16X16_ASCII_0X56] =
{
    0x0006, 0x0803, 0x1000, 0x0803, 0x0006, 0x0809, 0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X57 9
uint16_t xyShape16x16Ascii0x57[XY_SHAPE_SIZE_16X16_ASCII_0X57] =
{
    0x0000, 0x0800, 0x1000, 0x0800, 0x0000, 0x0806, 0x000C, 0x080C,
    0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X58 7
uint16_t xyShape16x16Ascii0x58[XY_SHAPE_SIZE_16X16_ASCII_0X58] =
{
    0x0000, 0x0806, 0x1000, 0x0806, 0x100C, 0x0806, 0x000C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X59 6
uint16_t xyShape16x16Ascii0x59[XY_SHAPE_SIZE_16X16_ASCII_0X59] =
{
    0x0006, 0x0806, 0x0A06, 0x1000, 0x0A06, 0x100C
};

#define XY_SHAPE_SIZE_16X16_ASCII_0X5A 9
uint16_t xyShape16x16Ascii0x5A[XY_SHAPE_SIZE_16X16_ASCII_0X5A] =
{
    0x0000, 0x0006, 0x000C, 0x0006, 0x0000, 0x0806, 0x100C, 0x1006,
    0x1000
};

uint16_t* xyShape16x16Ascii[128] = 
{
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,

    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,

    xyShape16x16Ascii0x20, xyShape16x16Ascii0x21, xyShape16x16Ascii0x22, xyShape16x16Ascii0x23,
    xyShape16x16Ascii0x24, xyShape16x16Ascii0x25, xyShape16x16Ascii0x26, xyShape16x16Ascii0x27,
    xyShape16x16Ascii0x28, xyShape16x16Ascii0x29, xyShape16x16Ascii0x2A, xyShape16x16Ascii0x2B,
    xyShape16x16Ascii0x2C, xyShape16x16Ascii0x2D, xyShape16x16Ascii0x2E, xyShape16x16Ascii0x2F,

    xyShape16x16Ascii0x30, xyShape16x16Ascii0x31, xyShape16x16Ascii0x32, xyShape16x16Ascii0x33,
    xyShape16x16Ascii0x34, xyShape16x16Ascii0x35, xyShape16x16Ascii0x36, xyShape16x16Ascii0x37,
    xyShape16x16Ascii0x38, xyShape16x16Ascii0x39, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    // TODO: 6 Symbols

    // TODO: 1 Symbol
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x41, xyShape16x16Ascii0x42, xyShape16x16Ascii0x43,
    xyShape16x16Ascii0x44, xyShape16x16Ascii0x45, xyShape16x16Ascii0x46, xyShape16x16Ascii0x47,
    xyShape16x16Ascii0x48, xyShape16x16Ascii0x49, xyShape16x16Ascii0x4A, xyShape16x16Ascii0x4B,
    xyShape16x16Ascii0x4C, xyShape16x16Ascii0x4D, xyShape16x16Ascii0x4E, xyShape16x16Ascii0x4F,

    xyShape16x16Ascii0x50, xyShape16x16Ascii0x51, xyShape16x16Ascii0x52, xyShape16x16Ascii0x53,
    xyShape16x16Ascii0x54, xyShape16x16Ascii0x55, xyShape16x16Ascii0x56, xyShape16x16Ascii0x57,
    xyShape16x16Ascii0x58, xyShape16x16Ascii0x59, xyShape16x16Ascii0x5A, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    // TODO: 5 Symbols

    // TODO: 16 Symbols
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    
    // TODO: 16 Symbols
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00,
    xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00, xyShape16x16Ascii0x00
};

// TODO: See above symbols
uint16_t xyShapeSize16x16Ascii[128] = 
{
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,

    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,

    XY_SHAPE_SIZE_16X16_ASCII_0X20, XY_SHAPE_SIZE_16X16_ASCII_0X21, XY_SHAPE_SIZE_16X16_ASCII_0X22, XY_SHAPE_SIZE_16X16_ASCII_0X23,
    XY_SHAPE_SIZE_16X16_ASCII_0X24, XY_SHAPE_SIZE_16X16_ASCII_0X25, XY_SHAPE_SIZE_16X16_ASCII_0X26, XY_SHAPE_SIZE_16X16_ASCII_0X27,
    XY_SHAPE_SIZE_16X16_ASCII_0X28, XY_SHAPE_SIZE_16X16_ASCII_0X29, XY_SHAPE_SIZE_16X16_ASCII_0X2A, XY_SHAPE_SIZE_16X16_ASCII_0X2B,
    XY_SHAPE_SIZE_16X16_ASCII_0X2C, XY_SHAPE_SIZE_16X16_ASCII_0X2D, XY_SHAPE_SIZE_16X16_ASCII_0X2E, XY_SHAPE_SIZE_16X16_ASCII_0X2F,

    XY_SHAPE_SIZE_16X16_ASCII_0X30, XY_SHAPE_SIZE_16X16_ASCII_0X31, XY_SHAPE_SIZE_16X16_ASCII_0X32, XY_SHAPE_SIZE_16X16_ASCII_0X33,
    XY_SHAPE_SIZE_16X16_ASCII_0X34, XY_SHAPE_SIZE_16X16_ASCII_0X35, XY_SHAPE_SIZE_16X16_ASCII_0X36, XY_SHAPE_SIZE_16X16_ASCII_0X37,
    XY_SHAPE_SIZE_16X16_ASCII_0X38, XY_SHAPE_SIZE_16X16_ASCII_0X39, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,

    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X41, XY_SHAPE_SIZE_16X16_ASCII_0X42, XY_SHAPE_SIZE_16X16_ASCII_0X43,
    XY_SHAPE_SIZE_16X16_ASCII_0X44, XY_SHAPE_SIZE_16X16_ASCII_0X45, XY_SHAPE_SIZE_16X16_ASCII_0X46, XY_SHAPE_SIZE_16X16_ASCII_0X47,
    XY_SHAPE_SIZE_16X16_ASCII_0X48, XY_SHAPE_SIZE_16X16_ASCII_0X49, XY_SHAPE_SIZE_16X16_ASCII_0X4A, XY_SHAPE_SIZE_16X16_ASCII_0X4B,
    XY_SHAPE_SIZE_16X16_ASCII_0X4C, XY_SHAPE_SIZE_16X16_ASCII_0X4D, XY_SHAPE_SIZE_16X16_ASCII_0X4E, XY_SHAPE_SIZE_16X16_ASCII_0X4F,

    XY_SHAPE_SIZE_16X16_ASCII_0X50, XY_SHAPE_SIZE_16X16_ASCII_0X51, XY_SHAPE_SIZE_16X16_ASCII_0X52, XY_SHAPE_SIZE_16X16_ASCII_0X53,
    XY_SHAPE_SIZE_16X16_ASCII_0X54, XY_SHAPE_SIZE_16X16_ASCII_0X55, XY_SHAPE_SIZE_16X16_ASCII_0X56, XY_SHAPE_SIZE_16X16_ASCII_0X57,
    XY_SHAPE_SIZE_16X16_ASCII_0X58, XY_SHAPE_SIZE_16X16_ASCII_0X59, XY_SHAPE_SIZE_16X16_ASCII_0X5A, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,

    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,

    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00,
    XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00, XY_SHAPE_SIZE_16X16_ASCII_0X00
};