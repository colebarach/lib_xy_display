//Includes
#include "vector_xy.h"

// C Standard Libraries
#include <stdint.h>

void configureGpio()
{
	// Enable GPIO Clock
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	// Enable all pins as output
	GPIOB->MODER = 0x55555555;

	// Set all pins to high speed
	GPIOB->OSPEEDR = 0xAAAAAAAA;

	// Set all pins to use pull-down
	GPIOB->PUPDR = 0xAAAAAAAA;

	// Set all outputs low
	GPIOB->ODR = 0x0000;
}

void configureTimer(void)
{

}

int main()
{
	configureGpio();
	configureTimer();

	while(1)
	{
		XY_CURSOR = 0xEC00;

		XY_DRAW_CHAR_16x16_D();
		XY_DRAW_CHAR_16x16_Y();
		XY_DRAW_CHAR_16x16_L();
		XY_DRAW_CHAR_16x16_A();
		XY_DRAW_CHAR_16x16_N();
		XY_DRAW_CHAR_16x16_SPACE();
		XY_DRAW_CHAR_16x16_I();
		XY_DRAW_CHAR_16x16_S();
		XY_DRAW_CHAR_16x16_SPACE();
		XY_DRAW_CHAR_16x16_A();

		XY_CURSOR  = 0xEC00;
		XY_CURSOR -= 0x1400;

		XY_DRAW_CHAR_16x16_P();
		XY_DRAW_CHAR_16x16_I();
		XY_DRAW_CHAR_16x16_S();
		XY_DRAW_CHAR_16x16_S();
		XY_DRAW_CHAR_16x16_SPACE();
		XY_DRAW_CHAR_16x16_B();
		XY_DRAW_CHAR_16x16_U();
		XY_DRAW_CHAR_16x16_C();
		XY_DRAW_CHAR_16x16_K();
		XY_DRAW_CHAR_16x16_E();
		XY_DRAW_CHAR_16x16_T();

//		xyDemoAlphabet();
//		xyDemoGrid();
//		xyDemoHilbertCurve(3, 16, 0, 0);
	}
}
