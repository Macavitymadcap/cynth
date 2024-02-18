#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "waveforms.h"

int getRandomInt(int maximum)
{
    return (rand() % maximum);
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
