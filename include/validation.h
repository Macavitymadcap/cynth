/**
 * @file validation.h
 * @brief Functions for checking command line arguments and throwing errors.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include "wav.h"

/**
 * @brief Exit the program if the number of command line arguments is wrong.
*/
void checkUsage(int argc);

/**
 * @brief Determine whether the waveform matches the name of the sine wave.
 * @param waveform String of waveform to be checked.
 * @returns 1 if the string matches, otherwise 0.
*/
int isSine(const char *waveform);


/**
 * @brief Determine whether the waveform matches the name of the sawtooth wave.
 * @param waveform String of waveform to be checked.
 * @returns 1 if the string matches, otherwise 0.
*/
int isSawtooth(const char *waveform);

/**
 * @brief Determine whether the waveform matches the name of the square wave.
 * @param waveform String of waveform to be checked.
 * @returns 1 if the string matches, otherwise 0.
*/
int isSquare(const char *waveform);


/**
 * @brief Determine whether the waveform matches the name of the triangle wave.
 * @param waveform String of waveform to be checked.
 * @returns 1 if the string matches, otherwise 0.
*/
int isTriangle(const char *waveform);


/**
 * @brief Determine whether the waveform matches the name of the pulse wave.
 * @param waveform String of waveform to be checked.
 * @returns 1 if the string matches, otherwise 0.
*/
int isPulse(const char *waveform);

/**
 * @brief Exit the program if an invalid waveformName is passed as an argument.
 * @param waveformName The name of the waveform to be checked.
*/
void checkWaveformName(const char *waveformName);

/**
 * @brief Determine if the passed character is a valid note.
 * @param note Character to be checked. Must be lower case a-g.
 * @returns 1 if valid, otherwise 0.
 * 
*/
int isValidNote(char note);

/**
 * @brief Determine if passed character is a valid flat note.
 * @param note Character to be checked. Must be a, b, d, e or g.
 * @returns 1 if valid, otherwise 0.
*/
int isValidFlat(char note);

/**
 * @brief Determine if the passed pitch is in valid range.
 * @param pitch Integer to be checked. Must be 0-8;
 * @returns 1 if valid, otherwise 0.
*/
int isValidPitch(int pitch);

/**
 * @brief Exit program if an inavlid noteName is passed as an argument.
 * @param noteName The name of the note to be checked.
*/
void checkNoteName(const char *noteName);

/**
 * @brief Print error message about memory allocation.
 * @param item The item for which memory allocation has failed.
*/
void printAllocationError(const char *item);

/**
 * @brief Exit program if the wavHeader is NULL.
 * @param wavHeader The WavHeader to be checked.
*/
void checkWavHeaderAllocation(WavHeader *wavHeader);

/**
 * @brief Exit the program if the buffer is NULL. 
 * @param buffer The buffer to be checked. 
*/
void checkBufferAllocation(short int *buffer);

/**
 * @brief Close file and exit program if the file opened is NULL.
 * @param output Filestream to be checked for nullness.
 * @param fileName String representing the strings name.
*/
void checkFileOpening(FILE *output, const char *fileName);

#endif // VALIDATION_H