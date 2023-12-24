// Header
#include "xy_hardware.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Raspberry Pi Pico
#include <pico/stdlib.h>
#include <hardware/pwm.h>

// Global Data ----------------------------------------------------------------------------------------------------------------

static uint16_t portXOffset    = 0;      // Starting pin number of X signal parallel output.
static uint32_t portXMask      = 0;      // Bitmask for pins in X signal parallel output.
static uint16_t portYOffset    = 0;      // Starting pin number of Y signal parallel output.
static uint32_t portYMask      = 0;      // Bitmask for pins in Y signal parallel output.

static int16_t pwmSliceZ       = -1;     // PWM slice number of Z signal output, -1 if unused.
static int16_t pwmChannelZ     = -1;     // PWM channel number of Z signal output, -1 if unused.

static int16_t pwmSliceRed     = -1;     // PWM slice number of red signal output, -1 if unused.
static int16_t pwmChannelRed   = -1;     // PWM channel number of red signal output, -1 if unused.
static int16_t pwmSliceGreen   = -1;     // PWM slice number of green signal output, -1 if unused.
static int16_t pwmChannelGreen = -1;     // PWM channel number of green signal output, -1 if unused.
static int16_t pwmSliceBlue    = -1;     // PWM slice number of blue signal output, -1 if unused
static int16_t pwmChannelBlue  = -1;     // PWM channel number of blue signal output, -1 if unused.

static xyCoord_t screenWidth   = 0;      // Width of the screen in pixels.
static xyCoord_t screenHeight  = 0;      // Height of the screen in pixels.
static bool      screenWrap    = false;  // Indicates whether to clamp or wrap coordinates within the screen boundaries.

// Functions ------------------------------------------------------------------------------------------------------------------

void xySetupXy(uint16_t portXOffset_, uint16_t portXSize, uint16_t portYOffset_, uint16_t portYSize)
{
    // Store GPIO mapping
    portXOffset = portXOffset_;
    portYOffset = portYOffset_;
    portXMask   = 0;
    portYMask   = 0;

    // Set default screen size
    screenWidth  = 1 << portXSize;
    screenHeight = 1 << portYSize;

    // Configure X parallel port
    for(uint16_t index = portXOffset; index < portXOffset + portXSize; ++index)
    {
        portXMask |= (0b1 << index);
        gpio_init(index);
        gpio_set_dir(index, GPIO_OUT);
    }

    // Configure Y parallel port
    for(uint16_t index = portYOffset; index < portYOffset + portYSize; ++index)
    {
        portYMask |= (0b1 << index);
        gpio_init(index);
        gpio_set_dir(index, GPIO_OUT);
    }
}

void xySetupZ(int16_t pinZ)
{
    if(pinZ == -1)
    {
        pwmSliceZ   = -1;
        pwmChannelZ = -1;
        return;
    }

    // Configure GPIO
    gpio_set_function(pinZ, GPIO_FUNC_PWM);

    // Store PWM mapping
    pwmSliceZ   = pwm_gpio_to_slice_num(pinZ);
    pwmChannelZ = pwm_gpio_to_channel(pinZ);

    // Configure PWM
    // - Note: This currently uses 8-bit, could expose this for configuration.
    pwm_set_wrap(pwmSliceZ, 255);
    pwm_set_chan_level(pwmSliceZ, pwmChannelZ, 0);
    pwm_set_enabled(pwmSliceZ, true);
}

void xySetupRgb(int16_t pinRed, int16_t pinGreen, int16_t pinBlue)
{
    if(pinRed == -1)
    {
        pwmSliceRed   = -1;
        pwmChannelRed = -1;
    }
    else
    {
        // Configure GPIO
        gpio_set_function(pinRed, GPIO_FUNC_PWM);

        // Store PWM mapping
        pwmSliceRed   = pwm_gpio_to_slice_num(pinRed);
        pwmChannelRed = pwm_gpio_to_channel(pinRed);

        // Configure PWM
        // - Note: This currently uses 8-bit, could expose this for configuration.
        pwm_set_wrap(pwmSliceRed, 255);
        pwm_set_chan_level(pwmSliceRed, pwmChannelRed, 0);
        pwm_set_enabled(pwmSliceRed, true);
    }

    if(pinGreen == -1)
    {
        pwmSliceGreen   = -1;
        pwmChannelGreen = -1;
    }
    else
    {
        // Configure GPIO
        gpio_set_function(pinGreen, GPIO_FUNC_PWM);

        // Store PWM mapping
        pwmSliceGreen   = pwm_gpio_to_slice_num(pinGreen);
        pwmChannelGreen = pwm_gpio_to_channel(pinGreen);

        // Configure PWM
        // - Note: This currently uses 8-bit, could expose this for configuration.
        pwm_set_wrap(pwmSliceGreen, 255);
        pwm_set_chan_level(pwmSliceGreen, pwmChannelGreen, 0);
        pwm_set_enabled(pwmSliceGreen, true);
    }

    if(pinBlue == -1)
    {
        pwmSliceBlue   = -1;
        pwmChannelBlue = -1;
    }
    else
    {
        // Configure GPIO
        gpio_set_function(pinBlue, GPIO_FUNC_PWM);

        // Store PWM mapping
        pwmSliceBlue   = pwm_gpio_to_slice_num(pinBlue);
        pwmChannelBlue = pwm_gpio_to_channel(pinBlue);

        // Configure PWM
        // - Note: This currently uses 8-bit, could expose this for configuration.
        pwm_set_wrap(pwmSliceBlue, 255);
        pwm_set_chan_level(pwmSliceBlue, pwmChannelBlue, 0);
        pwm_set_enabled(pwmSliceBlue, true);
    }
}

void xySetupScreen(xyCoord_t width, xyCoord_t height, bool wrap)
{
    screenWidth  = width;
    screenHeight = height;
    screenWrap   = wrap;
}

void xyCursorMove(xyCoord_t x, xyCoord_t y)
{
    // Clamp / wrap cursor
    if(x >= screenWidth)
    {
        if(screenWrap)
        {
            while(x >= screenWidth) x -= screenWidth;
        }
        else
        {
            x = screenWidth - 1;
        }
    }
    else if(x < 0)
    {
        if(screenWrap)
        {
            while(x < screenWidth) x += screenWidth;
        }
        else
        {
            x = 0;
        }
    }

    if(y >= screenHeight)
    {
        if(screenWrap)
        {
            while(y >= screenHeight) y -= screenHeight;
        }
        else
        {
            y = screenHeight - 1;
        }
    }
    else if(y < 0)
    {
        if(screenWrap)
        {
            while(y < screenHeight) x += screenHeight;
        }
        else
        {
            y = 0;
        }
    }

    // Update output
    uint32_t outputValue = ((uint32_t)x << portXOffset) & portXMask | ((uint32_t)y << portYOffset) & portYMask;
    uint32_t outputMask = portXMask | portYMask;
    gpio_put_masked(outputMask, outputValue);
}

void xyCursorColor(xyColor_t red, xyColor_t green, xyColor_t blue)
{
    if(pwmSliceRed   != -1) pwm_set_chan_level(pwmSliceRed,   pwmChannelRed,   255 - red);
    if(pwmSliceGreen != -1) pwm_set_chan_level(pwmSliceGreen, pwmChannelGreen, 255 - green);
    if(pwmSliceBlue  != -1) pwm_set_chan_level(pwmSliceBlue,  pwmChannelBlue,  255 - blue);

    if(pwmSliceZ != -1)
    {
        // Convert to luma
        xyColor_t z = ((uint32_t)red * 21 + (uint32_t)green * 72 + (uint32_t)blue * 7) / 100;
        pwm_set_chan_level(pwmSliceZ, pwmChannelZ, 255 - z);
    }
}

xyCoord_t xyScreenWidth()
{
    return screenWidth;
}

xyCoord_t xyScreenHeight()
{
    return screenHeight;
}
