#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "wav.h"
#include "notes.h"
#include "play.h"
#include "waveforms.h"
#include "validation.h"

void play(float freq, float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  float current_beat = beatsPerMeasure * measure + beat;
  int start_index = current_beat * samplesPerBeat;
  int end_index = start_index + duration * samplesPerBeat;

  for (int i = start_index; i < end_index; i++)
  {
    float amplitudeMultiplier = getAmplitudeMultiplier(i, start_index, end_index);
    buffer[i] += (short int)((cos((2 * M_PI * freq * i) / sampleRate) * 3000) * amplitudeMultiplier);
  }
}

// DMajor
void DM(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  play(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(Gb4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(A4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

// A Major 1st Inversion
void AM1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  play(Db4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(E4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(A4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

// B Minor 1st Inversion
void Bm1st(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  play(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(Gb4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(B4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

// G Major 2nd Inversion
void GM2nd(float duration, int measure, float beat, int beatsPerMeasure, int samplesPerBeat, int sampleRate, short int *buffer)
{
  play(D4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(G4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
  play(B4, duration, measure, beat, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
}

int main(void)
{
  const int measuresToPlay = 4 * 4;
  const int sampleRate = 16000;
  const int beatsPerMeasure = 4;
  const int millisecondsPerBeat = 500;
  const int samplesPerBeat = (sampleRate * millisecondsPerBeat) / 1000;

  const int bufferSize = measuresToPlay * beatsPerMeasure * samplesPerBeat;
  short int *buffer = malloc(bufferSize * sizeof(short int));
  checkBufferAllocation(buffer);
  memset(buffer, 0, bufferSize * sizeof(short int));

  WavHeader *wavHeader = malloc(sizeof(WavHeader));
  checkWavHeaderAllocation(wavHeader);
  memset(wavHeader, 0, sizeof(WavHeader));

  setFormatFields(wavHeader);
  wavHeader->chunkSize = STANDARD_CHUNK_SIZE;
  wavHeader->audioFormat = PCM;
  wavHeader->numChannels = MONO;
  wavHeader->sampleRate = sampleRate;
  wavHeader->bitsPerSample = STANDARD_CHUNK_SIZE;

  int measure = 0;
  while (measure < measuresToPlay)
  {

    play(D2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    play(D3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    play(A3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    play(A2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    play(B2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    play(B3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    play(G2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    play(G3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    GM2nd(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    GM2nd(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    GM2nd(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    GM2nd(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;
  }

  wavHeader->fileLength = bufferSize + 44;
  const int num_bytes = 2;
  wavHeader->dataLength = bufferSize * num_bytes;

  FILE *fp = fopen("four_chords.wav", "wb");
  fwrite(wavHeader, 1, sizeof(WavHeader), fp);
  fwrite(buffer, sizeof(short int), bufferSize, fp);

  fclose(fp);
  free(wavHeader);
  free(buffer);
}
