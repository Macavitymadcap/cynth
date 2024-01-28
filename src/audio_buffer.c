#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "audio_buffer.h"

short int *createBuffer(int size)
{
    short int *buffer = malloc(size * sizeof(short int));
    if (buffer == NULL)
    {
        fprintf(stderr, "Error allocating audio buffer\n");
        exit(EXIT_FAILURE);
    }

    memset(buffer, 0, size * sizeof(short int));

    return buffer;
}