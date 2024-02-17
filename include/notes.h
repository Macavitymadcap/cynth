/**
 * @file notes.h
 * @brief Functions and constants pertaining to musical notes.
 * @see https://pages.mtu.edu/~suits/notefreqs.html
 */

#ifndef NOTES_H
#define NOTES_H

#include <stdlib.h>

/**
 * @brief The number of semitones in a western scale, not including the octave.
*/
extern const int TOTAL_SEMITONES;

/**
 * @brief Array of strings representing the names of notes.
 */
extern const char *NOTE_NAMES[];

extern const float C0;
extern const float Db0;
extern const float D0;
extern const float Eb0;
extern const float E0;
extern const float F0;
extern const float Gb0;
extern const float G0;
extern const float Ab0;
extern const float A0;
extern const float Bb0;
extern const float B0;
extern const float C1;
extern const float Db1;
extern const float D1;
extern const float Eb1;
extern const float E1;
extern const float F1;
extern const float Gb1;
extern const float G1;
extern const float Ab1;
extern const float A1;
extern const float Bb1;
extern const float B1;
extern const float C2;
extern const float Db2;
extern const float D2;
extern const float Eb2;
extern const float E2;
extern const float F2;
extern const float Gb2;
extern const float G2;
extern const float Ab2;
extern const float A2;
extern const float Bb2;
extern const float B2;
extern const float C3;
extern const float Db3;
extern const float D3;
extern const float Eb3;
extern const float E3;
extern const float F3;
extern const float Gb3;
extern const float G3;
extern const float Ab3;
extern const float A3;
extern const float Bb3;
extern const float B3;
extern const float C4;
extern const float Db4;
extern const float D4;
extern const float Eb4;
extern const float E4;
extern const float F4;
extern const float Gb4;
extern const float G4;
extern const float Ab4;
extern const float A4;
extern const float Bb4;
extern const float B4;
extern const float C5;
extern const float Db5;
extern const float D5;
extern const float Eb5;
extern const float E5;
extern const float F5;
extern const float Gb5;
extern const float G5;
extern const float Ab5;
extern const float A5;
extern const float Bb5;
extern const float B5;
extern const float C6;
extern const float Db6;
extern const float D6;
extern const float Eb6;
extern const float E6;
extern const float F6;
extern const float Gb6;
extern const float G6;
extern const float Ab6;
extern const float A6;
extern const float Bb6;
extern const float B6;
extern const float C7;
extern const float Db7;
extern const float D7;
extern const float Eb7;
extern const float E7;
extern const float F7;
extern const float Gb7;
extern const float G7;
extern const float Ab7;
extern const float A7;
extern const float Bb7;
extern const float B7;
extern const float C8;
extern const float Db8;
extern const float D8;
extern const float Eb8;
extern const float E8;
extern const float F8;
extern const float Gb8;
extern const float G8;
extern const float Ab8;
extern const float A8;
extern const float Bb8;
extern const float B8;

/**
 * @brief Return the note corresponding with the passed string.
 * @param noteName A string representation of the note.
 * @returns The float that corresponds with the noteName.
 */
float getFrequencyFromName(const char *noteName);

/**
 * @brief Calculate a note's frequency based on a root note and scale interval.
 *
 *  The frequency  is calculated using the formula:
 * `frequency = tonic * 2^(semitone / 12)`.
 *
 * @param tonic The root frequency of the desired note's key.
 * @param interval The number of semitones between the root and desired note.
 * @returns The float corresponding to the desired note
 */
float getFrequencyFromTonicAndInterval(float tonic, int interval);

/**
 * @struct Note
 * @brief Encapsulates information about an individual note
 */
typedef struct
{
    float frequency; /** The pitch of the note. */
    float value;     /** The duration in beats of the note. */
} __attribute__((__packed__)) Note;

/**
 * @brief The szie of a Note struct.
 */
extern const size_t NOTE_SIZE;

/**
 * @brief Create a new note, exiting the program if memory cannot be allocated.
 * @param frequency The pitch of the note.
 * @param value The duration in beats of the note.
 * @returns note Pointer to a Note struct.
 */
Note *createNote(float frequency, float value);

#endif
