/**
 * @file choices.h
 * @brief functions for randomly selecting options.
*/

#ifndef CHOICES_H
#define CHOICES_H

/**
 * @brief Get a random number between 0 and maximum.
 * @param maximum Upper bound of random number to be generated.
 * @returns a number within the given range.
*/
int getRandomInt(int maximum);

/**
 * @brief Randomly select a wavefrom type.
 * One of; sine; sawtooth; sqaure; triangle or pulse.
 * @returns a string representing the name of a waveform.
*/
const char *getRandomWaveformName(void);

/**
 * @brief Returns a randomly selected float from an array.
 * @param array Floats from which to select.
 * @param size Number of floats in the array.
 * @returns A float from the given array.
*/
float getRandomFloatFromArray(float *array, int size);

/**
 * @brief Return a randomly selected duration, excluding breve.
 * @returns a float representing a note's duration.
*/
float getRandomNoteValue(float barCompletion);

#endif
