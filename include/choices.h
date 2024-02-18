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

#endif
