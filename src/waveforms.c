#include <stdint.h>
#include <math.h>

#include "waveforms.h"
#include "validation.h"

const char *SINE = "sine";
const char *SAWTOOTH = "sawtooth";
const char *SQUARE = "square";
const char *TRIANGLE = "triangle";
const char *PULSE = "pulse";

int16_t getSineWave(float frequency, int bufferIndex, int sampleRate, int volume)
{
    return (int16_t)((cos((2 * M_PI * frequency * bufferIndex) / sampleRate) * volume));
}

int16_t getSawtoothWave(float frequency, int bufferIndex, int sampleRate, int volume)
{
    float phase = fmod((2 * M_PI * frequency * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);
    return (int16_t)(((2 * phase - 1) * volume) );
}

int16_t getSquareWave(float frequency, int bufferIndex, int sampleRate, int volume)
{
    return (int16_t)(((sin((2 * M_PI * frequency * bufferIndex) / sampleRate) > 0) ? volume : -volume) );
}

int16_t getTriangleWave(float frequency, int bufferIndex, int sampleRate, int volume)
{
    float phase = fmod((2 * M_PI * frequency * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);
    return (int16_t)(((2 * fabs(phase - 0.5) - 1) * volume) );
}

int16_t getPulseWave(float frequency, int bufferIndex, int sampleRate, int volume, float dutyCycle)
{
    float phase = fmod((2 * M_PI * frequency * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);

    return (int16_t)(((phase < dutyCycle) ? volume : -volume) );
}

int16_t getWaveform(const char* waveformName, float frequency, int bufferIndex, int sampleRate, int volume)
{
    if (isSine(waveformName))
        {
            return getSineWave(frequency, bufferIndex, sampleRate, volume);
        }
        else if (isSquare(waveformName))
        {
            return getSquareWave(frequency, bufferIndex, sampleRate, volume);
        }
        else if (isSawtooth(waveformName))
        {
            return getSawtoothWave(frequency, bufferIndex, sampleRate, volume);
        }
        else if (isTriangle(waveformName))
        {
            return getTriangleWave(frequency, bufferIndex, sampleRate, volume);
        }
        else if (isPulse(waveformName))
        {
            float dutyCycle = (bufferIndex + 1) % 2 == 0 ? 0.25 : 0.5;
            return getPulseWave(frequency, bufferIndex, sampleRate, volume, dutyCycle);
        }

        return 0;
}
