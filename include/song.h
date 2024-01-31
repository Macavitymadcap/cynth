/**
 * @file song.h
 * @brief Struct and functions for song data;
*/

#ifndef SONG_H
#define SONG_H

/**
 * @struct Song
 * @brief Structure encapsulating time and performance information for a song.
*/
typedef struct
{
    int totalMeasures;          /** Number of measures in the song. */
    int sampleRate;             /** Rate at which notes will be sampled. */
    float timeSignature;        /** Number of beats in each bar. */
    int beatsPerMinute;         /** The overall tempo of the song. */
    int millisecondsPerBeat;    /** Durtion of each beat in milliseconds. */
    int samplesPerBeat;         /** Rate at which each beat is sampled. */
    int volume;                 /** The average volume of notes in the song. */
} __attribute__((__packed__)) Song;

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
 * @brief Convert user input volume to a vlaue usable for buffer writing.
 * @param inputVolume The volume passed by the user (1-11).
 * @returns Calculated volume (inputVolume * 500).
*/
int getVolume(in inputVolume);

/**
 * @brief Create a Song struct, exiting the program if memory allocation fails.
 * @param totalMeasures Number of bars in the song.
 * @param sampleRate Rate at which notes will be sampled.
 * @param timeSignature Number of beats in each bar.
 * @param beatsPerMinute The overall tempo of the song.
 * @param volume The average volume of notes in the song.
 * @returns Pointer to the new Song struct.
*/
Song *createSong(int totalMeasures, int sampleRate, float timeSignature, int beatsPerMinute, int volume);

#endif