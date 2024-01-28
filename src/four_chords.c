#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "wav.h"
#include "notes.h"
#include "play.h"
#include "waveforms.h"
#include "validation.h"
#include "duration.h"

int main(void)
{
  const int sampleRate = 16000;

  Tempo *tempo = malloc(sizeof(Tempo));
  memset(tempo, 0, sizeof(Tempo));
  setupTempo(tempo, 16, sampleRate, FOUR_FOUR, 120);

  const int bufferSize = tempo->totalBars * tempo->timeSignature * tempo->samplesPerBeat;
  short int *buffer = malloc(bufferSize * sizeof(short int));
  checkBufferAllocation(buffer);
  memset(buffer, 0, bufferSize * sizeof(short int));

  size_t headerSize = sizeof(WavHeader); 
  WavHeader *wavHeader = malloc(headerSize);
  checkWavHeaderAllocation(wavHeader);
  memset(wavHeader, 0, headerSize);
  setupHeader(wavHeader, STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate);

  int measure = 0;
  while (measure < tempo->totalBars)
  {

    writeNoteToBuffer(D2, SEMIBREVE, measure, 0, tempo, buffer);
    writeNoteToBuffer(D3, SEMIBREVE, measure, 0, tempo, buffer);
    DM(CROTCHET, measure, 0, tempo, buffer);
    DM(CROTCHET, measure, 1, tempo, buffer);
    DM(CROTCHET, measure, 2, tempo, buffer);
    DM(CROTCHET, measure, 3, tempo, buffer);

    measure++;

    writeNoteToBuffer(A3, SEMIBREVE, measure, 0, tempo, buffer);
    writeNoteToBuffer(A2, SEMIBREVE, measure, 0, tempo, buffer);
    AM1st(CROTCHET, measure, 0, tempo, buffer);
    AM1st(CROTCHET, measure, 1, tempo, buffer);
    AM1st(CROTCHET, measure, 2, tempo, buffer);
    AM1st(CROTCHET, measure, 3, tempo, buffer);

    measure++;

    writeNoteToBuffer(B2, SEMIBREVE, measure, 0, tempo, buffer);
    writeNoteToBuffer(B3, SEMIBREVE, measure, 0, tempo, buffer);
    Bm1st(CROTCHET, measure, 0, tempo, buffer);
    Bm1st(CROTCHET, measure, 1, tempo, buffer);
    Bm1st(CROTCHET, measure, 2, tempo, buffer);
    Bm1st(CROTCHET, measure, 3, tempo, buffer);

    measure++;

    writeNoteToBuffer(G2, SEMIBREVE, measure, 0, tempo, buffer);
    writeNoteToBuffer(G3, SEMIBREVE, measure, 0, tempo, buffer);
    GM2nd(CROTCHET, measure, 0, tempo, buffer);
    GM2nd(CROTCHET, measure, 1, tempo, buffer);
    GM2nd(CROTCHET, measure, 2, tempo, buffer);
    GM2nd(CROTCHET, measure, 3, tempo, buffer);

    measure++;
  }

  setDataAndFileLength(wavHeader, bufferSize, headerSize);

  FILE *fp = fopen("four_chords.wav", "wb");
  fwrite(wavHeader, headerSize, 1, fp);
  fwrite(buffer, bufferSize, 1, fp);

  fclose(fp);
  free(wavHeader);
  free(buffer);
  free(tempo);
}
