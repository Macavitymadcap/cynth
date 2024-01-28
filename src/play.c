#include "play.h"
#include "notes.h"
#include "waveforms.h"
#include "duration.h"

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

void writeNoteToBuffer(float freq, float noteValue, int measure, float beat, Tempo *tempo, short int *buffer)
{
  float duration = noteValue * tempo->timeSignature;
  float current_beat = tempo->timeSignature * measure + beat;
  int start_index = current_beat * tempo->samplesPerBeat;
  int end_index = start_index + duration * tempo->samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (short int)(getSineWave(freq, i, tempo->sampleRate, 3000) * amplitudeMultiplier);
  }
}

void DM(float noteValue, int measure, float beat, Tempo *tempo, short int *buffer)
{
  writeNoteToBuffer(D4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(Gb4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(A4, noteValue, measure, beat, tempo, buffer);
}

void AM1st(float noteValue, int measure, float beat, Tempo *tempo, short int *buffer)
{
  writeNoteToBuffer(Db4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(E4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(A4, noteValue, measure, beat, tempo, buffer);
}

void Bm1st(float noteValue, int measure, float beat, Tempo *tempo, short int *buffer)
{
  writeNoteToBuffer(D4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(Gb4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(B4, noteValue, measure, beat, tempo, buffer);
}

void GM2nd(float noteValue, int measure, float beat, Tempo *tempo, short int *buffer)
{
  writeNoteToBuffer(D4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(G4, noteValue, measure, beat, tempo, buffer);
  writeNoteToBuffer(B4, noteValue, measure, beat, tempo, buffer);
}
