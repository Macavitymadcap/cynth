/**
 * @file waveforms.h
 * @brief Functions and constants for generating different types of waveforms.
 */

#ifndef WAVEFORMS_H
#define WAVEFORMS_H

#include <stdint.h>

extern const char *SINE;
extern const char *SAWTOOTH;
extern const char *SQUARE;
extern const char *TRIANGLE;
extern const char *PULSE;

/**
 * @brief Generate a sine wave.
 * @param frequency Frequency of the sine wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the sine wave.
 * @return The generated sample of the sine wave.
 */
int16_t getSineWave(float frequency, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a square wave.
 * @param frequency Frequency of the square wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the square wave.
 * @return The generated sample of the square wave.
 */
int16_t getSquareWave(float frequency, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a sawtooth wave.
 * @param frequency Frequency of the sawtooth wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the sawtooth wave.
 * @return The generated sample of the sawtooth wave.
 */
int16_t getSawtoothWave(float frequency, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a triangle wave.
 * @param frequency Frequency of the triangle wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the triangle wave.
 * @return The generated sample of the triangle wave.
 */
int16_t getTriangleWave(float frequency, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a pulse wave.
 * @param frequency Frequency of the pulse wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the pulse wave.
 * @param dutyCycle Duty cycle of the pulse wave (proportion of time high).
 * @return The generated sample of the pulse wave.
 */
int16_t getPulseWave(float frequency, int bufferIndex, int sampleRate, int volume, float dutyCycle);

/**
 * @brief Get a waveform to write to a buffer
 * @param waveformName String of the type of waveform to return.
 * @param frequency Frequency of the pulse wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the pulse wave.
 * @return A waveform of the specified type.
*/
int16_t getWaveform(const char* waveformName, float frequency, int bufferIndex, int sampleRate, int volume);

#endif
