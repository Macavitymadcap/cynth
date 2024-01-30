/**
 * @file audio_buffer.h
 * @brief Functions for creating and writing data to audio buffers.
*/

#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include "stdint.h"
#include "song.h"

/**
 * @brief Create a buffer for writing audio, exiting the program if allocation fails.
 * @param size Size of the buffer to be created.
 * @returns Pointer to the created buffer.
*/
int16_t *createBuffer(int size);

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
 * @param waveformName String of waveform to write.
 * @param note Pointer to a Note struct.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeNoteToBuffer(const char *waveformName, Note *note, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Write a D major chord to the buffer based on arguments.
 * @param waveformName String of waveform to write.
 * @param noteValue Length in beats of note.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void DM(const char *waveformName, float noteValue, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Write an A major 1st inversion chord to the buffer based on arguments.
 * @param waveformName String of waveform to write.
 * @param noteValue Length in beats of note.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void AM1st(const char *waveformName, float noteValue, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);


/**
 * @brief Write a B minor 1st inversion to the buffer based on arguments.
 * @param waveformName String of waveform to write.
 * @param noteValue Length in beats of note.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void Bm1st(const char *waveformName, float noteValue, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Write a G major 2nd inversion to the buffer based on arguments.
 * @param waveformName String of waveform to write.
 * @param noteValue Length in beats of note.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void GM2nd(const char *waveformName, float noteValue, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Writes a whole tone scale to an audio buffer, excluding the melodic minor.
 * @param waveformName String of waveform to write.
 * @param scale Array of Note structs comprings the notes of the scale.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeWholeToneScaleToBuffer(const char *waveformName, Note *scale, Song *song, int16_t *buffer);

/**
 * @brief Writes a whole tone scale to an audio buffer, excluding the melodic minor.
 * @param waveformName String of waveform to write.
 * @param Tonic Float representing the root note of the melodic minor scale.
 * @param song Pointer to structure containg the song's time information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeMelodicMinorScaleToBuffer(const char *waveformName, float tonic, Song *song, int16_t *buffer);

#endif