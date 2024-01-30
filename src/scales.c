#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scales.h"
#include "notes.h"
#include "duration.h"
#include "validation.h"

const char *MAJOR = "major";
const char *MINOR = "minor";
const char *HARMONIC_MINOR = "harmonic-minor";
const char *MELODIC_MINOR = "melodic-minor";  

const int MAJOR_INTERVALS[] = {0, 2, 4, 5, 7, 9, 11, 12};
const int NATURAL_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 8, 10, 12};
const int HARMONIC_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 8, 11, 12};
const int ASCENDING_MELODIC_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 9, 11, 12};
const int DESCENDING_MELODIC_MINOR_INTERVALS[] = {12, 10, 8, 7, 5, 3, 2, 0};

const int WHOLE_TONE_LENGTH = 8;

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

Note *getScale(const char *scaleName, float tonic)
{
    if (isMajor(scaleName))
    {
        return createScaleArray(tonic, MAJOR_INTERVALS, WHOLE_TONE_LENGTH);
    }
    else if (isMinor(scaleName))
    {
        return createScaleArray(tonic, NATURAL_MINOR_INTERVALS, WHOLE_TONE_LENGTH);
    }
    else if (isHarmonicMinor(scaleName))
    {
        return createScaleArray(tonic, HARMONIC_MINOR_INTERVALS, WHOLE_TONE_LENGTH);
    }

    return NULL;
}