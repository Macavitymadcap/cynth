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

  Song *song = createSong(16, sampleRate, FOUR_FOUR, bpm, volume, waveformName);

  size_t bufferSize = song->totalMeasures * song->timeSignature * song->samplesPerBeat;
  int16_t *buffer = createBuffer(bufferSize);

  WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

  const int BASS_SIZE = 2;
  const int CHORD_SIZE = 3;

  Note *dBass[BASS_SIZE] = {createNote(D2, SEMIBREVE), createNote(D3, SEMIBREVE)};
  Note *dMajor[CHORD_SIZE] = {createNote(D4, CROTCHET), createNote(Gb4, CROTCHET), createNote(A4, CROTCHET)};

  Note *aBass[BASS_SIZE] = {createNote(A2, SEMIBREVE), createNote(A3, SEMIBREVE)};
  Note *aMajor1st[CHORD_SIZE] = {createNote(Db4, CROTCHET), createNote(E4, CROTCHET), createNote(A4, CROTCHET)};

  Note *bBass[BASS_SIZE] = {createNote(B2, SEMIBREVE), createNote(B3, SEMIBREVE)};
  Note *bMinor1st[CHORD_SIZE] = {createNote(D4, CROTCHET), createNote(Gb4, CROTCHET), createNote(B4, CROTCHET)};

  Note *gBass[BASS_SIZE] = {createNote(G2, SEMIBREVE), createNote(G3, SEMIBREVE)};
  Note *gMajor2nd[CHORD_SIZE] = {createNote(D4, CROTCHET), createNote(G4, CROTCHET), createNote(B4, CROTCHET)};
  
  const int FIRST_BEAT = 0;

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeChordToBuffer(BASS_SIZE, dBass, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(CHORD_SIZE, dMajor, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(BASS_SIZE, aBass, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(CHORD_SIZE, aMajor1st, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(BASS_SIZE, bBass, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(CHORD_SIZE, bMinor1st, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(BASS_SIZE, gBass, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(CHORD_SIZE, gMajor2nd, measureIndex, i, song, buffer);
    }
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

  for (int i = 0; i < BASS_SIZE; i++)
  {
    free(dBass[i]);
    free(aBass[i]);
    free(bBass[i]);
    free(gBass[i]);
  }

  for (int i = 0; i < CHORD_SIZE; i++)
  {
    free(dMajor[i]);
    free(aMajor1st[i]);
    free(bMinor1st[i]);
    free(gMajor2nd[i]);
  }

  exit(EXIT_SUCCESS);
}
