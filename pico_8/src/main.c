#include "xy.h"

int main()
{
    xyRendererInitialize();

    uint16_t* circle = xyShapeAllocate(256);

    for(uint16_t x = 0; x < 256; ++x)
    {
        circle[x] = cosLut256x256Unsigned[x] + (uint16_t)sinLut256x256Unsigned[x] * 256;
    }

    xyRendererRenderShape(circle, 256, 0, 0);

    while(true)
    {
        
    }
}