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

  float *tonics = getFourChordTonics(keyName);

  Note *IBass = createChordArray(tonics[0], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
  Note *IChord = createChordArray(tonics[4], CROTCHET, MAJOR_TRIAD_INTERVALS, TRIAD_LENGTH);

  Note *VBass = createChordArray(tonics[1], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH); 
  Note *VChord1st = createChordArray(tonics[5], CROTCHET, MAJOR_TRIAD_1ST_INVERSION_INTERVALS, TRIAD_LENGTH);

  Note *viBass = createChordArray(tonics[2], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
  Note *viChord1st = createChordArray(tonics[6], CROTCHET, MINOR_TRIAD_1ST_INVERSION_INTERVALS, TRIAD_LENGTH);

  Note *IVBass = createChordArray(tonics[3], SEMIBREVE, BASS_PEDAL_INTERVALS, BASS_PEDAL_LENGTH);
  Note *IVChord2nd = createChordArray(tonics[7], CROTCHET, MAJOR_TRIAD_2ND_INVERSION_INTERVALS, TRIAD_LENGTH);
  
  const int FIRST_BEAT = 0;

  int measureIndex = 0;
  while (measureIndex < song->totalMeasures)
  {
    writeChordToBuffer(IBass, BASS_PEDAL_LENGTH, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(IChord, TRIAD_LENGTH, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(VBass, BASS_PEDAL_LENGTH, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(VChord1st, TRIAD_LENGTH, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(viBass, TRIAD_LENGTH, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(viChord1st, TRIAD_LENGTH, measureIndex, i, song, buffer);
    }
    measureIndex++;

    writeChordToBuffer(IVBass, BASS_PEDAL_LENGTH, measureIndex, FIRST_BEAT, song, buffer);
    for (int i = 0; i < (int)song->timeSignature; i++)
    {
      writeChordToBuffer(IVChord2nd, TRIAD_LENGTH, measureIndex, i, song, buffer);
    }
    measureIndex++;
  }

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
  
  free(tonics);

  free(IBass);
  free(VBass);
  free(viBass);
  free(IVBass);

  free(IChord);
  free(VChord1st);
  free(viChord1st);
  free(IVChord2nd);

  exit(EXIT_SUCCESS);
}
