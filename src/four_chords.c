#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav.h"
#include "audio_buffer.h"
#include "waveforms.h"
#include "duration.h"
#include "validation.h"
#include "audio_buffer.h"
#include "song.h"
#include "chords.h"

int main(int argc, char *argv[])
{
  checkFourChordsUsage(argc, argv[0]);

  const char *keyName = argv[1];
  checkKeyName(keyName);

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

  Chord *chords = getFourChords(keyName);

  writeFourChordsToBuffer(chords, song, buffer);

  char fileName[40];
  snprintf(fileName, sizeof(fileName), "%s-%s-four-chords.wav", waveformName, keyName);
  FILE *outfile = fopen(fileName, "wb");
  checkFileOpening(outfile, fileName);
  fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
  fwrite(buffer, bufferSize, 1, outfile);

  fclose(outfile);
  free(song);
  free(wavHeader);
  free(buffer);

  for (int i = 0; i < 8; i++)
  {
    free(chords[i].notes);
  } 
  free(chords);

  exit(EXIT_SUCCESS);
}
