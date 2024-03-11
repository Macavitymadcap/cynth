/**
 * @file scales.h
 * @brief extern constants and functions for creating scales.
*/

#ifndef SCALES_H
#define SCALES_H

#include "notes.h"

typedef struct Scale {
    int length;     /** Number of notes in the scale. */
    const int* intervals; /** Semitone intervals from tonic to last note of scale. */
} __attribute__((__packed__)) Scale;

/**
 * @brief String representing the name of the chromatic scale.
*/
extern const char *CHROMATIC;

/**
 * @brief String representing the name of the mixo-blues scale.
*/
extern const char *MIXO_BLUES;

/**
 * @brief String representing the name of the diminished (half-whole) scale.
*/
extern const char *DIMINISHED_HALF_WHOLE;

/**
 * @brief String representing the name of the diminished (whole-half) scale.
*/
extern const char *DIMINISHED_WHOLE_HALF;

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
 * @brief String representing the name of the Mixolydian scale.
*/
extern const char *MIXOLYDIAN;

/**
 * @brief String representing the name of the Dorian scale.
*/
extern const char *DORIAN;

/**
 * @brief String representing the name of the Phrygian scale.
*/
extern const char *PHRYGIAN;

/**
 * @brief String representing the name of the Locrian scale.
*/
extern const char *LOCRIAN;

/**
 * @brief String representing the name of the Lydian scale.
*/
extern const char *LYDIAN;

/**
 * @brief String representing the name of the Blues scale.
*/
extern const char *BLUES;

/**
 * @brief String representing the name of the Whole Tone scale.
*/
extern const char *WHOLE_TONE;

/**
 * @brief String representing the name of the Major Pentatonic scale.
*/
extern const char *MAJOR_PENTATONIC;

/**
 * @brief String representing the name of the Minor Pentatonic scale.
*/
extern const char *MINOR_PENTATONIC;


/**
 * @brief The number of notes in the chromatic scale (including octave).
*/
extern const int CHROMATIC_LENGTH;

/**
 * @brief Intervals of the chromatic scale in semitones.
*/
extern const int CHROMATIC_INTERVALS[];

/**
 * @brief The number of notes in the mixo-blues scale (including octave).
*/
extern const int MIXO_BLUES_LENGTH;

/**
 * @brief The number of notes in Mixo-blues scale (including octave).
*/
extern const int MIXO_BLUES_INTERVALS[];

/**
 * @brief The number of notes in Diminsihed scales (including octave).
*/
extern const int DIMINISHED_LENGTH;

/**
 * @brief Intervals of the Diminished scale in semitones (half-whole).
*/
extern const int DIMINISHED_HALF_WHOLE_INTERVALS[]; 

/**
 * @brief Intervals of the Diminished scale in semitones (whole-half).
*/
extern const int DIMINISHED_HALF_WHOLE_INTERVALS[];

/**
 * @brief The number of notes whole tone scales (including octave) e.g major, natural minor.
*/
extern const int STANDARD_LENGTH;

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
 * @brief The intervals of the mixolydian mode in semitones.
*/
extern const int MIXOLYDIAN_INTERVALS[];

/**
 * @brief The intervals of the dorian mode in semitones.
*/
extern const int DORIAN_INTERVALS[];

/**
 * @brief The intervals of the phrygian mode in semitones.
*/
extern const int PHRYGIAN_INTERVALS[];

/**
 * @brief The intervals of the locrian mode in semitones.
*/
extern const int LOCRIAN_INTERVALS[];

/**
 * @brief The intervals of the lydian mode in semitones.
*/
extern const int LYDIAN_INTERVALS[];

/**
 * @brief Number of notes in the blues and whole tone scales (including ocatve).
*/
extern const int BLUES_LENGTH;

/**
 * @brief Intervals of the Blues scale in semitones.
*/
extern const int BLUES_INTERVALS[];

/**
 * @brief Intervals of the Whole Tone scale in semitones.
*/
extern const int WHOLE_TONE_INTERVALS[];

/**
 * @brief Number of notes in pentatonic scales (including ocatve).
*/
extern const int PENTATONIC_LENGTH;

/**
 * @brief Intervals of the Major Pentatonic scale in semitones.
*/
extern const int MAJOR_PENTATONIC_INTERVALS[];

/**
 * @brief Intervals of the Minor Pentatonic scale in semitones.
*/
extern const int MINOR_PENTATONIC_INTERVALS[];


/**
 * @brief Generate a Scale struct for he given intervals.
 * @param scaleLength Number of notes in the scale.
 * @param intervals Array of integers representing the semitones of the scale.
 * @returns A Scale sctruct encapsulating the given information.
*/
Scale *createScale(int scaleLength, const int *intervals);

/**
 * @brief Generate a scale based on the provided tonic and intervals.
 * 
 * The length of each Note is set to a crotchet (1/8th).
 * 
 * @param tonic The base frequency of the scale.
 * @param scale Struct conntaing the intervals and length of the scale.
 * @returns An array of Note structs of the desired scale.
*/
Note *createScaleArray(float tonic, Scale *scale);

/**
 * @brief Create a scale based on the name and tonic, excling the melodic minor.
 * @param scaleName String representing the name of the scale.
 * @param tonic The base frequency of the scale.
 * @returns Array of notes structs comprising the desired scale.
*/
Note *getScaleArray(const char *scaleName, float tonic);

#endif
