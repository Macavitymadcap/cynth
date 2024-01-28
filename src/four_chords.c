#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "wav.h"
#include "notes.h"
#include "play.h"
#include "waveforms.h"
#include "validation.h"

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
  setupHeader(wavHeader, STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate);

  int measure = 0;
  while (measure < measuresToPlay)
  {

    writeNoteToBuffer(D2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    writeNoteToBuffer(D3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    DM(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    writeNoteToBuffer(A3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    writeNoteToBuffer(A2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    AM1st(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    writeNoteToBuffer(B2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    writeNoteToBuffer(B3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 1, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 2, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    Bm1st(1, measure, 3, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);

    measure++;

    writeNoteToBuffer(G2, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
    writeNoteToBuffer(G3, 4, measure, 0, beatsPerMeasure, samplesPerBeat, sampleRate, buffer);
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
