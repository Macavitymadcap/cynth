#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chords.h"
#include "notes.h"
#include "validation.h"
#include "duration.h"

const int BASS_PEDAL_LENGTH = 2;
const int BASS_PEDAL_INTERVALS[] = {0, 12};

const int TRIAD_LENGTH = 3;
const int MAJOR_TRIAD_INTERVALS[] = {0, 4, 7};
const int MAJOR_TRIAD_1ST_INVERSION_INTERVALS[] = {-8, -5, 0};
const int MAJOR_TRIAD_2ND_INVERSION_INTERVALS[] = {-5, 0, 4};

const int MINOR_TRIAD_INTERVALS[] = {0, 3, 7};
const int MINOR_TRIAD_1ST_INVERSION_INTERVALS[] = {-9, -5, 0};
const int MINOR_TRIAD_2ND_INVERSION_INTERVALS[] = {-5, 0, 3};

const int DIMINISHED_TRIAD_INTERVALS[] = {0, 3, 6};
const int DIMINISHED_TRIAD_1ST_INVERSION_INTERVALS[] = {-9, -6, 0};
const int DIMINISHED_TRIAD_2ND_INVERSION_INTERVALS[] = {-6, 0, 3};

const int AUGMENTED_TRIAD_INTERVALS[] = {0, 4, 8};
const int AUGMENTED_TRIAD_1ST_INVERSION_INTERVALS[] = {-8, -4, 0};
const int AUGMENTED_TRIAD_2ND_INVERSION_INTERVALS[] = {-4, 0, 4};

const int SEVENTH_LENGTH = 4;
const int DOMINANT_SEVENTH_CHORD_INTERVALS[] = {0, 4, 7, 10};
const int DOMINANT_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[] = {-8, -5, -1, 0};
const int DOMINANT_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[] = {-5, -1, 0, 4};
const int DOMINANT_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[] = {-1, 0, 4, 7};

const int MAJOR_SEVENTH_CHORD_INTERVALS[] = {0, 4, 7, 11};
const int MAJOR_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[] = {-8, -3, 0, 4};
const int MAJOR_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[] = {-3, 0, 4, 7};
const int MAJOR_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[] = {0, 4, 7, 11};

const int MINOR_SEVENTH_CHORD_INTERVALS[] = {0, 3, 7, 10};
const int MINOR_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[] = {-9, -5, 0, 3};
const int MINOR_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[] = {-5, 0, 3, 7};
const int MINOR_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[] = {0, 3, 7, 10};

const int DIMINISHED_SEVENTH_CHORD_INTERVALS[] = {0, 3, 6, 9};
const int DIMINISHED_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[] = {-9, -6, -3, 0};
const int DIMINISHED_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[] = {-6, -3, 0, 3};
const int DIMINISHED_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[] = {-3, 0, 3, 6};

const int AUGMENTED_SEVENTH_CHORD_INTERVALS[] = {0, 4, 8, 10};
const int AUGMENTED_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[] = {-8, -4, 0, 6};
const int AUGMENTED_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[] = {-4, 0, 6, 10};
const int AUGMENTED_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[] = {0, 6, 10, 16};

Note *createChordArray(float tonic, float value, const int *chordIntervals, const int chordLength)
{
    size_t chordSize = chordLength * NOTE_SIZE;
    Note *chordArray = malloc(chordSize);
    if (chordArray == NULL)
    {
        fprintf(stderr, "Error allocating chordArray.\n");
        exit(EXIT_FAILURE);
    }

    memset(chordArray, 0, chordSize);

    for (int i = 0; i < chordLength; i++)
    {
        chordArray[i].frequency = getFrequencyFromTonicAndInterval(tonic, chordIntervals[i]);
        chordArray[i].value = value;
    }

    return chordArray;
}

const size_t CHORD_SIZE = sizeof(Chord);

Chord *createChord(float tonic, float value, const int *intervals, const int chordLength)
{
    Chord *chord = malloc(CHORD_SIZE);
    if (chord == NULL)
    {
        fprintf(stderr, "Error allocating Chord\n");
        exit(EXIT_FAILURE);
    }

    chord->length = chordLength;
    chord->notes = createChordArray(tonic, value, intervals, chordLength);

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
        tonics[7] = C5;
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

Chord *getFourChords(const char *keyName)
{
    const int totalChords = 8;
    float *tonics = getFourChordTonics(keyName);

    Chord *chords = malloc(CHORD_SIZE * totalChords);
    if (chords == NULL)
    {
        fprintf(stderr, "Error allocating chords\n");
        exit(EXIT_FAILURE);
    }
    memset(chords, 0, totalChords);

    Chord *bassI = createChord(tonics[0], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
    chords[0] = *bassI;
    free(bassI);

    Chord *I = createChord(tonics[4], CROTCHET, MAJOR_TRIAD_INTERVALS, TRIAD_LENGTH);
    chords[1] = *I;
    free(I);

    Chord *bassIV = createChord(tonics[1], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
    chords[2] = *bassIV;
    free(bassIV);

    Chord *IV = createChord(tonics[5], CROTCHET, MAJOR_TRIAD_1ST_INVERSION_INTERVALS, TRIAD_LENGTH);
    chords[3] = *IV;
    free(IV);

    Chord *viBass = createChord(tonics[2], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
    chords[4] = *viBass;
    free(viBass);

    Chord *vi = createChord(tonics[6], CROTCHET, MINOR_TRIAD_1ST_INVERSION_INTERVALS, TRIAD_LENGTH);
    chords[5] = *vi;
    free(vi);

    Chord *VIBass = createChord(tonics[3], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
    chords[6] = *VIBass;
    free(VIBass);

    Chord *VI =createChord(tonics[7], CROTCHET, MAJOR_TRIAD_2ND_INVERSION_INTERVALS, TRIAD_LENGTH);
    chords[7] = *VI;
    free(VI);

    free(tonics);

    return chords;
}
