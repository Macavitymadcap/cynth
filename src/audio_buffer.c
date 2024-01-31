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

void writeNoteToBuffer(const char *waveformName, Note *note, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  float duration = note->value * song->timeSignature;
  float current_beat = song->timeSignature * measureIndex + beatIndex;
  int start_index = current_beat * song->samplesPerBeat;
  int end_index = start_index + duration * song->samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (int16_t)(getWaveform(waveformName, note->frequency, i, song->sampleRate, song->volume) * amplitudeMultiplier);
  }
}

void writeChordToBuffer(const char *waveformName, int chordSize, Note *chord[chordSize], int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  for (int i = 0; i < chordSize; i++)
  {
    writeNoteToBuffer(waveformName, chord[i], measureIndex, beatIndex, song, buffer);
  }
}

void writeWholeToneScaleToBuffer(const char *waveformName, Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(waveformName, &scale[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &scale[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &scale[4], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &scale[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &scale[6], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &scale[7], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &scale[6], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &scale[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &scale[4], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &scale[3], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &scale[2], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &scale[1], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &scale[0], measureIndex, 1, song, buffer);
    measureIndex++;
  }
}

void writeMelodicMinorScaleToBuffer(const char *waveformName, float tonic, Song *song, int16_t *buffer)
{
  Note *ascending = createScaleArray(tonic, ASCENDING_MELODIC_MINOR_INTERVALS, WHOLE_TONE_LENGTH);
  Note *descending = createScaleArray(tonic, DESCENDING_MELODIC_MINOR_INTERVALS, WHOLE_TONE_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeNoteToBuffer(waveformName, &ascending[0], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &ascending[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &ascending[2], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &ascending[4], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &ascending[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &ascending[6], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &ascending[7], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &descending[1], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &descending[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &descending[3], measureIndex, 1, song, buffer);
    writeNoteToBuffer(waveformName, &descending[4], measureIndex, 2, song, buffer);
    writeNoteToBuffer(waveformName, &descending[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, &descending[6], measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, &descending[7], measureIndex, 1, song, buffer);
    measureIndex++;
  }

  free(ascending);
  free(descending);
}