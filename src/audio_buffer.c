#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "notes.h"
#include "waveforms.h"
#include "duration.h"
#include "song.h"
#include "audio_buffer.h"
#include "scales.h"
#include "validation.h"

int16_t *createBuffer(int size)
{
  size_t dataSize = sizeof(int16_t);

  int16_t *buffer = malloc(size * dataSize);
  if (buffer == NULL)
  {
    fprintf(stderr, "Error allocating audio buffer\n");
    exit(EXIT_FAILURE);
  }

  memset(buffer, 0, size * dataSize);

  return buffer;
}

float getAmplitudeMultiplier(int bufferIndex, int beatStartIndex, int beatEndIndex)
{
  float percentThroughNote = ((float)bufferIndex - beatStartIndex) / (beatEndIndex - beatStartIndex);
  float amplitudeMultiplier = 1.0f;
  float quarter = 0.25;
  float half = 0.5;

  if (percentThroughNote < quarter)
  {
    amplitudeMultiplier = (percentThroughNote / quarter);
  }
  else if (percentThroughNote < half)
  {
    amplitudeMultiplier = (1 - ((percentThroughNote - quarter) / quarter)) * 0.8 + 0.2;
  }
  else
  {
    amplitudeMultiplier = 1 - percentThroughNote;
  }

  return amplitudeMultiplier;
}

void writeNoteToBuffer(Note *note, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  float duration = note->value * song->timeSignature;
  float current_beat = song->timeSignature * measureIndex + beatIndex;
  int start_index = current_beat * song->samplesPerBeat;
  int end_index = start_index + duration * song->samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (int16_t)(getWaveform(song->waveformName, note->frequency, i, song->sampleRate, song->volume) * amplitudeMultiplier);
  }
}

void writeChordToBuffer(int chordSize, Note *chord[chordSize], int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  for (int i = 0; i < chordSize; i++)
  {
    writeNoteToBuffer(chord[i], measureIndex, beatIndex, song, buffer);
  }
}

void writeChromaticScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Note *chromaticScale = createScaleArray(tonic, CHROMATIC_INTERVALS, CHROMATIC_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&chromaticScale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[9], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[10], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[11], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[12], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[11], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[10], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[9], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[7], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&chromaticScale[3], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&chromaticScale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&chromaticScale[1], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&chromaticScale[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }

  free(chromaticScale);
}

void writeMixoBluesScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Note *mixoBluesScale = createScaleArray(tonic, MIXO_BLUES_INTERVALS, MIXO_BLUES_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&mixoBluesScale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&mixoBluesScale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&mixoBluesScale[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[9], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[8], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&mixoBluesScale[6], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[4], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&mixoBluesScale[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }

  free(mixoBluesScale);
}

void writeDiminishedScaleToBuffer(Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[7], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }
}

void writeStandardLengthScaleToBuffer(Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[7], measureIndex, 3, song, buffer);
    measureIndex++;
    writeNoteToBuffer(&scale[6], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[4], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeMelodicMinorScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Note *ascending = createScaleArray(tonic, ASCENDING_MELODIC_MINOR_INTERVALS, STANDARD_LENGTH);
  Note *descending = createScaleArray(tonic, DESCENDING_MELODIC_MINOR_INTERVALS, STANDARD_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&ascending[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&ascending[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&ascending[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&ascending[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&ascending[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&ascending[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&ascending[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&ascending[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&descending[1], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&descending[2], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&descending[3], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&descending[4], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&descending[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&descending[6], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&descending[7], measureIndex, 2, song, buffer);
    measureIndex++;
  }

  free(ascending);
  free(descending);
}

void writeBluesLengthScaleToBuffer(Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }
}

void writePentatonicScaleToBuffer(Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(&scale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[4], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeScaleToBuffer(const char *scaleName, float tonic, Song *song, int16_t *buffer)
{
  if (isChromaticName(scaleName))
  {
    writeChromaticScaleToBuffer(tonic, song, buffer);
  }
  else if (isMixoBluesName(scaleName))
  {
    writeMixoBluesScaleToBuffer(tonic, song, buffer);
  }
  else if (isDiminishedLengthScale(scaleName))
  {
    Note *diminishedScale = getScaleArray(scaleName, tonic);
    writeDiminishedScaleToBuffer(diminishedScale, song, buffer);
    free(diminishedScale);
  }
  else if (isMelodicMinorName(scaleName))
  {
    writeMelodicMinorScaleToBuffer(tonic, song, buffer);
  }
  else if (isStandardLengthScale(scaleName))
  {
    Note *standardLengthScale = getScaleArray(scaleName, tonic);
    writeStandardLengthScaleToBuffer(standardLengthScale, song, buffer);
    free(standardLengthScale);
  }
  else if (isBluesLengthScale(scaleName))
  {
    Note *bluesLengthScale = getScaleArray(scaleName, tonic);
    writeBluesLengthScaleToBuffer(bluesLengthScale, song, buffer);
    free(bluesLengthScale);
  }
  else if (isPentatonicLengthScale(scaleName))
  {
    Note *pentatonicScale = getScaleArray(scaleName, tonic);
    writePentatonicScaleToBuffer(pentatonicScale, song, buffer);
    free(pentatonicScale);
  }
}