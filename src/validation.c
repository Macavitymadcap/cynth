#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"
#include "waveforms.h"
#include "wav.h"

void checkUsage(int argc)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: ./cynth output waveform note seconds\n");
        exit(EXIT_FAILURE);
    }
}

int isSine(const char *waveformName)
{
    return strcmp(waveformName, SINE) == 0;
}

int isSquare(const char *waveformName)
{
    return strcmp(waveformName, SQUARE) == 0;
}

int isSawtooth(const char *waveformName)
{
    return strcmp(waveformName, SAWTOOTH) == 0;
}

int isTriangle(const char *waveformName)
{
    return strcmp(waveformName, TRIANGLE) == 0;
}

int isPulse(const char *waveformName)
{
    return strcmp(waveformName, PULSE) == 0;
}

void checkWaveformName(const char *waveformName)
{
    if (!isSine(waveformName) &&
        !isSawtooth(waveformName) &&
        !isSquare(waveformName) &&
        !isTriangle(waveformName) &&
        !isPulse(waveformName))
    {
        fprintf(stderr, "Invalid waveformName: %s\n", waveformName);
        fprintf(stderr, "Available waveforms: sine, square, sawtooth, triangle, pulse\n");
        exit(EXIT_FAILURE);
    }
}

int isValidNote(char note)
{
    return note >= 'c' && note <= 'g';
}

int isValidFlat(char note)
{
    return note == 'a' || note == 'b' || note == 'd' || note == 'e' || note == 'g';
}

int isValidPitch(int pitch)
{
    return pitch >= 0 && pitch <= 8;
}

void checkNoteName(const char *noteName)
{
    const char *invalidNote = "Invalid note:";
    int nameLength = strlen(noteName);
    if (nameLength > 3 || nameLength < 2)
    {
        fprintf(stderr, "%s '%s'. Note must be 2 or 3 characters.\n", invalidNote, noteName);
        exit(EXIT_FAILURE);
    }

    char note = noteName[0];
    int pitch;

    if (isValidNote(note) == 0)
    {
        fprintf(stderr, "%s '%s'. Notes must be a lower case character a-g.\n", invalidNote, noteName);
        exit(EXIT_FAILURE);
    }
    if (nameLength == 3)
    {
        if (noteName[1] != 'b')
        {
            fprintf(stderr, "%s '%s'. Use 'b' to indicate a flat.\n", invalidNote, noteName);
            exit(EXIT_FAILURE);
        }

        if (isValidFlat(note) == 0)
        {
            fprintf(stderr, "%s '%s'. %c cannot be flat.\n", invalidNote, noteName, note);
            exit(EXIT_FAILURE);
        }

        pitch = noteName[2] - '0';
        if (isValidPitch(pitch) == 0)
        {
            fprintf(stderr, "%s '%s'. Pitch must be in range 0-8.\n", invalidNote, noteName);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pitch = noteName[1] - '0';
        if (isValidPitch(pitch) == 0)
        {
            fprintf(stderr, "%s '%s'. Pitch must be in range 0-8.\n", invalidNote, noteName);
            exit(EXIT_FAILURE);
        }
    }
}

void printAllocationError(const char *allocatee)
{
    fprintf(stderr, "Error allocating %s\n", allocatee);
}

void checkWavHeaderAllocation(WavHeader *wavHeader)
{
    if (wavHeader == NULL)
    {
        printAllocationError("wavHeader");
        exit(EXIT_FAILURE);
    }
}

void checkBufferAllocation(short int *buffer)
{
    if (buffer == NULL)
    {
        printAllocationError("buffer");
        exit(EXIT_FAILURE);
    }
}

void checkFileOpening(FILE *output, const char *fileName)
{
    if (output == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", fileName);
        fclose(output);
        exit(EXIT_FAILURE);
    }
}