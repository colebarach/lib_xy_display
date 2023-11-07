// X-Y Rendering Demos --------------------------------------------------------------------------------------------------------
// 
// Author: Cole Barach
// 
// Description: Set of functions for demonstrating usage of the X-Y rendering library

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Demos ----------------------------------------------------------------------------------------------------------------------

// Rendering Demo - ASCII Table
// - Call once to put an ASCII table into the render stack
void xyRendererDemoAscii()
{
	for(uint16_t index = 0; index < 0x80; ++index)
	{
		xyRendererRenderChar(index, 0x10 * index, 0x8C - 0x14 * (index / 0x10));
	}
}

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Start renderer
    xyRendererInitialize();

    // Render table
    xyRendererDemoAscii();

    // Spin
    while(1);
}
