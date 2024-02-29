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
#include "choices.h"

const int STANDARD_SAMPLE_RATE = 16000;

size_t calculateBufferSize(Song *song)
{
  return song->totalMeasures * song->timeSignature * song->samplesPerBeat;
}

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

void writeChromaticScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 12, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }
}

void writeMixoBluesScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[8], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[9], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[8], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scaleArray[7], measureIndex, 3, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 6, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeDiminishedScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 8, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }
}

void writeStandardLengthScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 6, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeMelodicMinorScaleToBuffer(float tonic, Song *song, int16_t *buffer)
{
  Scale *ascendingScale = createScale(STANDARD_LENGTH, ASCENDING_MELODIC_MINOR_INTERVALS);
  Note *ascendingArray = createScaleArray(tonic, ascendingScale);
  Scale *descendingScale = createScale(STANDARD_LENGTH, DESCENDING_MELODIC_MINOR_INTERVALS);
  Note * descendingArray = createScaleArray(tonic, descendingScale);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, ascendingArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, ASCENDING, ascendingArray, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 1, ASCENDING, descendingArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&descendingArray[5], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&descendingArray[6], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&descendingArray[7], measureIndex, 2, song, buffer);
    measureIndex++;
  }

  free(ascendingScale);
  free(ascendingArray);
  free(descendingScale);
  free(descendingArray);
}

void writeBluesLengthScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[6], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scaleArray[5], measureIndex, 3, song, buffer);
    measureIndex++;

    writeBarOfScaleToBuffer(measureIndex, 4, DESCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[0], measureIndex, 0, song, buffer);
    measureIndex++;
  }
}

void writePentatonicScaleToBuffer(Note *scaleArray, Song *song, int16_t *buffer)
{
  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeBarOfScaleToBuffer(measureIndex, 0, ASCENDING, scaleArray, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[4], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[5], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[4], measureIndex, 2, song, buffer);
    writeNoteToBuffer(&scaleArray[3], measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(&scaleArray[2], measureIndex, 0, song, buffer);
    writeNoteToBuffer(&scaleArray[1], measureIndex, 1, song, buffer);
    writeNoteToBuffer(&scaleArray[0], measureIndex, 2, song, buffer);
    measureIndex++;
  }
}

void writeScaleToBuffer(const char *scaleName, float tonic, Song *song, int16_t *buffer)
{
  Note *scaleArray = getScaleArray(scaleName, tonic);

  if (isChromaticName(scaleName))
  {
    writeChromaticScaleToBuffer(scaleArray, song, buffer);
  }
  else if (isMixoBluesName(scaleName))
  {
    writeMixoBluesScaleToBuffer(scaleArray, song, buffer);
  }
  else if (isDiminishedLengthScale(scaleName))
  {
    writeDiminishedScaleToBuffer(scaleArray, song, buffer);
  }
  else if (isMelodicMinorName(scaleName))
  {
    writeMelodicMinorScaleToBuffer(tonic, song, buffer);
  }
  else if (isStandardLengthScale(scaleName))
  {
    writeStandardLengthScaleToBuffer(scaleArray, song, buffer);
  }
  else if (isBluesLengthScale(scaleName))
  {
    writeBluesLengthScaleToBuffer(scaleArray, song, buffer);
  }
  else if (isPentatonicLengthScale(scaleName))
  {
    writePentatonicScaleToBuffer(scaleArray, song, buffer);
  }

  free(scaleArray);
}

void writeRandomBarOfScaleToBuffer(Scale *scale, float tonic, int measureIndex, Song *song, int16_t *buffer)
{
  float barCompletion = 0.0;
  while (barCompletion < 1.0)
  {
    float value = getRandomNoteValue(barCompletion);
    float frequency = getFrequencyFromTonicAndInterval(tonic, scale->intervals[getRandomInt(scale->length)]);
    Note *note =createNote(frequency, value);
    writeNoteToBuffer(note, measureIndex, barCompletion, song, buffer);
    barCompletion += note->value * 2;
    free(note);
  } 
}
