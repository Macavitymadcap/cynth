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

    int bpm = atoi(argv[4]);
    checkBpm(bpm);

    int volume = atoi(argv[5]);
    checkVolume(volume);

    const int sampleRate = 16000;

    Song *song = createSong(8, sampleRate, FOUR_FOUR, bpm, volume * 500);

    size_t bufferSize = song->totalMeasures * song->timeSignature * song->samplesPerBeat;
    int16_t *buffer = createBuffer(bufferSize);

    WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

    Note *scale = createScaleArray(C4, NATURAL_MINOR_INTERVALS, WHOLE_TONE_SCALE_LENGTH);

    int measureIndex = 0;
    while (measureIndex < song->totalMeasures)
    {
        writeNoteToBuffer(waveformName, &scale[0], measureIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, &scale[1], measureIndex, 1, song, buffer);
        writeNoteToBuffer(waveformName, &scale[2], measureIndex, 2, song, buffer);
        writeNoteToBuffer(waveformName, &scale[4], measureIndex, 3, song, buffer);
        measureIndex++;

        writeNoteToBuffer(waveformName, &scale[5], measureIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, &scale[6], measureIndex, 1, song, buffer);
        writeNoteToBuffer(waveformName, &scale[7], measureIndex, 2, song, buffer);
        writeNoteToBuffer(waveformName, &scale[6], measureIndex, 3, song, buffer);
        measureIndex++;

        writeNoteToBuffer(waveformName, &scale[5], measureIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, &scale[4], measureIndex, 1, song, buffer);
        writeNoteToBuffer(waveformName, &scale[3], measureIndex, 2, song, buffer);
        writeNoteToBuffer(waveformName, &scale[2], measureIndex, 3, song, buffer);
        measureIndex++;

        writeNoteToBuffer(waveformName, &scale[1], measureIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, &scale[0], measureIndex, 1, song, buffer);
        measureIndex++;
    }

    FILE *outfile = fopen("scale.wav", "wb");
    checkFileOpening(outfile, "scale.wav");
    fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
    fwrite(buffer, bufferSize, 1, outfile);

    fclose(outfile);
    free(song);
    free(wavHeader);
    free(buffer);
    free(scale);

    exit(EXIT_SUCCESS);
}