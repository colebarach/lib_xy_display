#ifndef XY_H
#define XY_H

// X-Y ------------------------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: X-Y aggregate library. Organizes includes and provides demos of library capability.
// 
// Naming: This library reserves the 'xy' prefix.
//
// To do:
// - Configurable screen and font sizes would be nice, if hardware supports it.
// - I'd like to move to >10-bit output, obviously this needs changes.
// - Blanking is important, need to figure that out 
// - Characters need updated to clean double tracing and weird end-points.
// - ASCII table needs finished
// - Configurable XY packaging, consider using macro for register assignment
// - Generic X-Y storage in points, currently hardware dependent.
// - Pick and implement a constant period for the renderer / pen, ex. 1us
// - Demos for renderer need dynamically allocated memory, how to handle this

// Includes -------------------------------------------------------------------------------------------------------------------

#include "xy_hardware.h"
#include "xy_drawing.h"
#include "xy_renderer.h"
#include "xy_shapes.h"
#include "xy_math.h"

// Rendering Demos ------------------------------------------------------------------------------------------------------------
// Rendering Demo - ASCII Table
// - Call once to put an ASCII table into the render stack
void xyRendererDemoAscii()
{
	for(uint16_t index = 0; index < 0x80; ++index)
	{
		xyRendererRenderChar(index, 0x10 * index, 0x8C - 0x14 * (index / 0x10));
	}
}

// Rendering Demo - Hello World
// - Call once to put the text "Hello, World!" into the render stack
void xyRendererDemoHelloWorld()
{
	xyRendererRenderString("HELLO,\nWORLD!", 0x50, 0x82);
}

// Rendering Demo - Grid
// - Call once to put a grid into the render stack
// - Scale determines the size of the squares
// - X and Y iterations determine how many boxes to draw in each direction
volatile struct xyShape xyRendererDemoGrid(uint16_t scale, uint16_t xIterations, uint16_t yIterations)
{
	xIterations += 1; // only draws (xIterations - 1) squares, for aesthetics only

	uint16_t shapeSize = xIterations * yIterations * 3;
	uint16_t* shape = xyShapeAllocate(shapeSize);

	for(uint16_t yIndex = 0; yIndex < yIterations; ++yIndex)
	{
		for(uint16_t xIndex = 0; xIndex < xIterations; ++xIndex)
		{
			uint16_t pointIndex = (xIndex + yIndex * xIterations) * 3;

			shape[pointIndex]     = xIndex * scale +  yIndex      * scale * 256;
			shape[pointIndex + 1] = xIndex * scale + (yIndex + 1) * scale * 256;
			shape[pointIndex + 2] = xIndex * scale +  yIndex      * scale * 256;
		}
	}

	// xyRendererRenderShape();
}

// Rendering Demo - Screen Grid
// - Call once to put a grid spanning the screen size into the render stack
void xyRendererDemoScreenGrid()
{
	xyRendererDemoGrid(15, 17, 17);
}

// Drawing Demos --------------------------------------------------------------------------------------------------------------

// Drawing Demo - Alphabet
// - Call to draw an alphabet on the screen
void xyDrawDemoAlphabet()
{
	while(true)
	{
		XY_CURSOR = 0x0000; XY_DELAY();

		XY_DRAW_CHAR_16x16_Y();
		XY_DRAW_CHAR_16x16_Z();

		XY_CURSOR -= 0x0020; XY_DELAY();
		XY_CURSOR += 0X1400; XY_DELAY();

		XY_DRAW_CHAR_16x16_S();
		XY_DRAW_CHAR_16x16_T();
		XY_DRAW_CHAR_16x16_U();
		XY_DRAW_CHAR_16x16_V();
		XY_DRAW_CHAR_16x16_W();
		XY_DRAW_CHAR_16x16_X();

		XY_CURSOR -= 0x0060; XY_DELAY();
		XY_CURSOR += 0X1400; XY_DELAY();

		XY_DRAW_CHAR_16x16_M();
		XY_DRAW_CHAR_16x16_N();
		XY_DRAW_CHAR_16x16_O();
		XY_DRAW_CHAR_16x16_P();
		XY_DRAW_CHAR_16x16_Q();
		XY_DRAW_CHAR_16x16_R();

		XY_CURSOR -= 0x0060; XY_DELAY();
		XY_CURSOR += 0X1400; XY_DELAY();

		XY_DRAW_CHAR_16x16_G();
		XY_DRAW_CHAR_16x16_H();
		XY_DRAW_CHAR_16x16_I();
		XY_DRAW_CHAR_16x16_J();
		XY_DRAW_CHAR_16x16_K();
		XY_DRAW_CHAR_16x16_L();

		XY_CURSOR -= 0x0060; XY_DELAY();
		XY_CURSOR += 0X1400; XY_DELAY();

		XY_DRAW_CHAR_16x16_A();
		XY_DRAW_CHAR_16x16_B();
		XY_DRAW_CHAR_16x16_C();
		XY_DRAW_CHAR_16x16_D();
		XY_DRAW_CHAR_16x16_E();
		XY_DRAW_CHAR_16x16_F();

		XY_CURSOR -= 0x0060; XY_DELAY();
		XY_CURSOR -= 0x5000; XY_DELAY();
	}

}

// Drawing Demo - Grid
// - Call to draw a grid on the screen
void xyDrawDemoGrid()
{
	while(true)
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
}

// Drawing Demo - Hilbert Curve
// - Call continuously to draw a hilbert curve on the screen
// - Depth - Depth of the curve, ex. 2
// - Scale - Length of a single line segment, ex. 16
void xyDrawDemoHilbertCurve(int depth, int scale, int rotation, int direction)
{
	if(depth == 0) return;

	if(rotation == 0)
	{
		if(direction == 0)
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
		}
		else
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
		}
	}
	else if(rotation == 1)
	{
		if(direction == 0)
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
		}
		else
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
		}
	}
	else if(rotation == 2)
	{
		if(direction == 0)
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 1);
		}
		else
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 1, 0);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
		}
	}
	else
	{
		if(direction == 0)
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 1);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 0);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 1);
		}
		else
		{
			xyDrawDemoHilbertCurve(depth - 1, scale, 2, 0);
			XY_CURSOR -= scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR -= scale;
			xyDrawDemoHilbertCurve(depth - 1, scale, 3, 1);
			XY_CURSOR += scale << 8;
			xyDrawDemoHilbertCurve(depth - 1, scale, 0, 0);
		}
	}
}

#endif // XY_H