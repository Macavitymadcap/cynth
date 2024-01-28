#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "validation.h"
#include "waveforms.h"
#include "wav.h"

void checkGetWaveUsage(int argc, const char *programName)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s outfile waveform note seconds\n", programName);
        printf("    outfile:  Name of file to be written, must be .wav.\n");
        printf("    waveform: Type of waveform to generate, one of;\n");
        printf("              pulse; sawtooth; sine; square; or triangle.\n");
        printf("    note:     Note in lowercase, from c0 to b8, use 'b' for flats\n");
        printf("    seconds:  Length of generated waveform, from 1 - 60\n");
        exit(EXIT_FAILURE);
    }
}

void checkFourChordsUsage(int argc, const char *programName)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s waveform\n", programName);
        exit(EXIT_FAILURE);
    }
}

void checkGetScaleUsage(int argc, const char *programName)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s waveform\n", programName);
        exit(EXIT_FAILURE);
    }
}

void checkFileName(const char *fileName)
{
    regex_t regex;
    int ret;

    const char *pattern = "^[a-zA-Z0-9_]+\\.wav$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Error compiling regular expression\n");
        exit(EXIT_FAILURE);
    }

    ret = regexec(&regex, fileName, 0, NULL, 0);

    regfree(&regex);

    if (ret == REG_NOMATCH)
    {
        fprintf(stderr, "Invald file name: '%s'\n", fileName);
        exit(EXIT_FAILURE);
    }

    if (ret != 0)
    {
        fprintf(stderr, "Error executing regular expression\n");
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

void checkSeconds(int seconds)
{
    if (seconds > 60 || seconds < 1)
    {
        fprintf(stderr, "Invalid seconds: %i. Must be number in range 1 -60.\n", seconds);
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
