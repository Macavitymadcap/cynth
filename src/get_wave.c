#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "wav.h"
#include "notes.h"
#include "waveforms.h"
#include "validation.h"
#include "audio_buffer.h"

const int sampleRate = 8000;
const int volume = 3000;

int main(int argc, char *argv[])
{
    checkGetWaveUsage(argc, argv[0]);

    const char *fileName = argv[1];
    checkFileName(fileName);

    const char *waveformName = argv[2];
    checkWaveformName(waveformName);

    const char *noteName = argv[3];
    checkNoteName(noteName);

    const float note = getFrequencyFromName(noteName);

    const int seconds = atoi(argv[4]);
    checkSeconds(seconds);
    
    size_t bufferSize = sampleRate * seconds;
    
    WavHeader *header = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate);

    int16_t *buffer = createBuffer(bufferSize);

    setDataAndFileLength(header, bufferSize, WAVE_HEADER_SIZE);

    FILE *output = fopen(fileName, "wb");
    checkFileOpening(output, fileName);

    for (int i = 0; i < (int)bufferSize; i++)
    {
        if (isSine(waveformName))
        {
            buffer[i] = getSineWave(note, i, sampleRate, volume);
        }
        else if (isSquare(waveformName))
        {
            buffer[i] = getSquareWave(note, i, sampleRate, volume);
        }
        else if (isSawtooth(waveformName))
        {
            buffer[i] = getSawtoothWave(note, i, sampleRate, volume);
        }
        else if (isTriangle(waveformName))
        {
            buffer[i] = getTriangleWave(note, i, sampleRate, volume);
        }
        else if (isPulse(waveformName))
        {
            float dutyCycle = (i + 1) % 2 == 0 ? 0.25 : 0.5;
            buffer[i] = getPulseWave(note, i, sampleRate, volume, dutyCycle);
        }
    }

    fwrite(header, WAVE_HEADER_SIZE, 1, output);
    fwrite(buffer, bufferSize, 1, output);

    fclose(output);
    free(buffer);
    free(header);

    return 0;
}
