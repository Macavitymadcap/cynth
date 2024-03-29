/**
 * @file audio_buffer.h
 * @brief Functions for creating and writing data to audio buffers.
*/

#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include "stdint.h"
#include "song.h"
#include "chords.h"
#include "scales.h"

/**
 * @enum ScaleDirection
 * @brief The direction to use when writing a scale to a buffer.
*/
typedef enum ScaleDirection
{
  ASCENDING,    /** Go up the scale. */
  DESCENDING    /** Go down the scale. */
} ScaleDirection;

/**
 * @brief Usual sample rate for programs (16,000).
*/
extern const int STANDARD_SAMPLE_RATE;

/**
 * @brief Get the size of based on song parameters.
 * Calculation is totalMeasures * timeSignature * samplesPerBeat.
 * @returns The size of the buffer
*/
size_t calculateBufferSize(Song *song);

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
 * @param note Pointer to a Note struct.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeNoteToBuffer(Note *note, int meaureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Write a chord to the buffer based on arguments.
 * @param chord Chord struct representing the chord.
 * @param meaureIndex The current measure in which the note is written.
 * @param beatIndex The index of the current beat in the measure.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeChordToBuffer(Chord *chord, int measureIndex, float beatIndex, Song *song, int16_t *buffer);

/**
 * @brief Write the Four Chord progression to the buffer.
 * @param chords Array of chords for the progresion.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeFourChordsToBuffer(Chord *chords, Song *song, int16_t *buffer);

/**
 * @brief Write four notes of a scale to one bar of the buffer.
 * @param measureIndex The bar to which the notes should be written
 * @param scaleIndex The index of the scale at which to start writing.
 * @param direction Whether to go up or go down the scale from the scaleIndex.
 * @param scale Array of Note structs comprising the notes of the scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeBarOfScaleToBuffer(int measureIndex, int scaleIndex, ScaleDirection direction, Note *scale, Song *song, int16_t *buffer);

/**
 * @brief Writes a chromatic scale to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs comprising the notes of the chromatic scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeChromaticScaleToBuffer(Note * scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a mixo-blues scale to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs comprising the notes of the mixo-blues scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeMixoBluesScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a diminished scale to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs comprings the notes of the diminished scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeDiminishedScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a scale of standard length to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs comprising the notes of the scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeStandardLengthScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a whole tone scale to an audio buffer, excluding the melodic minor.
 * @param tonic Float representing the root note of the melodic minor scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeMelodicMinorScaleToBuffer(float tonic, Song *song, int16_t *buffer);

/**
 * @brief Writes a blues length scale to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs of a blues scale length (blues or whole tone).
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeBluesLengthScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a pentatonic scale to an audio buffer, excluding the melodic minor.
 * @param scaleArray Array of Note structs of a comprising a pentatonic scale..
 * @param song Pointer to structure containg the song's perfomance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writePentatonicScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer);

/**
 * @brief Writes a scale to an audio buffer.
 * @param scaleName String representing the name of the scale to be written.
 * @param tonic Float representing the root note of the scale.
 * @param song Pointer to structure containg the song's performance information. 
 * @param buffer The buffer into which the note will be written.
*/
void writeScaleToBuffer(const char *scaleName, float tonic, Song *song, int16_t *buffer);

#endif
