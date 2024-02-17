/**
 * @file chords.h
 * @brief Functions for generating chords
*/

#ifndef CHORDS_H
#define CHORDS_H

#include "notes.h"

/**
 * @brief Number of notes in a bass pedal chord.
*/
extern const int BASS_PEDAL_LENGTH;

/**
 * @brief The intervals in a bass pedal chord.
*/
extern const int BASS_PEDAL_INTERVALS[];

/**
 * @brief Number of notes in a triad chord;
*/
extern const int TRIAD_LENGTH;

/**
 * @brief The intervals in a major triad chord.
*/
extern const int MAJOR_TRIAD_INTERVALS[];

/**
 * @brief The intervals of the 1st inversion of a major triad chord.
*/
extern const int MAJOR_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals of the 2nd inversion of a major triad chord.
*/
extern const int MAJOR_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals of a minor triad chord.
*/
extern const int MINOR_TRIAD_INTERVALS[];

/**
 * @brief The intervals of the 1st inversion of a minor triad chord.
*/
extern const int MINOR_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals of the 2nd inversion of a minor triad chord.
*/
extern const int MINOR_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief Generate a chord based on the the tonic and intervals.
 * 
 * @param tonic The base frequency of the chord.
 * @param value The duration of the chord
 * @param chordIntervals Array of ints containing the intervals of the chord.
 * @param chordLength The number of notes in the chord
 * @returns An array of Note structs of the desired chord.
*/
Note *createChordArray(float tonic, float value, const int *chordIntervals, const int chordLength);

/**
 * @brief Generate the tonic notes for a given key to create a four chord song.
 * @param keyName Name of the major key for which to generate tonic notes.
 * @returns Array of floats for the I, IV, vi and V chords of the key.
*/
float *getFourChordTonics(const char *keyName);

#endif
