/**
 * @file play.h
 * @brief Functions and constants for playing notes and chords.
*/

#ifndef PLAY_H
#define PLAY_H

/**
 * @brief Calculate amplitude multiplier based on the position in a musical note.
 *
 * This function computes an amplitude multiplier based on the position within a
 * musical note, represented by the buffer index relative to the beat start and end indices.
 * The amplitude multiplier varies during different phases of the note.
 *
 * @param bufferIndex Index within the audio buffer representing the current position.
 * @param beatStartIndex Index within the audio buffer indicating the start of the musical note.
 * @param beatEndIndex Index within the audio buffer indicating the end of the musical note.
 *
 * @return The calculated amplitude multiplier for the given position in the musical note.
 *
 * @note The amplitude multiplier is determined by the percentage of progress through the note,
 *       and different multipliers are applied during various phases (quarters and halves) of the note.
 *       The resulting amplitude multiplier ranges from 0.2 to 1.0.
 */
float getAmplitudeMultiplier(int bufferIndex, int beatStartIndex, int beatEndIndex);


#endif // PLAY_H