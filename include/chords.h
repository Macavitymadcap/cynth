/**
 * @file chords.h
 * @brief Functions for generating chords
*/

#ifndef CHORDS_H
#define CHORDS_H

#include "notes.h"

/**
 * @struct Chord
 * @brief Encapsulates information for a musical chord.
*/
typedef struct Chord
{
    Note *notes;    /** Array of Note structs comprising the chord. */
    int length;     /** Number of notes in the chord. */
} __attribute__((__packed__)) Chord;

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
 * @brief The intervals in the 1st inversion of a major triad chord.
*/
extern const int MAJOR_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a major triad chord.
*/
extern const int MAJOR_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in a minor triad chord.
*/
extern const int MINOR_TRIAD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a minor triad chord.
*/
extern const int MINOR_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a minor triad chord.
*/
extern const int MINOR_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in a diminished triad chord.
*/
extern const int DIMINISHED_TRIAD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a diminished triad chord.
*/
extern const int DIMINISHED_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a diminished triad chord.
*/
extern const int DIMINISHED_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in an augmented triad chord.
*/
extern const int AUGMENTED_TRIAD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of an augmented triad chord.
*/
extern const int AUGMENTED_TRIAD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of an augmented triad chord.
*/
extern const int AUGMENTED_TRIAD_2ND_INVERSION_INTERVALS[];

/**
 * @brief Number of notes in a 7th chord
*/
extern const int SEVENTH_LENGTH;

/**
 * @brief The intervals in a dominant 7th chord.
*/
extern const int DOMINANT_SEVENTH_CHORD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a dominant 7th chord.
*/
extern const int DOMINANT_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a dominant 7th chord.
*/
extern const int DOMINANT_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 3rd inversion of a dominant 7th chord.
*/
extern const int DOMINANT_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[];

/**
 * @brief The intervals in a major 7th chord.
*/
extern const int MAJOR_SEVENTH_CHORD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a major 7th chord.
*/
extern const int MAJOR_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a major 7th chord.
*/
extern const int MAJOR_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 3rd inversion of a major 7th chord.
*/
extern const int MAJOR_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[];

/**
 * @brief The intervals in a minor 7th chord.
*/
extern const int MINOR_SEVENTH_CHORD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a minor 7th chord.
*/
extern const int MINOR_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a minor 7th chord.
*/
extern const int MINOR_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 3rd inversion of a minor 7th chord.
*/
extern const int MINOR_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[];

/**
 * @brief The intervals in a diminished 7th chord.
*/
extern const int DIMINISHED_SEVENTH_CHORD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of a diminished 7th chord.
*/
extern const int DIMINISHED_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of a diminsihed 7th chord.
*/
extern const int DIMINISHED_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 3rd inversion of a diminished 7th chord.
*/
extern const int DIMINISHED_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[];

/**
 * @brief The intervals in an diminished 7th chord.
*/
extern const int AUGMENTED_SEVENTH_CHORD_INTERVALS[];

/**
 * @brief The intervals in the 1st inversion of an augmented 7th chord.
*/
extern const int AUGMENTED_SEVENTH_CHORD_1ST_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 2nd inversion of an augmented 7th chord.
*/
extern const int AUGMENTED_SEVENTH_CHORD_2ND_INVERSION_INTERVALS[];

/**
 * @brief The intervals in the 3rd inversion of an augmented 7th chord.
*/
extern const int AUGMENTED_SEVENTH_CHORD_3RD_INVERSION_INTERVALS[];

/**
 * @brief Generate array of Note structs for a chord.
 * 
 * @param tonic The base frequency of the chord.
 * @param value The duration of the chord
 * @param chordIntervals Array of ints containing the intervals of the chord.
 * @param chordLength The number of notes in the chord
 * @returns An array of Note structs of the desired chord.
*/
Note *createChordArray(float tonic, float value, const int *chordIntervals, const int chordLength);

/**
 * @brief Generate a chord based on the the tonic and intervals.
 * 
 * @param tonic The base frequency of the chord.
 * @param value The duration of the chord
 * @param chordIntervals Array of ints containing the intervals of the chord.
 * @param chordLength The number of notes in the chord
 * @returns A Chord struct for the desired chord.
*/
Chord *createChord(float tonic, float value, const int *chordIntervals, const int chordLength);

/**
 * @brief Generate the tonic notes for a given key to create a four chord song.
 * @param keyName Name of the major key for which to generate tonic notes.
 * @returns Array of floats for the I, IV, vi and V chords of the key.
*/
float *getFourChordTonics(const char *keyName);

/**
 * @brief Generat an array of Chord structs for the I, IV, vi and V progression.
 * @param keyName Name of the key for the progression.
 * @returns An array of Chord structs;
*/
Chord *getFourChords(const char *keyName);

#endif
