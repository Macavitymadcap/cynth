#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "wav.h"
#include "notes.h"
#include "waveforms.h"
#include "validation.h"
#include "audio_buffer.h"
#include "song.h"

int main(int argc, char *argv[])
{
    checkGetWaveUsage(argc, argv[0]);

    const char *waveformName = argv[1];
    checkWaveformName(waveformName);

    const char *noteName = argv[2];
    checkNoteName(noteName);

    const float note = getFrequencyFromName(noteName);

    const int seconds = atoi(argv[3]);
    checkSeconds(seconds);

    int volume = atoi(argv[4]);
    checkVolume(volume);
    int outputVolume = getVolume(volume);

    char fileName[20];
    snprintf(fileName, sizeof(fileName), "%s-%s.wav", noteName, waveformName);

    const int sampleRate = 8000;

    size_t bufferSize = sampleRate * (seconds * 2);
    int16_t *buffer = createBuffer(bufferSize);

    WavHeader *header = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

    FILE *output = fopen(fileName, "wb");
    checkFileOpening(output, fileName);

    for (int i = 0; i < (int)bufferSize; i++)
    {
        buffer[i] = getWaveform(waveformName, note, i, sampleRate, outputVolume);
    }

    fwrite(header, WAVE_HEADER_SIZE, 1, output);
    fwrite(buffer, bufferSize, 1, output);

    fclose(output);
    free(buffer);
    free(header);

    return 0;
}
