/**
 * @file scales.h
 * @brief Constants and functions for creating scales.
*/

#ifndef SCALES_H
#define SCALES_H

#include "notes.h"

/**
 * @brief String representing the name of the major scale.
*/
extern const char *MAJOR;

/**
 * @brief String representing the name of the natural minor scale.
*/
extern const char *MINOR;

/**
 * @brief string representing the name of the harmonic minor scale.
*/
extern const char *HARMONIC_MINOR;

/**
 * @brief string representing the name of the melodic minor scale.
*/
extern const char *MELODIC_MINOR; 

/**
 * @brief The intervals of the major scale in semitones.
*/
extern const int MAJOR_INTERVALS[];

/**
 * @brief The intervals of the natural minor scale in semitones.
*/
extern const int NATURAL_MINOR_INTERVALS[];

/**
 * @brief The intervals of the harmonic minor scale in semitones.
*/
extern const int HARMONIC_MINOR_INTERVALS[];

/**
 * @brief The intervals of the melodic minor scale in semitones when ascending.
*/
extern const int ASCENDING_MELODIC_MINOR_INTERVALS[];

/**
 * @brief The intervals of the melodic minor scale in semitones when descending.
*/
extern const int DESCENDING_MELODIC_MINOR_INTERVALS[];

/**
 * @brief The number of notes whole tone scales (including octave) e.g major, natural minor.
*/
extern const int WHOLE_TONE_LENGTH;


/**
 * @brief Generate a scale based on the provided tonic and intervals.
 * 
 * The frequency of each Note is calculated using the formula:
 * `frequency = tonic * 2^(semitones / 12)`.
 * The length of each Note is set to a crotchet (1/8th).
 * 
 * @param tonic The base frequency of the scale.
 * @param intervals Array of int containing the intervals of the scale.
 * @param scaleLength The number of notes in the scale
 * @returns An array of Note structs of the desired scale.
*/
Note *createScaleArray(float tonic, const int *intervals, const int scaleLength);


/**
 * @brief Create a scale based on the name and tonic, excling the melodic minor.
 * @param scaleName String representing the name of the scale.
 * @param tonic The base frequency of the scale.
 * @returns Array of notes structs comprising the desired scale.
*/
Note *getScale(const char *scaleName, float tonic);

#endif