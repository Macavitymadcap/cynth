/**
 * @file duration.h
 * @brief Constants for musical duration.
*/

#ifndef DURATION_H
#define DURATION_H

/**
 * @brief A float representing the value of a double note.
*/
extern const float BREVE;

/**
 * @brief A float representing the value of a whole note.
*/
extern const float SEMIBREVE;

/**
 * @brief A float representing the value of a half note.
*/
extern const float MINIM;

/**
 * @brief A float representing the value of a quarter note.
*/
extern const float CROTCHET;

/**
 * @brief An float representing the value of a eight note.
*/
extern const float QUAVER;

/**
 * @brief A float representing the value of a sixteenth note
*/
extern const float SEMIQUAVER;

/**
 * @brief A float representing the value of a thrity-second note.
*/
extern const float DEMISEMIQUAVER;

/**
 * @brief A float representing the value of a sixty-fourth note.
*/
extern const float HEMIDEMISEMIQUAVER;

/**
 * @brief A float representing the value of a hunder twenty-eight note.
*/
extern const float QUASIHEMIDEMISEMIQUAVER;

/**
 * @brief A float representing the beats per measure in common (4/4) time.
*/
extern const float FOUR_FOUR;

/**
 * @brief A float representing the beats per measure in waltz (3/4) time.
*/
extern const float THREE_FOUR;

/**
 * @brief Total measure required to play a chromatic scale.
*/
extern const int CHROMATIC_SCALE_MEASURES;

/**
 * @brief Toral measure required to play a mixo-blues scale.
*/
extern const int MIXO_BLUES_OR_DIMINISHED_SCALE_MEASURES;

/**
 * @brief Number of measures required to play a standard or blues length scale.
*/
extern const int STANDARD_OR_BLUES_SCALE_MEASURES;

/**
 * @brief Number of measures required to play a pentatonic scale.
*/
extern const int PENTATONIC_SCALE_MEASURES;

/**
 * @brief Get the number of measures required to play the given scale.
 * @param scaleName String representing the name of the scale.
 * @returns The number of measures required to play the scale.
*/
int getTotalMeasuresForScale(const char *scaleName);

#endif
