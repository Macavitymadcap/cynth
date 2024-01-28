#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "song.h"

int getMillisecondsPerBeat(int bpm)
{
    int minuteInMilliseconds = 60000;

    return round(minuteInMilliseconds / bpm);
}

int getSamplesBerBeat(int sampleRate, int millisecondsPerBeat)
{
    return (int)(sampleRate * millisecondsPerBeat) / 1000;
}

Song *createSong(int totalMeasures, int sampleRate, float timeSignature, int beatsPerMinute, int volume)
{
    size_t songSize = sizeof(Song);
    Song *song = malloc(songSize);
    if (song == NULL)
    {
        fprintf(stderr, "Error allocating Song\n");
        exit(EXIT_FAILURE);
    }

    memset(song, 0, songSize);
    song->totalMeasures = totalMeasures;
    song->sampleRate = sampleRate;
    song->timeSignature = timeSignature;
    song->beatsPerMinute = beatsPerMinute;
    song->volume = volume;
    song->millisecondsPerBeat = getMillisecondsPerBeat(beatsPerMinute);
    song->samplesPerBeat = getSamplesBerBeat(sampleRate, song->millisecondsPerBeat);

    return song;
}