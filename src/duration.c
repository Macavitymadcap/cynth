#include <math.h>
#include <stdlib.h>

#include "duration.h"

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

int getMillisecondsPerBeat(int bpm)
{
    int minuteInMilliseconds = 60000;

    return round(minuteInMilliseconds / bpm);
}