/**
 * @file waveforms.h
 * @brief Functions and constants for generating different types of waveforms.
 */

#ifndef WAVEFORMS_H
#define WAVEFORMS_H

/**
 * @brief The value of Pi, included to avoid compilation issues.
 */
#define M_PI (3.14159265358979323846264338327950288)

extern const char *SINE;
extern const char *SAWTOOTH;
extern const char *SQUARE;
extern const char *TRIANGLE;
extern const char *PULSE;

/**
 * @brief Generate a sine wave.
 * @param note Frequency of the sine wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the sine wave.
 * @return The generated sample of the sine wave.
 */
short int getSineWave(float note, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a square wave.
 * @param note Frequency of the square wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the square wave.
 * @return The generated sample of the square wave.
 */
short int getSquareWave(float note, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a sawtooth wave.
 * @param note Frequency of the sawtooth wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the sawtooth wave.
 * @return The generated sample of the sawtooth wave.
 */
short int getSawtoothWave(float note, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a triangle wave.
 * @param note Frequency of the triangle wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the triangle wave.
 * @return The generated sample of the triangle wave.
 */
short int getTriangleWave(float note, int bufferIndex, int sampleRate, int volume);

/**
 * @brief Generate a pulse wave.
 * @param note Frequency of the pulse wave.
 * @param bufferIndex Sample bufferIndex.
 * @param sampleRate Sample rate in Hz.
 * @param volume Amplitude of the pulse wave.
 * @param dutyCycle Duty cycle of the pulse wave (proportion of time high).
 * @return The generated sample of the pulse wave.
 */
short int getPulseWave(float note, int bufferIndex, int sampleRate, int volume, float dutyCycle);

#endif // WAVEFORM_H
