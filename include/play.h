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


/**
 * @brief Write the given note to the buffer based on arguments.
 * @param freq Frequency of the note to be written.
 * @param duration Length in beats of note.
 * @param measure The current measure in which the note is written.
 * @param beat The index of the current beat in the measure.
 * @param beatsPerMeasure Number of beats in the current measure.
 * @param samplesPerBeat Number of sample per beat.
 * @param sampleRate The sample rate to use.
 * @param buffer The buffer into which the note will be written.
*/
void writeNoteToBuffer(float freq, float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer);

/**
 * @brief Write a D major chord to the buffer based on arguments.
 * @param duration Length in beats of note.
 * @param measure The current measure in which the note is written.
 * @param beat The index of the current beat in the measure.
 * @param beatsPerMeasure Number of beats in the current measure.
 * @param samplesPerBeat Number of sample per beat.
 * @param sampleRate The sample rate to use.
 * @param buffer The buffer into which the note will be written.
*/
void DM(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer);

/**
 * @brief Write an A major 1st inversion chord to the buffer based on arguments.
 * @param duration Length in beats of note.
 * @param measure The current measure in which the note is written.
 * @param beat The index of the current beat in the measure.
 * @param beatsPerMeasure Number of beats in the current measure.
 * @param samplesPerBeat Number of sample per beat.
 * @param sampleRate The sample rate to use.
 * @param buffer The buffer into which the note will be written.
*/
void AM1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer);


/**
 * @brief Write a B minor 1st inversion to the buffer based on arguments.
 * @param duration Length in beats of note.
 * @param measure The current measure in which the note is written.
 * @param beat The index of the current beat in the measure.
 * @param beatsPerMeasure Number of beats in the current measure.
 * @param samplesPerBeat Number of sample per beat.
 * @param sampleRate The sample rate to use.
 * @param buffer The buffer into which the note will be written.
*/
void Bm1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer);

/**
 * @brief Write a G major 2nd inversion to the buffer based on arguments.
 * @param duration Length in beats of note.
 * @param measure The current measure in which the note is written.
 * @param beat The index of the current beat in the measure.
 * @param beatsPerMeasure Number of beats in the current measure.
 * @param samplesPerBeat Number of sample per beat.
 * @param sampleRate The sample rate to use.
 * @param buffer The buffer into which the note will be written.
*/
void GM2nd(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer);
#endif // PLAY_H