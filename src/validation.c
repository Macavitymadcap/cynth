#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "validation.h"
#include "waveforms.h"
#include "wav.h"
#include "scales.h"

void printFile(const char *filePath)
{
    FILE *filePointer;
    char character;

    filePointer = fopen(filePath, "r");
    if (filePointer == NULL)
    {
        fprintf(stderr, "Unable to open file: %s.\n", filePath);
        exit(EXIT_FAILURE);
    }

    while ((character = fgetc(filePointer)) != EOF)
    {
        putchar(character);
    }
    putchar('\n');

    fclose(filePointer);
}

void checkGetWaveUsage(int argc, const char *programName)
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s outfile waveform note seconds volume\n", programName);
        printFile("docs/get_wave.txt");
        exit(EXIT_FAILURE);
    }
}

void checkFourChordsUsage(int argc, const char *programName)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s outfile waveform bpm volume\n", programName);
        printFile("docs/four_chords.txt");
        exit(EXIT_FAILURE);
    }
}

void checkGetScaleUsage(int argc, const char *programName)
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s waveform tonic scale bpm volume\n", programName);
        printFile("docs/get_scale.txt");
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
        fprintf(stderr, "Invalid waveformName: '%s'\n", waveformName);
        fprintf(stderr, "Available waveforms: sine, square, sawtooth, triangle, pulse\n");
        exit(EXIT_FAILURE);
    }
}

int isValidNote(char note)
{
    return note >= 'a' && note <= 'g';
}

int isValidFlat(char note)
{
    return note == 'a' || note == 'b' || note == 'd' || note == 'e' || note == 'g';
}

int isValidPitch(int pitch)
{
    return pitch >= 0 && pitch <= 8;
}

int isInNoteRange(int pitch, int flat, char note)
{
    if (pitch == 8)
    {
        return note >= 'b';
    }
    if (pitch == 0)
    {
        return note <= 'c';
    }

    return 1;
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

int outOfBounds(int value, int min, int max)
{
    return value < min || value > max;
}

void checkSeconds(int seconds)
{
    if (outOfBounds(seconds, 1, 60))
    {
        fprintf(stderr, "Invalid seconds: '%i'. Must be number in range 1-60.\n", seconds);
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

void checkVolume(int volume)
{
    if (outOfBounds(volume, 1, 11))
    {
        fprintf(stderr, "Invalid volume: '%i'. Must be number in range 1-11\n", volume);
        exit(EXIT_FAILURE);
    }
}

void checkBpm(int bpm)
{
    if (outOfBounds(bpm, 1, 300))
    {
        fprintf(stderr, "Invalid bpm: '%i'. Must be number in range 1-300\n", bpm);
        exit(EXIT_FAILURE);
    }
}

int isChromaticName(const char *scaleName)
{
    return strcmp(scaleName, CHROMATIC) == 0;
}

int isMixoBluesName(const char *scaleName)
{
    return strcmp(scaleName, MIXO_BLUES) == 0;
}

int isDiminishedHalfWholeName(const char *scaleName)
{
    return strcmp(scaleName, DIMINISHED_HALF_WHOLE) == 0;
}

int isDiminishedWholeHalfName(const char *scaleName)
{
    return strcmp(scaleName, DIMINISHED_WHOLE_HALF) == 0;
}

int isMajorName(const char *scaleName)
{
    return strcmp(scaleName, MAJOR) == 0;
}

int isMinorName(const char *scaleName)
{
    return strcmp(scaleName, MINOR) == 0;
}

int isHarmonicMinorName(const char *scaleName)
{
    return strcmp(scaleName, HARMONIC_MINOR) == 0;
}

int isMelodicMinorName(const char *scaleName)
{
    return strcmp(scaleName, MELODIC_MINOR) == 0;
}

int isMixolydianName(const char *scaleName)
{
    return strcmp(scaleName, MIXOLYDIAN) == 0;
}

int isDorianName(const char *scaleName)
{
    return strcmp(scaleName, DORIAN) == 0;
}

int isPhrygianName(const char *scaleName)
{
    return strcmp(scaleName, PHRYGIAN) == 0;
}

int isLocrianName(const char *scaleName)
{
    return strcmp(scaleName, LOCRIAN) == 0;
}

int isLydianName(const char *scaleName)
{
    return strcmp(scaleName, LYDIAN) == 0;
}

int isBluesName(const char *scaleName)
{
    return strcmp(scaleName, BLUES) == 0;
}

int isWholeToneName(const char *scaleName)
{
    return strcmp(scaleName, WHOLE_TONE) == 0;
}

int isMajorPentatonicName(const char *scaleName)
{
    return strcmp(scaleName, MAJOR_PENTATONIC) == 0;
}

int isMinorPentatonicName(const char *scaleName)
{
    return strcmp(scaleName, MINOR_PENTATONIC) == 0;
}

void checkScaleName(const char *scaleName)
{
    if (!isChromaticName(scaleName) &&
        !isMixoBluesName(scaleName) &&
        !isDiminishedHalfWholeName(scaleName) &&
        !isDiminishedWholeHalfName(scaleName) &&
        !isMajorName(scaleName) &&
        !isMinorName(scaleName) &&
        !isHarmonicMinorName(scaleName) &&
        !isMelodicMinorName(scaleName) &&
        !isMixolydianName(scaleName) &&
        !isDorianName(scaleName) &&
        !isPhrygianName(scaleName) &&
        !isLocrianName(scaleName) &&
        !isLydianName(scaleName) &&
        !isBluesName(scaleName) &&
        !isWholeToneName(scaleName) &&
        !isMajorPentatonicName(scaleName) &&
        !isMinorPentatonicName(scaleName))
    {
        fprintf(stderr, "Invalid scale name: '%s'. Use one of:\n", scaleName);
        printf("\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n", CHROMATIC, MIXO_BLUES, DIMINISHED_HALF_WHOLE, DIMINISHED_WHOLE_HALF, MAJOR, MINOR, HARMONIC_MINOR, MELODIC_MINOR);
        printf("\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n\t- %s\n", MIXOLYDIAN, DORIAN, PHRYGIAN, LOCRIAN, LYDIAN, BLUES, WHOLE_TONE, MAJOR_PENTATONIC, MINOR_PENTATONIC);

        exit(EXIT_FAILURE);
    }
}

int isDiminishedLengthScale(const char *scaleName)
{
    return isDiminishedHalfWholeName(scaleName) || isDiminishedWholeHalfName(scaleName);
}

int isStandardLengthScale(const char *scaleName)
{
    return (isMajorName(scaleName) ||
            isHarmonicMinorName(scaleName) ||
            isMinorName(scaleName) ||
            isMixolydianName(scaleName) ||
            isDorianName(scaleName) ||
            isPhrygianName(scaleName) ||
            isLocrianName(scaleName) ||
            isLydianName(scaleName));
}

int isBluesLengthScale(const char *scaleName)
{
    return isBluesName(scaleName) || isWholeToneName(scaleName);
}

int isPentatonicLengthScale(const char *scaleName)
{
    return isMajorPentatonicName(scaleName) || isMinorPentatonicName(scaleName);
}
