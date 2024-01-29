#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav.h"
#include "notes.h"
#include "audio_buffer.h"
#include "waveforms.h"
#include "validation.h"
#include "duration.h"
#include "audio_buffer.h"
#include "song.h"

int main(int argc, char *argv[])
{
  checkFourChordsUsage(argc, argv[0]);

  const char *fileName = argv[1];
  checkFileName(fileName);

  const char *waveformName = argv[2];
  checkWaveformName(waveformName);

  int bpm = atoi(argv[3]);
  checkBpm(bpm);

  int volume = atoi(argv[4]);
  checkVolume(volume);

  const int sampleRate = 16000;

  Song *song = createSong(16, sampleRate, FOUR_FOUR, bpm, volume * 500);

  size_t bufferSize = song->totalMeasures * song->timeSignature * song->samplesPerBeat;
  int16_t *buffer = createBuffer(bufferSize);

  WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

  Note *dLowBass = createNote(D2, SEMIBREVE);
  Note *dHighBass = createNote(D3, SEMIBREVE);
  Note *aBassLow = createNote(A2, SEMIBREVE);
  Note *aBassHigh = createNote(A3, SEMIBREVE);
  Note *bBassLow = createNote(B2, SEMIBREVE);
  Note *bBassHigh = createNote(B3, SEMIBREVE);
  Note *gBassLow = createNote(G2, SEMIBREVE);
  Note *gBassHigh = createNote(G3, SEMIBREVE);

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {

    writeNoteToBuffer(waveformName, dLowBass, measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, dHighBass, measureIndex, 0, song, buffer);
    DM(waveformName, CROTCHET, measureIndex, 0, song, buffer);
    DM(waveformName, CROTCHET, measureIndex, 1, song, buffer);
    DM(waveformName, CROTCHET, measureIndex, 2, song, buffer);
    DM(waveformName, CROTCHET, measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, aBassLow, measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, aBassHigh, measureIndex, 0, song, buffer);
    AM1st(waveformName, CROTCHET, measureIndex, 0, song, buffer);
    AM1st(waveformName, CROTCHET, measureIndex, 1, song, buffer);
    AM1st(waveformName, CROTCHET, measureIndex, 2, song, buffer);
    AM1st(waveformName, CROTCHET, measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, bBassLow, measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, bBassHigh, measureIndex, 0, song, buffer);
    Bm1st(waveformName, CROTCHET, measureIndex, 0, song, buffer);
    Bm1st(waveformName, CROTCHET, measureIndex, 1, song, buffer);
    Bm1st(waveformName, CROTCHET, measureIndex, 2, song, buffer);
    Bm1st(waveformName, CROTCHET, measureIndex, 3, song, buffer);
    measureIndex++;

    writeNoteToBuffer(waveformName, gBassLow, measureIndex, 0, song, buffer);
    writeNoteToBuffer(waveformName, bBassHigh, measureIndex, 0, song, buffer);
    GM2nd(waveformName, CROTCHET, measureIndex, 0, song, buffer);
    GM2nd(waveformName, CROTCHET, measureIndex, 1, song, buffer);
    GM2nd(waveformName, CROTCHET, measureIndex, 2, song, buffer);
    GM2nd(waveformName, CROTCHET, measureIndex, 3, song, buffer);
    measureIndex++;
  }

  FILE *outfile = fopen(fileName, "wb");
  checkFileOpening(outfile, fileName);
  fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
  fwrite(buffer, bufferSize, 1, outfile);

  fclose(outfile);
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
