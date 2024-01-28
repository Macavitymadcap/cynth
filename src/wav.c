#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "wav.h"

const uint32_t STANDARD_CHUNK_SIZE = 16;

const uint16_t MONO = 1;
const uint16_t STEREO = 2;

const uint16_t PCM = 1;
const uint16_t MU_LAW = 257;
const uint16_t A_LAW = 258;
const uint16_t ADPCM1 = 259;

const uint16_t SIXTEEN_BIT_MONO = 2;
const uint16_t SIXTEEN_BIT_STEREO = 4;

const size_t WAVE_HEADER_SIZE = sizeof(WavHeader);

int getBytesPerSample(WavHeader *header)
{
    return header->bitsPerSample / 8 * header->numChannels;
}

int getBytesPerSecond(WavHeader *header)
{
    return header->sampleRate * header->bitsPerSample / 8 * header->numChannels;
}

int getBitsPerSample(WavHeader *header)
{
    return 8 * sizeof(short int) * header->numChannels;
}

WavHeader *createWavHeader(uint32_t fileLength, uint16_t audioFormat, uint16_t numChannels, uint32_t sampleRate, size_t bufferSize)
{
    WavHeader *header = malloc(WAVE_HEADER_SIZE);
    if (header == NULL)
    {
        fprintf(stderr, "Error allocating WavHeader\n");
        exit(EXIT_FAILURE);
    }

    memset(header, 0, WAVE_HEADER_SIZE);
    memcpy(header->riff, "RIFF", 4);
    memcpy(header->wave, "WAVE", 4);
    memcpy(header->fmt, "fmt ", 4);
    memcpy(header->data, "data", 4);
    header->chunkSize = fileLength;
    header->audioFormat = audioFormat;
    header->numChannels = numChannels;
    header->sampleRate = sampleRate;
    header->bitsPerSample = getBitsPerSample(header);
    header->bytesPerSample = getBytesPerSample(header);
    header->bytesPerSecond = getBytesPerSecond(header);
    header->dataLength = bufferSize * header->bytesPerSample;
    header->fileLength = header->dataLength + WAVE_HEADER_SIZE;
    
    return header;
}