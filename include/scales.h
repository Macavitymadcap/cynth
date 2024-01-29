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
extern const int MAJOR_SCALE_INTERVALS[];

/**
 * @brief The number of notes in the major scale (including octave).
*/
extern const int MAJOR_SCALE_LENGTH;


/**
 * @brief Generate a scale based on the provided tonic and intervals.
 * 
 * The frequency of each Note is calculated using the formula:
 * `frequency = tonic * 2^(semitones / 12)`.
 * The length of each Note is set to a crotchet (1/8th).
 * 
 * @param tonic The base frequency of the scale.
 * @param intervals Array of int conatining the intervals of the scale.
 * @param scaleLength The number of notes in the scale
 * @returns An array of Note structs of the desired scale.
*/
Note *createScaleArray(float tonic, const int *intervals, const int scaleLength);

#endif