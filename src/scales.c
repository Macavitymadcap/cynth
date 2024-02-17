#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scales.h"
#include "notes.h"
#include "duration.h"
#include "validation.h"

const char *CHROMATIC = "chromatic";
const char *MIXO_BLUES = "mixo-blues";
const char *DIMINISHED_HALF_WHOLE = "diminished-half-whole";
const char *DIMINISHED_WHOLE_HALF = "diminished-whole-half";
const char *MAJOR = "major";
const char *MINOR = "minor";
const char *HARMONIC_MINOR = "harmonic-minor";
const char *MELODIC_MINOR = "melodic-minor";
const char *MIXOLYDIAN = "mixolydian";
const char *DORIAN = "dorian";
const char *PHRYGIAN = "phrygian";
const char *LOCRIAN = "locrian";
const char *LYDIAN = "lydian";
const char *BLUES = "blues";
const char *WHOLE_TONE = "whole-tone";
const char *MAJOR_PENTATONIC = "major-pentatonic";
const char *MINOR_PENTATONIC = "minor-pentatonic";

const int CHROMATIC_LENGTH = 13;
const int CHROMATIC_INTERVALS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

const int MIXO_BLUES_LENGTH = 10;
const int MIXO_BLUES_INTERVALS[] = {0, 1, 2, 3, 4, 5, 7, 8, 10, 12};

const int DIMINISHED_LENGTH = 9;
const int DIMINISHED_HALF_WHOLE_INTERVALS[] = {0, 1, 3, 4, 6, 7, 9, 10, 12};
const int DIMINISHED_WHOLE_HALF_INTERVALS[] = {0, 2, 3, 5, 6, 8, 9, 11, 12};

const int STANDARD_LENGTH = 8;
const int MAJOR_INTERVALS[] = {0, 2, 4, 5, 7, 9, 11, 12};
const int NATURAL_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 8, 10, 12};
const int HARMONIC_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 8, 11, 12};
const int ASCENDING_MELODIC_MINOR_INTERVALS[] = {0, 2, 3, 5, 7, 9, 11, 12};
const int DESCENDING_MELODIC_MINOR_INTERVALS[] = {12, 10, 8, 7, 5, 3, 2, 0};
const int MIXOLYDIAN_INTERVALS[] = {0, 2, 4, 5, 7, 9, 10, 12};
const int DORIAN_INTERVALS[] = {0, 2, 3, 5, 7, 9, 10, 12};
const int PHRYGIAN_INTERVALS[] = {0, 1, 3, 5, 7, 8, 10, 12};
const int LOCRIAN_INTERVALS[] = {0, 1, 3, 5, 6, 8, 10, 12};
const int LYDIAN_INTERVALS[] = {0, 2, 4, 6, 7, 9, 11, 12};

const int BLUES_LENGTH = 7;
const int BLUES_INTERVALS[] = {0, 3, 5, 6, 7, 10, 12};
const int WHOLE_TONE_INTERVALS[] = {0, 2, 4, 6, 8, 10, 12};

const int PENTATONIC_LENGTH = 6;
const int MAJOR_PENTATONIC_INTERVALS[] = {0, 2, 5, 7, 10, 12};
const int MINOR_PENTATONIC_INTERVALS[] = {0, 3, 5, 7, 10, 12};

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
        scale[i].frequency = getFrequencyFromTonicAndInterval(tonic, intervals[i]);
        scale[i].value = CROTCHET;
    }

    return scale;
}

Note *getScaleArray(const char *scaleName, float tonic)
{
    if (isDiminishedHalfWholeName(scaleName))
    {
        return createScaleArray(tonic, DIMINISHED_HALF_WHOLE_INTERVALS, DIMINISHED_LENGTH);
    }
    else if (isDiminishedWholeHalfName(scaleName))
    {
        return createScaleArray(tonic, DIMINISHED_WHOLE_HALF_INTERVALS, DIMINISHED_LENGTH);
    }
    else if (isMajorName(scaleName))
    {
        return createScaleArray(tonic, MAJOR_INTERVALS, STANDARD_LENGTH);
    }
    else if (isMinorName(scaleName))
    {
        return createScaleArray(tonic, NATURAL_MINOR_INTERVALS, STANDARD_LENGTH);
    }
    else if (isHarmonicMinorName(scaleName))
    {
        return createScaleArray(tonic, HARMONIC_MINOR_INTERVALS, STANDARD_LENGTH);
    }
    else if (isMixolydianName(scaleName))
    {
        return createScaleArray(tonic, MIXOLYDIAN_INTERVALS, STANDARD_LENGTH);
    }
    else if (isDorianName(scaleName))
    {
        return createScaleArray(tonic, DORIAN_INTERVALS, STANDARD_LENGTH);
    }
    else if (isPhrygianName(scaleName))
    {
        return createScaleArray(tonic, PHRYGIAN_INTERVALS, STANDARD_LENGTH);
    }
    else if (isLocrianName(scaleName))
    {
        return createScaleArray(tonic, LOCRIAN_INTERVALS, STANDARD_LENGTH);
    }
    else if (isLydianName(scaleName))
    {
        return createScaleArray(tonic, LYDIAN_INTERVALS, STANDARD_LENGTH);
    }
    else if (isBluesName(scaleName))
    {
        return createScaleArray(tonic, BLUES_INTERVALS, BLUES_LENGTH);
    }
    else if (isWholeToneName(scaleName))
    {
        return createScaleArray(tonic, WHOLE_TONE_INTERVALS, BLUES_LENGTH);
    }
    else if (isMajorPentatonicName(scaleName))
    {
        return createScaleArray(tonic, MAJOR_PENTATONIC_INTERVALS, PENTATONIC_LENGTH);
    }
    else if (isMinorPentatonicName(scaleName))
    {
        return createScaleArray(tonic, MINOR_PENTATONIC_INTERVALS, PENTATONIC_LENGTH);
    }

    return NULL;
}
