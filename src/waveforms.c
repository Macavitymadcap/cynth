#include "waveforms.h"
#include <math.h>

const char *SINE = "sine";
const char *SAWTOOTH = "sawtooth";
const char *SQUARE = "square";
const char *TRIANGLE = "triangle";
const char *PULSE = "pulse";

short int getSineWave(float note, int bufferIndex, int sampleRate, int volume)
{
    return (short int)((cos((2 * M_PI * note * bufferIndex) / sampleRate) * volume));
}

short int getSawtoothWave(float note, int bufferIndex, int sampleRate, int volume)
{
    float phase = fmod((2 * M_PI * note * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);
    return (short int)(((2 * phase - 1) * volume) );
}

short int getSquareWave(float note, int bufferIndex, int sampleRate, int volume)
{
    return (short int)(((sin((2 * M_PI * note * bufferIndex) / sampleRate) > 0) ? volume : -volume) );
}

short int getTriangleWave(float note, int bufferIndex, int sampleRate, int volume)
{
    float phase = fmod((2 * M_PI * note * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);
    return (short int)(((2 * fabs(phase - 0.5) - 1) * volume) );
}

short int getPulseWave(float note, int bufferIndex, int sampleRate, int volume, float dutyCycle)
{
    float phase = fmod((2 * M_PI * note * bufferIndex) / sampleRate, 2 * M_PI) / (2 * M_PI);

    return (short int)(((phase < dutyCycle) ? volume : -volume) );
}
