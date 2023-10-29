// Header
#include "xy_hardware.h"

void xyCursorInitialize()
{
    gpio_init(0);
    gpio_init(1);
    gpio_init(2);
    gpio_init(3);
    gpio_init(4);
    gpio_init(5);
    gpio_init(6);
    gpio_init(7);

    gpio_init(8);
    gpio_init(9);
    gpio_init(10);
    gpio_init(11);
    gpio_init(12);
    gpio_init(13);
    gpio_init(14);
    gpio_init(15);

    gpio_set_dir(0, GPIO_OUT);
    gpio_set_dir(1, GPIO_OUT);
    gpio_set_dir(2, GPIO_OUT);
    gpio_set_dir(3, GPIO_OUT);
    gpio_set_dir(4, GPIO_OUT);
    gpio_set_dir(5, GPIO_OUT);
    gpio_set_dir(6, GPIO_OUT);
    gpio_set_dir(7, GPIO_OUT);

    gpio_set_dir(8, GPIO_OUT);
    gpio_set_dir(9, GPIO_OUT);
    gpio_set_dir(10, GPIO_OUT);
    gpio_set_dir(11, GPIO_OUT);
    gpio_set_dir(12, GPIO_OUT);
    gpio_set_dir(13, GPIO_OUT);
    gpio_set_dir(14, GPIO_OUT);
    gpio_set_dir(15, GPIO_OUT);
}