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
#include "audio_buffer.h"
#include "song.h"

int main(void)
{
  const int sampleRate = 16000;

  Song *song = createSong(16, sampleRate, FOUR_FOUR, 120, 3000);

  const int bufferSize = song->totalBars * song->timeSignature * song->samplesPerBeat;
  short int *buffer = createBuffer(bufferSize);

  WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate);

  Note *dLowBass = createNote(D2, SEMIBREVE);
  Note *dHighBass = createNote(D3, SEMIBREVE);
  Note *aBassLow = createNote(A2, SEMIBREVE);
  Note *aBassHigh = createNote(A3, SEMIBREVE);
  Note *bBassLow = createNote(B2, SEMIBREVE);
  Note *bBassHigh = createNote(B3, SEMIBREVE);
  Note *gBassLow = createNote(G2, SEMIBREVE);
  Note *gBassHigh = createNote(G3, SEMIBREVE);

  int measure = 0;
  while (measure < song->totalBars)
  {

    writeNoteToBuffer(dLowBass, measure, 0, song, buffer);
    writeNoteToBuffer(dHighBass, measure, 0, song, buffer);
    DM(CROTCHET, measure, 0, song, buffer);
    DM(CROTCHET, measure, 1, song, buffer);
    DM(CROTCHET, measure, 2, song, buffer);
    DM(CROTCHET, measure, 3, song, buffer);

    measure++;

    writeNoteToBuffer(aBassLow, measure, 0, song, buffer);
    writeNoteToBuffer(aBassHigh, measure, 0, song, buffer);
    AM1st(CROTCHET, measure, 0, song, buffer);
    AM1st(CROTCHET, measure, 1, song, buffer);
    AM1st(CROTCHET, measure, 2, song, buffer);
    AM1st(CROTCHET, measure, 3, song, buffer);

    measure++;

    writeNoteToBuffer(bBassLow, measure, 0, song, buffer);
    writeNoteToBuffer(bBassHigh, measure, 0, song, buffer);
    Bm1st(CROTCHET, measure, 0, song, buffer);
    Bm1st(CROTCHET, measure, 1, song, buffer);
    Bm1st(CROTCHET, measure, 2, song, buffer);
    Bm1st(CROTCHET, measure, 3, song, buffer);

    measure++;

    writeNoteToBuffer(gBassLow, measure, 0, song, buffer);
    writeNoteToBuffer(bBassHigh, measure, 0, song, buffer);
    GM2nd(CROTCHET, measure, 0, song, buffer);
    GM2nd(CROTCHET, measure, 1, song, buffer);
    GM2nd(CROTCHET, measure, 2, song, buffer);
    GM2nd(CROTCHET, measure, 3, song, buffer);

    measure++;
  }

  setDataAndFileLength(wavHeader, bufferSize, WAVE_HEADER_SIZE);

  FILE *fp = fopen("four_chords.wav", "wb");
  fwrite(wavHeader, WAVE_HEADER_SIZE, 1, fp);
  fwrite(buffer, bufferSize, 1, fp);

  fclose(fp);
  free(song);
  free(wavHeader);
  free(buffer);
  free(dLowBass);
  free(dHighBass);
  free(aBassLow);
  free(aBassHigh);
  free(bBassLow);
  free(bBassHigh);
  free(gBassLow);
  free(gBassHigh);
  
  exit(EXIT_SUCCESS);
}
