/**
 * @file duration.h
 * @brief Functions and constants for musical duration.
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
 * @struct Tempo
 * @brief Structure encapsulating time information for a song.
*/
typedef struct
{
    int totalBars;              /** Number of bars in the song. */
    int sampleRate;             /** Rate at which notes will be sampled. */
    float timeSignature;        /** Number of beats in each bar. */
    int beatsPerMinute;         /** The overall tempo of the song. */
    int millisecondsPerBeat;    /** Durtion of each beat in milliseconds. */
    int samplesPerBeat;         /** Rate at which each beat is sampled. */
} __attribute__((__packed__)) Tempo;

/**
 * @brief Calculate milliseconds per beat based on beats per minute (BPM).
 *
 * This function calculates the duration of a beat in milliseconds given the
 * beats per minute (BPM). It uses the formula: milliseconds per beat = 60000 / BPM.
 * The result is rounded to the nearest integer before being returned.
 *
 * @param bpm Beats per minute (BPM) indicating the tempo of the music.
 * @return The calculated milliseconds per beat.
 *
 * @note The function relies on the standard C library function 'round' to round
 *       the result to the nearest integer. Ensure that the 'math.h' header is included
 *       if compiling with GCC or a compatible compiler.
 */
int getMillisecondsPerBeat(int bpm);

/**
 * @brief Calculate the number of samples per beat.
 * @param sampleRate Rate at which notes will be sampled.
 * @param milliscondsPerBeat Durtion of each beat in milliseconds.
 * @returns Number of samples per beat.
*/
int getSamplesBerBeat(int sampleRate, int millisecondsPerBeat);

/**
 * @brief Write song information to a Tempo struct
 * @param tempo Structre to which will be written.
 * @param totalBars Number of bars in the song.
 * @param sampleRate Rate at which notes will be sampled.
 * @param timeSignature Number of beats in each bar.
 * @param beatsPerMinute The overall tempo of the song.
*/
void setupTempo(Tempo *tempo, int totalBars, int sampleRate, float timeSignature, int beatsPerMinute);

#endif // DURATION_H