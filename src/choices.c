#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "choices.h"
#include "waveforms.h"
#include "duration.h"

int getRandomInt(int maximum)
{
    return (arc4random() % maximum);
}

const char *getRandomWaveformName(void)
{
    const int choice = getRandomInt(5);

    switch (choice)
    {
    case 0:
        return SINE;

    case 1:
        return SAWTOOTH;

    case 2:
        return SQUARE;

    case 3:
        return TRIANGLE;

    default:
        return PULSE;
    }
}

float getRandomFloatFromArray(float *array, int size)
{
    int choiceIndex = getRandomInt(size);

    return array[choiceIndex];
}

float getRandomNoteValue(float barCompletion)
{
    // if (barCompletion >= 0)
    // {
    //     float choices[] = {SEMIBREVE, MINIM, CROTCHET, QUAVER, SEMIQUAVER, DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER};
    //     return getRandomFloatFromArray(choices, 8);
    // }
    // else if (barCompletion >= MINIM)
    // {
    //     float choices[] = {MINIM, CROTCHET, QUAVER, SEMIQUAVER, DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER};
    //     return getRandomFloatFromArray(choices, 7);
    // }
    // else if (barCompletion >= MINIM + CROTCHET)
    // {
    //     float choices[] = {CROTCHET, QUAVER, SEMIQUAVER, DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER};
    //     return getRandomFloatFromArray(choices, 6);
    // } 
    // else if (barCompletion >= MINIM + CROTCHET + QUAVER)
    // {
    //     float choices[] = {QUAVER, SEMIBREVE, DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER };
    //     return getRandomFloatFromArray(choices, 5);
    // }
    // else if (barCompletion >= MINIM + CROTCHET + QUAVER + SEMIBREVE)
    // {
    //     float choices[] = { SEMIBREVE, DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER };
    //     return getRandomFloatFromArray(choices, 4);
    // }
    // else if (barCompletion >= MINIM + CROTCHET + QUAVER + SEMIQUAVER + DEMISEMIQUAVER)
    // {
    //     float choices[] = { DEMISEMIQUAVER, HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER };
    //     return getRandomFloatFromArray(choices, 3);
    // }
    // else if (barCompletion >= MINIM + CROTCHET + QUAVER + SEMIBREVE + DEMISEMIQUAVER + HEMIDEMISEMIQUAVER)
    // {
    //     float choices[] = { HEMIDEMISEMIQUAVER, QUASIHEMIDEMISEMIQUAVER };
    //     return getRandomFloatFromArray(choices, 2);
    // }
    // else
    // {
    //     return QUASIHEMIDEMISEMIQUAVER;
    // }

    if (barCompletion == 0)
    {
        float choices[] = {MINIM, CROTCHET, QUAVER, SEMIQUAVER};
        return getRandomFloatFromArray(choices, 4);
    }
    else if (barCompletion >= MINIM && barCompletion < 1)
    {
        float choices[] = {CROTCHET, QUAVER, SEMIQUAVER};
        return getRandomFloatFromArray(choices, 3);
    }
    else if (barCompletion >= MINIM + CROTCHET && barCompletion < 1)
    {
        float choices[] = {QUAVER, SEMIQUAVER};
        return getRandomFloatFromArray(choices, 2);
    } 
    else 
    {
        return SEMIQUAVER;
    }
}
