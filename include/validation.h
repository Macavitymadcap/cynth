/**
 * @file validation.h
 * @brief Functions for checking command line arguments and throwing errors.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include "wav.h"

/**
 * @brief Exit the program if wrong number of args provided and print usage.
 * @param argc Number of arguments passed to the program.
 * @param programName The name of the program.
*/
void checkGetWaveUsage(int argc, const char *programName);

/**
 * @brief Exit the program if wrong number of args provided and print usage.
 * @param argc Number of arguments passed to the program.
 * @param programName The name of the program.
*/
void checkFourChordsUsage(int argc, const char *programName);

/**
 * @brief Exit the program if wrong number of args provided and print usage.
 * @param argc Number of arguments passed to the program.
 * @param programName The name of the program.
*/
void checkGetScaleUsage(int argc, const char *programName);

/**
 * @brief Exit the program if the filename is invalid.
 * @param fileName The name of the file to be checked.
*/
void checkFileName(const char *fileName);

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
 * @brief Determine whether a value is outside of a given range
 * @param value Number to be checked.
 * @param min Lower bound of range.
 * @param max Upper bound of range.
 * @return 1 if out of range, otherwise 0.
 * 
*/
int outOfBounds(int value, int min, int max);

/**
 * @brief Exit program if seconds are out of valid range.
 * @param seconds Integer representing length of waveform in seconds.
*/
void checkSeconds(int seconds);

/**
 * @brief Exit program if volume is out of valid range.
 * @param volume Integer to be checked. 
*/
void checkVolume(int volume);

/**
 * @brief Close file and exit program if the file opened is NULL.
 * @param output Filestream to be checked for nullness.
 * @param fileName String representing the strings name.
*/
void checkFileOpening(FILE *output, const char *fileName);

/**
 * @brief Exit program if bpm is outside valid range.
 * @param bpm Integer to be checked.
*/
void checkBpm(int bpm);

#endif // VALIDATION_H
