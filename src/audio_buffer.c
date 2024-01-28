#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "audio_buffer.h"

int16_t *createBuffer(int size)
{
    size_t dataSize = sizeof(int16_t);

    int16_t*buffer = malloc(size * dataSize);
    if (buffer == NULL)
    {
        fprintf(stderr, "Error allocating audio buffer\n");
        exit(EXIT_FAILURE);
    }

    memset(buffer, 0, size * dataSize);

    return buffer;
}