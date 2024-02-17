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
#include "chords.h"

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

void writeChordToBuffer(Chord *chord, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  for (int i = 0; i < chord->length; i++)
  {
    writeNoteToBuffer(&chord->notes[i], measureIndex, beatIndex, song, buffer);
  }
}

void writeFourChordsToBuffer(Chord *chords, Song *song, int16_t *buffer)
{
  const int FIRST_BEAT = 0;
  int measureIndex = 0;
  
  while (measureIndex < song->totalMeasures)
  {
    writeChordToBuffer(&chords[0], measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(&chords[1], measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(&chords[2], measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(&chords[3], measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(&chords[4], measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(&chords[5], measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(&chords[6], measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(&chords[7], measureIndex, i, song, buffer);
    }
    measureIndex++;
  }
}

void writeBarOfScaleToBuffer(int measureIndex, int scaleIndex, ScaleDirection direction, Note *scale, Song *song, int16_t *buffer)
{
  for (int beatIndex = 0; beatIndex < (int)FOUR_FOUR; beatIndex++, direction == ASCENDING ? scaleIndex++ : scaleIndex--)
  {
    writeNoteToBuffer(&scale[scaleIndex], measureIndex, beatIndex, song, buffer);
  }
}

void writeChromaticScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Note *chromaticScale = createScaleArray(tonic, CHROMATIC_INTERVALS, CHROMATIC_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, chromaticScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, chromaticScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, ASCENDING, chromaticScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 12, DESCENDING, chromaticScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, DESCENDING, chromaticScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, chromaticScale, song, buffer);
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
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, mixoBluesScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, mixoBluesScale, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&mixoBluesScale[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[9], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[8], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&mixoBluesScale[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 6, DESCENDING, mixoBluesScale, song, buffer);
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
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, DESCENDING, scale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, scale, song, buffer);
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
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 6, DESCENDING, scale, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeMelodicMinorScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Note *ascendingScale = createScaleArray(tonic, ASCENDING_MELODIC_MINOR_INTERVALS, STANDARD_LENGTH);
  Note *descendingScale = createScaleArray(tonic, DESCENDING_MELODIC_MINOR_INTERVALS, STANDARD_LENGTH);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, ascendingScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, ascendingScale, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 1, ASCENDING, descendingScale, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&descendingScale[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&descendingScale[6], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&descendingScale[7], measureIndex, 2, song, buffer);
    measureIndex++;
  }

  free(ascendingScale);
  free(descendingScale);
}

void writeBluesLengthScaleToBuffer(Note *scale, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scale, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scale[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scale[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scale[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, scale, song, buffer);
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
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scale, song, buffer);
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
