#include "play.h"
#include "notes.h"
#include "waveforms.h"

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

void writeNoteToBuffer(float freq, float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  float current_beat = beatsPerMeasure * measure + beat;
  int start_index = current_beat * samplesPerBeat;
  int end_index = start_index + duration * samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (short int)(getSineWave(freq, i, sampleRate, 3000) * amplitudeMultiplier);
  }
}

void DM(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  writeNoteToBuffer(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(Gb4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(A4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

void AM1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  writeNoteToBuffer(Db4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(E4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(A4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

void Bm1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  writeNoteToBuffer(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(Gb4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(B4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

void GM2nd(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  writeNoteToBuffer(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(G4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  writeNoteToBuffer(B4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}
