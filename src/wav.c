#include <string.h>
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

void setFormatFields(WavHeader *header)
{
    memcpy(header->riff, "RIFF", 4);
    memcpy(header->wave, "WAVE", 4);
    memcpy(header->fmt, "fmt ", 4);
    memcpy(header->data, "data", 4);
}

void setupHeader(WavHeader *header, uint32_t fileLength, uint16_t audioFormat, uint16_t numChannels, uint32_t sampleRate)
{
    setFormatFields(header);
    header->chunkSize = fileLength;
    header->audioFormat = audioFormat;
    header->numChannels = numChannels;
    header->sampleRate = sampleRate;
    header->bytesPerSample = getBytesPerSample(header);
    header->bytesPerSecond = getBytesPerSecond(header);
    header->bitsPerSample = getBitsPerSample(header);
}

void setDataAndFileLength(WavHeader *header, size_t bufferSize, size_t headerSize)
{
    header->dataLength = bufferSize * header->bytesPerSample;
    header->fileLength = header->dataLength + headerSize;
}