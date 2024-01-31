#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav.h"
#include "notes.h"
#include "waveforms.h"
#include "validation.h"
#include "duration.h"
#include "audio_buffer.h"
#include "song.h"
#include "scales.h"

int main(int argc, const char *argv[])
{
    checkGetScaleUsage(argc, argv[0]);

    const char *waveformName = argv[1];
    checkWaveformName(waveformName);

    const char *noteName = argv[2];
    checkNoteName(noteName);

    const float tonic = getFrequencyFromName(noteName);

    const char *scaleName = argv[3];
    checkScaleName(scaleName);

    int bpm = atoi(argv[4]);
    checkBpm(bpm);

    int volume = atoi(argv[5]);
    checkVolume(volume);

    const int totalMeasures = getTotalMeasuresForScale(scaleName);
    const int sampleRate = 16000;

    Song *song = createSong(totalMeasures, sampleRate, FOUR_FOUR, bpm, volume, waveformName);

    size_t bufferSize = song->totalMeasures * song->timeSignature * song->samplesPerBeat;
    int16_t *buffer = createBuffer(bufferSize);

    WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

    writeScaleToBuffer(scaleName, tonic, song, buffer);
    
    char fileName[40];
    memset(fileName, 0, 40);
    strcat(fileName, waveformName);
    strcat(fileName, "-");
    strcat(fileName, noteName);
    strcat(fileName, "-");
    strcat(fileName, scaleName);
    strcat(fileName, ".wav");

    FILE *outfile = fopen(fileName, "wb");
    checkFileOpening(outfile, fileName);
    fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
    fwrite(buffer, bufferSize, 1, outfile);

    fclose(outfile);
    free(song);
    free(wavHeader);
    free(buffer);

    exit(EXIT_SUCCESS);
}