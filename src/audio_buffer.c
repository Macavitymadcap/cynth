#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "notes.h"
#include "waveforms.h"
#include "duration.h"
#include "song.h"
#include "audio_buffer.h"

int16_t *createBuffer(int size)
{
    size_t dataSize = sizeof(int16_t);

    int16_t*buffer = malloc(size * dataSize);
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

void DM(const char *waveformName, float noteValue, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *gb = createNote(Gb4, noteValue);
  Note *a = createNote(A4, noteValue);

  writeNoteToBuffer(waveformName, d, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, gb, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, a, measureIndex, beatIndex, song, buffer);

  free(d);
  free(gb);
  free(a);
}

void AM1st(const char*waveformName, float noteValue, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  Note *db = createNote(Db4, noteValue);
  Note *e = createNote(E4, noteValue);
  Note *a = createNote(A4, noteValue);

  writeNoteToBuffer(waveformName, db, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, e, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, a, measureIndex, beatIndex, song, buffer);

  free(db);
  free(e);
  free(a);
}

void Bm1st(const char*waveformName, float noteValue, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *gb = createNote(Gb4, noteValue);
  Note *b = createNote(B4, noteValue);

  writeNoteToBuffer(waveformName, d, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, gb, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, b, measureIndex, beatIndex, song, buffer);

  free(d);
  free(gb);
  free(b);
}

void GM2nd(const char *waveformName, float noteValue, int measureIndex, float beatIndex, Song *song, int16_t *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *g = createNote(G4, noteValue);
  Note *b = createNote(B4, noteValue);

  writeNoteToBuffer(waveformName, d, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, g, measureIndex, beatIndex, song, buffer);
  writeNoteToBuffer(waveformName, b, measureIndex, beatIndex, song, buffer);

  free(d);
  free(g);
  free(b);
}