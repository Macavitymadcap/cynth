/**
 * @file validation.h
 * @brief Functions for checking command line arguments and throwing errors.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>
#include "wav.h"

/**
 * @brief Print the contents of a text file to the console.
 * @param filePath The relative path of the file to be printed.
*/
void printFile(const char* filePath);

/**
 * @brief Exit getWave if wrong number of args provided and print usage.
 * @param argc Number of arguments passed to the program.
 * @param programName The name of the program.
*/
void checkGetWaveUsage(int argc, const char *programName);

/**
 * @brief Exit getFourChords if wrong number of args provided and print usage.
 * @param argc Number of arguments passed to the program.
 * @param programName The name of the program.
*/
void checkGetFourChordsUsage(int argc, const char *programName);

/**
 * @brief Exit getScale if wrong number of args provided and print usage.
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
 * @brief Certermine if the note is within valid range.
 * @param pitch The number of the note.
 * @param note The letter of the note.
 * @param hasFlat 1 if the note is a flat, otherwise 0
 * @returns 1 if valid, otherwise 0.
*/
int isInNoteRange(int pitch, char note, int hasFlat);

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
 * @returns 1 if out of range, otherwise 0.
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

/**
 * @brief Exit program if keyName is invalid.
 * @param keyName String representing the desired key.
*/
void checkKeyName(const char *keyName);

/**
 * @brief Determine if the string matches the name of the chromatic scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isChromaticName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the mixo-blues scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMixoBluesName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the diminished (half-whole) scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isDiminishedHalfWholeName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the diminished (whole-half) scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isDiminishedWholeHalfName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the major scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMajorName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the natural minor scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMinorName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the harmonic minor scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isHarmonicMinorName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the melodic minor scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMelodicMinorName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the mixolydian scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMixolydianName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the dorian scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isDorianName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the phrygian scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isPhrygianName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the locrian scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isLocrianName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the lydian scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isLydianName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the blues scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isBluesName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the whole tone scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isWholeToneName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the major pentatonic scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMajorPentatonicName(const char *scaleName);

/**
 * @brief Determine if the string matches the name of the minor pentatonic scale.
 * @param scaleName String to be checked.
 * @returns 1 if valid, otherwise 0.
*/
int isMinorPentatonicName(const char *scaleName);

/**
 * @brief Exit program if scaleName is invalid.
 * @param scaleName String to be checked.
*/
void checkScaleName(const char* scaleName);

/**
 * @brief Determine if the scale is of diminished length (9).
 * @returns 1 if true, else 0; 
*/
int isDiminishedLengthScale(const char *scaleName);

/**
 * @brief Determine if the scale is of standard length (8 -excluding the melodic minor).
 * @returns 1 if true, else 0; 
*/
int isStandardLengthScale(const char *scaleName);

/**
 * @brief Determine if the scale is of blues length (7).
 * @returns 1 if true, else 0; 
*/
int isBluesLengthScale(const char *scaleName);

/**
 * @brief Determine if the scale is of pentatonic length (6).
 * @returns 1 if true, else 0; 
*/
int isPentatonicLengthScale(const char *scaleName);

#endif
