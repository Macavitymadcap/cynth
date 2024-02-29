#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "audio_buffer.h"
#include "choices.h"
#include "duration.h"
#include "notes.h"
#include "scales.h"
#include "song.h"
#include "validation.h"
#include "wav.h"
#include "waveforms.h"

int main(int argc, char const *argv[])
{
    checkGetWurfelspiel(argc, argv[0]);

    int bpm = atoi(argv[1]);
    checkBpm(bpm);

    int volume = atoi(argv[2]);
    checkVolume(volume);

    // srandom(time(NULL));

    const char *waveformName = getRandomWaveformName();

    printf("bpm: %i, volume: %i, waveform: %s\n", bpm, volume, waveformName);

    const int totalMeasures = 32;
    Song *song = createSong(totalMeasures, STANDARD_SAMPLE_RATE, FOUR_FOUR, bpm, volume, waveformName);

    size_t bufferSize = calculateBufferSize(song);
    int16_t *buffer = createBuffer(bufferSize);

    WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, STANDARD_SAMPLE_RATE, bufferSize);

    Note *dBass = createNote(D3, SEMIBREVE);
    Note *aBass = createNote(A2, SEMIBREVE);
    Note *bBass = createNote(B2, SEMIBREVE);
    Note *gbBass = createNote(Gb2, SEMIBREVE);
    Note *gBass = createNote(G2, SEMIBREVE);

    Scale *major = createScale(STANDARD_LENGTH, MAJOR_INTERVALS);
    Scale *minor = createScale(STANDARD_LENGTH, NATURAL_MINOR_INTERVALS);

    const int FIRST_BEAT = 0;
    int measureIndex = 0;

    while (measureIndex < song->totalMeasures)
    {

        writeNoteToBuffer(dBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, D4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(aBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, A4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(bBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(minor, B4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(gbBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, Gb4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(gBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, G4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(dBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, D4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(gBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, G4, measureIndex, song, buffer);
        measureIndex++;

        writeNoteToBuffer(aBass, measureIndex, FIRST_BEAT, song, buffer);
        writeRandomBarOfScaleToBuffer(major, A4, measureIndex, song, buffer);
        measureIndex++;
    }

    const char *fileName = "cannon.wav";
    FILE *outfile = fopen(fileName, "wb");
    checkFileOpening(outfile, fileName);
    fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
    fwrite(buffer, bufferSize, 1, outfile);

    fclose(outfile);
    free(song);
    free(wavHeader);
    free(buffer);

    free(dBass);
    free(aBass);
    free(bBass);
    free(gBass);
    free(gbBass);
    free(major);
    free(minor);

    return 0;
}
