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

Scale *createScale(int scaleLength, const int *intervals)
{
    size_t scaleSize = sizeof(Scale);
    Scale *scale = malloc(scaleSize);
    if (scale == NULL)
    {
        fprintf(stderr, "Error allocating scale\n");
        exit(EXIT_FAILURE);
    }

    scale->intervals = intervals;
    scale->length = scaleLength;
    
    return scale;
}

Note *createScaleArray(float tonic, Scale *scale)
{
    size_t scaleArraySize = scale->length * NOTE_SIZE;
    Note *scaleArray = malloc(scaleArraySize);
    if (scaleArray == NULL)
    {
        fprintf(stderr, "Error allocating scale array\n");
        exit(EXIT_FAILURE);
    }

    memset(scaleArray, 0, scaleArraySize);

    for (int i = 0; i < scale->length; i++)
    {
        scaleArray[i].frequency = getFrequencyFromTonicAndInterval(tonic, scale->intervals[i]);
        scaleArray[i].value = CROTCHET;
    }

    return scaleArray;
}

Note *getScaleArray(const char *scaleName, float tonic)
{
    Scale *scale = NULL;
    Note *scaleArray = NULL;

    if (isChromaticName(scaleName))
    {
        scale = createScale(CHROMATIC_LENGTH, CHROMATIC_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isMixoBluesName(scaleName))
    {
        scale = createScale(MIXO_BLUES_LENGTH, MIXO_BLUES_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isDiminishedHalfWholeName(scaleName))
    {   
        scale = createScale(DIMINISHED_LENGTH, DIMINISHED_HALF_WHOLE_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isDiminishedWholeHalfName(scaleName))
    {
        scale = createScale(DIMINISHED_LENGTH, DIMINISHED_WHOLE_HALF_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isMajorName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, MAJOR_INTERVALS);
        scaleArray = createScaleArray(tonic, scale); 
    }
    else if (isMinorName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, NATURAL_MINOR_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isHarmonicMinorName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, HARMONIC_MINOR_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isMixolydianName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, MIXOLYDIAN_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isDorianName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, DORIAN_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isPhrygianName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, PHRYGIAN_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isLocrianName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, LOCRIAN_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isLydianName(scaleName))
    {
        scale = createScale(STANDARD_LENGTH, LYDIAN_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isBluesName(scaleName))
    {
        scale = createScale(BLUES_LENGTH, BLUES_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isWholeToneName(scaleName))
    {
        scale = createScale(BLUES_LENGTH, WHOLE_TONE_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isMajorPentatonicName(scaleName))
    {
        scale = createScale(PENTATONIC_LENGTH, MAJOR_PENTATONIC_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }
    else if (isMinorPentatonicName(scaleName))
    {
        scale = createScale(PENTATONIC_LENGTH, MINOR_PENTATONIC_INTERVALS);
        scaleArray = createScaleArray(tonic, scale);
    }

    free(scale);

    return scaleArray;
}
