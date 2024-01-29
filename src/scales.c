#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scales.h"
#include "notes.h"
#include "duration.h"

const int MAJOR_SCALE_INTERVALS[] = {0, 2, 4, 5, 7, 9, 11, 12};
const int MAJOR_SCALE_LENGTH = 8;

Note *createScaleArray(float tonic, const int *intervals, const int scaleLength)
{
    size_t scaleSize = scaleLength * NOTE_SIZE;
    Note *scale = malloc(scaleSize);
    if (scale == NULL)
    {
        fprintf(stderr, "Error allocating scale\n");
        exit(EXIT_FAILURE);
    }

    memset(scale, 0, scaleSize);

    for (int i = 0; i < scaleLength; i++)
    {
        scale[i].frequency = tonic * pow(2, intervals[i] / 12.0);
        scale[i].value = CROTCHET;
    }

    return scale;
}