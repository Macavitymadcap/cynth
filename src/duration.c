#include <stdlib.h>

#include "duration.h"
#include "validation.h"

const float BREVE = 2.0;
const float SEMIBREVE = 1.0;
const float MINIM = 0.5;
const float CROTCHET = 0.25;
const float QUAVER = 0.125;
const float SEMIQUAVER = 0.0625;
const float DEMISEMIQUAVER = 0.03125;
const float HEMIDEMISEMIQUAVER = 0.015625;
const float QUASIHEMIDEMISEMIQUAVER = 0.0078125;

const float FOUR_FOUR = 4.0;
const float THREE_FOUR = 3.0;

const int CHROMATIC_SCALE_MEASURES = 12;
const int MIXO_BLUES_OR_DIMINISHED_SCALE_MEASURES = 10;
const int STANDARD_OR_BLUES_SCALE_MEASURES = 8;
const int PENTATONIC_SCALE_MEASURES = 6;

int getTotalMeasuresForScale(const char *scaleName)
{
    if (isChromaticName(scaleName))
    {
        return CHROMATIC_SCALE_MEASURES;
    }
    else if (isMixoBluesName(scaleName) || isDiminishedLengthScale(scaleName))
    {
        return MIXO_BLUES_OR_DIMINISHED_SCALE_MEASURES;
    }
    else if (isStandardLengthScale(scaleName) || isBluesLengthScale(scaleName) || isMelodicMinorName(scaleName))
    {
        return STANDARD_OR_BLUES_SCALE_MEASURES;
    }
    else if (isPentatonicLengthScale(scaleName))
    {
        return PENTATONIC_SCALE_MEASURES;
    }

    return 0;
}