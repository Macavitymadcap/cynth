/**
 * @file audio_buffer.h
 * @brief Functions for creating audio buffers
*/

#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include "stdint.h"

/**
 * @brief Create a buffer for writing audio, exiting the program if allocation fails.
 * @param size Size of the buffer to be created.
 * @returns Pointer to the created buffer.
*/
int16_t *createBuffer(int size);

#endif