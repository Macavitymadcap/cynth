/**
 * @file scales.h
 * @brief Constants and functions for creating scales.
*/

#ifndef SCALES_H
#define SCALES_H

#include "notes.h"

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
extern const int WHOLE_TONE_SCALE_LENGTH;


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

#endif