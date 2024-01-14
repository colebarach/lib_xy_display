#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POINT_CULL_MODULUS 12

int nearestNeighbor(int index, int* x, int* y, int pointCount, bool* pointsHit)
{
    int bestDistance = -1;
    int neighbor = -1;

    for(int neighborIndex = 0; neighborIndex < pointCount; ++neighborIndex)
    {
        if(neighborIndex == index || pointsHit[neighborIndex]) continue;

        int deltaX = x[index] - x[neighborIndex];
        int deltaY = y[index] - y[neighborIndex];

        int distance = deltaX * deltaX + deltaY * deltaY;

        if(distance < bestDistance || bestDistance == -1)
        {
            neighbor = neighborIndex;
            bestDistance = distance;
        }
    }

    return neighbor;
}

int main()
{
    int frameCount;
    fscanf(stdin, "%i", &frameCount);

    printf("#ifndef MODELS_H\n#define MODELS_H\n// Notice: This file is auto-generated. Any changes will be over-written on re-generation\n\n");

    for(int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
    {
        int pointCount;
        fscanf(stdin, "%i\n[", &pointCount);

        if(pointCount == 0)
        {
            fscanf(stdin, "]");
            printf("#define SIZE_FRAME_%i 0\nxyPoint_t* const frame%i = NULL;\n\n", frameIndex, frameIndex);
            continue;
        }

        int actualPointCount = pointCount / POINT_CULL_MODULUS;
        printf("#define SIZE_FRAME_%i %i\nxyPoint_t frame%i[SIZE_FRAME_%i] = \n{", frameIndex, actualPointCount, frameIndex, frameIndex);

        // Points to work with
        int* xIn = malloc(sizeof(int) * pointCount);
        int* yIn = malloc(sizeof(int) * pointCount);

        // Total number of points traversed
        int pointsHitTotal;

        // Indicates whether a point has been traversed
        bool* pointsHit = malloc(sizeof(bool) * pointCount);

        // Get input
        for(int index = 0; index < pointCount; ++index)
        {
            fscanf(stdin, "(%i, %i), ", &xIn[index], &yIn[index]);
            pointsHit[index] = false;
        }

        // Mark first point
        pointsHit[0] = true;
        pointsHitTotal = 1;
        int currentIndex = 0;

        if(POINT_CULL_MODULUS == 1)
        {
            printf("\n    {%i, %i}, ", xIn[0], yIn[0]);
        }
        else
        {
            printf("\n    ");
        }

        while(pointsHitTotal < pointCount)
        {
            if(pointsHitTotal % (8 * POINT_CULL_MODULUS) == 0) printf("\n    ");

            // Find next point
            currentIndex = nearestNeighbor(currentIndex, xIn, yIn, pointCount, pointsHit);
            pointsHit[currentIndex] = true;
            ++pointsHitTotal;

            // Print point
            if(pointsHitTotal % POINT_CULL_MODULUS == 0)
            {
                printf("{%3i, %3i}, ", xIn[currentIndex], yIn[currentIndex]);
            }
        }

        free(xIn);
        free(yIn);
        free(pointsHit);

        fscanf(stdin, "]\n");

        printf("\n};\n\n");
    }

    printf("#define FRAME_COUNT %i\nxyPoint_t* frames[FRAME_COUNT] = \n{", frameCount);
    for(int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
    {
        if(frameIndex % 8 == 0) printf("\n    ");

        printf("frame%i", frameIndex);

        if(frameIndex != frameCount - 1) printf(", ");
    }
    printf("\n};\n\n");

    printf("uint16_t frameSizes[FRAME_COUNT] = \n{");
    for(int frameIndex = 0; frameIndex < frameCount; ++frameIndex)
    {
        if(frameIndex % 8 == 0) printf("\n    ");

        printf("SIZE_FRAME_%i", frameIndex);

        if(frameIndex != frameCount - 1) printf(", ");
    }
    printf("\n};\n\n");

    printf("#endif // MODELS_H\n");
}
