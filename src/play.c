#include <stdlib.h>

#include "play.h"
#include "notes.h"
#include "waveforms.h"
#include "duration.h"
#include "song.h"

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

void writeNoteToBuffer(Note *note, int measure, float beat, Song *tempo, short int *buffer)
{
  float duration = note->value * tempo->timeSignature;
  float current_beat = tempo->timeSignature * measure + beat;
  int start_index = current_beat * tempo->samplesPerBeat;
  int end_index = start_index + duration * tempo->samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (short int)(getSineWave(note->frequency, i, tempo->sampleRate, tempo->volume) * amplitudeMultiplier);
  }
}

void DM(float noteValue, int measure, float beat, Song *tempo, short int *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *gb = createNote(Gb4, noteValue);
  Note *a = createNote(A4, noteValue);

  writeNoteToBuffer(d, measure, beat, tempo, buffer);
  writeNoteToBuffer(gb, measure, beat, tempo, buffer);
  writeNoteToBuffer(a, measure, beat, tempo, buffer);

  free(d);
  free(gb);
  free(a);
}

void AM1st(float noteValue, int measure, float beat, Song *tempo, short int *buffer)
{
  Note *db = createNote(Db4, noteValue);
  Note *e = createNote(E4, noteValue);
  Note *a = createNote(A4, noteValue);

  writeNoteToBuffer(db, measure, beat, tempo, buffer);
  writeNoteToBuffer(e, measure, beat, tempo, buffer);
  writeNoteToBuffer(a, measure, beat, tempo, buffer);

  free(db);
  free(e);
  free(a);
}

void Bm1st(float noteValue, int measure, float beat, Song *tempo, short int *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *gb = createNote(Gb4, noteValue);
  Note *b = createNote(B4, noteValue);

  writeNoteToBuffer(d, measure, beat, tempo, buffer);
  writeNoteToBuffer(gb, measure, beat, tempo, buffer);
  writeNoteToBuffer(b, measure, beat, tempo, buffer);

  free(d);
  free(gb);
  free(b);
}

void GM2nd(float noteValue, int measure, float beat, Song *tempo, short int *buffer)
{
  Note *d = createNote(D4, noteValue);
  Note *g = createNote(G4, noteValue);
  Note *b = createNote(B4, noteValue);

  writeNoteToBuffer(d, measure, beat, tempo, buffer);
  writeNoteToBuffer(g, measure, beat, tempo, buffer);
  writeNoteToBuffer(b, measure, beat, tempo, buffer);

  free(d);
  free(g);
  free(b);
}
