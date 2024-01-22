#include "play.h"

float getAmplitudeMultiplier(int bufferIndex, int beatStartIndex, int beatEndIndex)
{
    float percentThroughNote = ((float)bufferIndex - beatStartIndex) / (beatEndIndex - beatStartIndex);
    float amplitudeMultiplier = 1.0f;
    float quarter = 0.25;
    float half = 0.5;

    if (percentThroughNote < quarter)
    {
        amplitudeMultiplier = (percentThroughNote / quarter);
    }
    else if (percentThroughNote < half)
    {
        amplitudeMultiplier = (1 - ((percentThroughNote - quarter) / quarter)) * 0.8 + 0.2;
    }
    else
    {
        amplitudeMultiplier = 1 - percentThroughNote;
    }

    return amplitudeMultiplier;
}
