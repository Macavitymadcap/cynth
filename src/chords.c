#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chords.h"
#include "notes.h"
#include "validation.h"

const int BASS_PEDAL_LENGTH = 2;
const int BASS_PEDAL_INTERVALS[] = {0, 12};

const int TRIAD_LENGTH = 3;
const int MAJOR_TRIAD_INTERVALS[] = {0, 4, 7};
const int MAJOR_TRIAD_1ST_INVERSION_INTERVALS[] = {-8, -5, 0};
const int MAJOR_TRIAD_2ND_INVERSION_INTERVALS[] = {-5, 0, 4};
const int MINOR_TRIAD_INTERVALS[] = {0, 3, 7};
const int MINOR_TRIAD_1ST_INVERSION_INTERVALS[] = {-9, -5, 0};
const int MINOR_TRIAD_2ND_INVERSION_INTERVALS[] = {-5, 0, 3};

Note *createChordArray(float tonic, float value, const int *chordIntervals, const int chordLength)
{
    size_t chordSize = chordLength * NOTE_SIZE;
    Note *chord = malloc(chordSize);
    if (chord == NULL)
    {
        fprintf(stderr, "Error allocating chord.\n");
        exit(EXIT_FAILURE);
    }

    memset(chord, 0, chordSize);

    for (int i = 0; i < chordLength; i++)
    {
        chord[i].frequency = getFrequencyFromTonicAndInterval(tonic, chordIntervals[i]);
        chord[i].value = value;
    }

    return chord;
}

float *getFourChordTonics(const char *keyName)
{
    const int tonicsLength = 8;
    float *tonics = malloc(sizeof(float) * tonicsLength);
    if (tonics == NULL)
    {
        fprintf(stderr, "Error alloacting tonics.\n");
        exit(EXIT_FAILURE);
    }

    memset(tonics, 0, tonicsLength);

    if (strcmp(NOTE_NAMES[0], keyName) == 0)
    {
        tonics[0] = C2;
        tonics[1] = G2;
        tonics[2] = A2;
        tonics[3] = F2;
        tonics[4] = C4;
        tonics[5] = G4;
        tonics[6] = A4;
        tonics[7] = F4;
    }
    else if (strcmp(NOTE_NAMES[1], keyName) == 0)
    {
        tonics[0] = Db2;
        tonics[1] = Ab2;
        tonics[2] = Bb2;
        tonics[3] = Gb2;
        tonics[4] = Db4;
        tonics[5] = Ab4;
        tonics[6] = Bb4;
        tonics[7] = Gb4;
    }
    else if (strcmp(NOTE_NAMES[2], keyName) == 0)
    {
        tonics[0] = D2;
        tonics[1] = A2;
        tonics[2] = B2;
        tonics[3] = G2;
        tonics[4] = D4;
        tonics[5] = A4;
        tonics[6] = B4;
        tonics[7] = G4;
    }
    else if (strcmp(NOTE_NAMES[3], keyName) == 0)
    {
        tonics[0] = Eb2;
        tonics[1] = Bb2;
        tonics[2] = C2;
        tonics[3] = Ab2;
        tonics[4] = Eb4;
        tonics[5] = Bb4;
        tonics[6] = C5;
        tonics[7] = Ab4;
    }
    else if (strcmp(NOTE_NAMES[4], keyName) == 0)
    {
        tonics[0] = E2;
        tonics[1] = B2;
        tonics[2] = Db2;
        tonics[3] = A2;
        tonics[4] = E4;
        tonics[5] = B4;
        tonics[6] = Db5;
        tonics[7] = A4;
    }
    else if (strcmp(NOTE_NAMES[5], keyName) == 0)
    {
        tonics[0] = F2;
        tonics[1] = C2;
        tonics[2] = D2;
        tonics[3] = Bb2;
        tonics[4] = F4;
        tonics[5] = C5;
        tonics[6] = D5;
        tonics[7] = Bb4;
    }
    else if (strcmp(NOTE_NAMES[6], keyName) == 0)
    {
        tonics[0] = Gb2;
        tonics[1] = Db2;
        tonics[2] = Eb2;
        tonics[3] = B2;
        tonics[4] = Gb4;
        tonics[5] = Db5;
        tonics[6] = Eb5;
        tonics[7] = B4;
    }
    else if (strcmp(NOTE_NAMES[7], keyName) == 0)
    {
        tonics[0] = G2;
        tonics[1] = D2;
        tonics[2] = E2;
        tonics[3] = C2;
        tonics[4] = G4;
        tonics[5] = D5;
        tonics[6] = E5;
        tonics[7] = C4;
    }
    else if (strcmp(NOTE_NAMES[8], keyName) == 0)
    {
        tonics[0] = Ab2;
        tonics[1] = Eb2;
        tonics[2] = F2;
        tonics[3] = Db2;
        tonics[4] = Ab4;
        tonics[5] = Eb5;
        tonics[6] = F5;
        tonics[7] = Db5;
    }
    else if (strcmp(NOTE_NAMES[9], keyName) == 0)
    {
        tonics[0] = A2;
        tonics[1] = E2;
        tonics[2] = Gb2;
        tonics[3] = D2;
        tonics[4] = A4;
        tonics[5] = E5;
        tonics[6] = Gb5;
        tonics[7] = D5;
    }
    else if (strcmp(NOTE_NAMES[10], keyName) == 0)
    {
        tonics[0] = Bb2;
        tonics[1] = F2;
        tonics[2] = G2;
        tonics[3] = Eb2;
        tonics[4] = Bb4;
        tonics[5] = F5;
        tonics[6] = G5;
        tonics[7] = Eb5;
    }
    else
    {
        tonics[0] = B2;
        tonics[1] = Gb2;
        tonics[2] = Ab2;
        tonics[3] = E2;
        tonics[4] = B4;
        tonics[5] = Gb5;
        tonics[6] = Ab5;
        tonics[7] = E5;
    }

    return tonics;
}
