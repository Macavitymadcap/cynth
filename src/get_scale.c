#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "wav.h"
#include "notes.h"
#include "play.h"
#include "waveforms.h"
#include "validation.h"
#include "duration.h"
#include "audio_buffer.h"
#include "song.h"

int main(int argc, const char *argv[])
{
    checkGetScaleUsage(argc, argv[0]);

    const char *waveformName = argv[1];
    checkWaveformName(waveformName);

    const int sampleRate = 16000;

    Song *song = createSong(4, sampleRate, FOUR_FOUR, 100, 3000);

    size_t bufferSize = song->totalMeasures * song->timeSignature * song->samplesPerBeat;
    int16_t *buffer = createBuffer(bufferSize);

    WavHeader *wavHeader = createWavHeader(STANDARD_CHUNK_SIZE, PCM, MONO, sampleRate, bufferSize);

    Note *doh = createNote(C4, CROTCHET);
    Note *ray = createNote(D4, CROTCHET);
    Note *mi = createNote(E4, CROTCHET);
    Note *fah = createNote(F4, CROTCHET);
    Note *so = createNote(G4, CROTCHET);
    Note *la = createNote(A4, CROTCHET);
    Note *ti = createNote(B4, CROTCHET);
    Note *highDoh = createNote(C5, CROTCHET);

    int meausreIndex = 0;
    while (meausreIndex < song->totalMeasures)
    {
        writeNoteToBuffer(waveformName, doh, meausreIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, ray, meausreIndex, 1, song, buffer);
        writeNoteToBuffer(waveformName, mi, meausreIndex, 2, song, buffer);
        writeNoteToBuffer(waveformName, fah, meausreIndex, 3, song, buffer);

        meausreIndex++;

        writeNoteToBuffer(waveformName, so, meausreIndex, 0, song, buffer);
        writeNoteToBuffer(waveformName, la, meausreIndex, 1, song, buffer);
        writeNoteToBuffer(waveformName, ti, meausreIndex, 2, song, buffer);
        writeNoteToBuffer(waveformName, highDoh, meausreIndex, 3, song, buffer);

        meausreIndex++;
    }

    const char *fileName = "c_major.wav";
    FILE *outfile = fopen(fileName, "wb");
    checkFileOpening(outfile, fileName);
    fwrite(wavHeader, WAVE_HEADER_SIZE, 1, outfile);
    fwrite(buffer, bufferSize, 1, outfile);

    fclose(outfile);
    free(song);
    free(wavHeader);
    free(buffer);
    free(doh);
    free(ray);
    free(mi);
    free(fah);
    free(so);
    free(la);
    free(ti);
    free(highDoh);

    exit(EXIT_SUCCESS);
}