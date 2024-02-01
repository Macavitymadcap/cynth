/**
 * @file wav.h
 * @brief Struct, consts and function for creating WavHeaders.
 *
 */

#ifndef WAV_H
#define WAV_H

#include <stdint.h>

/**
 * @brief Integer representing the usual size of the format subchunk.
 */
extern const uint32_t STANDARD_CHUNK_SIZE;

/**
 * @brief Integer representing one audio channel.
 */
extern const uint16_t MONO;

/**
 * @brief Integer representing two audio channels.
 */
extern const uint16_t STEREO;

/**
 * @brief Integer representing the PCM audio format.
 */
extern const uint16_t PCM;

/**
 * @brief Integer representing the Mu-Law audio format.
 */
extern const uint16_t MU_LAW;

/**
 * @brief Integer representing the A-Law audio format.
 */
extern const uint16_t A_LAW;

/**
 * @brief Integer reprsenting the ADPCM1 audio format.
 */
extern const uint16_t ADPCM1;

/**
 * @brief Integer representing 16-bit mono bits per sample.
 */
extern const uint16_t SIXTEEN_BIT_MONO;

/**
 * @brief Integer representing 16-bit stereo bits per sample.
 */
extern const uint16_t SIXTEEN_BIT_STEREO;

/**
 * @brief Size of the WavHeader struct.
*/
extern const size_t WAVE_HEADER_SIZE;

/**
 * @struct WavHeader
 * @brief Structure representing the header of a WAV file.
 *
 * The WavHeader structure contains information about the type, size,
 * and layout of a file that contains audio samples.
 * Adapted from http://soundfile.sapp.org/doc/WaveFormat/.
 */
typedef struct
{
    uint8_t riff[4];         /** Four bytes that identify the file format (RIFF). */
    uint32_t fileLength;     /** Size of the entire file in bytes. */
    uint8_t wave[4];         /** Four bytes that identify the file as a WAV file (WAVE). */
    uint8_t fmt[4];          /** Four bytes that identify the format subchunk (fmt ). */
    uint32_t chunkSize;      /** Size of the format subchunk (usually 16). */
    uint16_t audioFormat;    /** Audio format (1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM1). */
    uint16_t numChannels;    /** Number of audio channels (1=mono, 2=stereo). */
    uint32_t sampleRate;     /** Number of samples per second. */
    uint32_t bytesPerSecond; /** Number of bytes per second. */
    uint16_t bytesPerSample; /** Number of bytes for one sample including all channels. */
    uint16_t bitsPerSample;  /** Number of bits per sample (2=16-bit mono, 4=16-bit stereo). */
    uint8_t data[4];         /** Four bytes that identify the data subchunk (data). */
    uint32_t dataLength;     /** Size of the data subchunk. */
} __attribute__((__packed__)) WavHeader;

/**
 * @brief Calculate the byte rate for a WAV header.
 *
 * This function calculates the byte rate, which represents the number
 * of bytes transmitted per second, for a given WAV header.
 *
 * @param header Pointer to the WAV header structure.
 * @return The calculated byte rate.
 */
int getBytesPerSecond(WavHeader *header);

/**
 * @brief Calculate the block alignment for a WAV header.
 *
 * This function calculates the block alignment, which represents the number
 * of bytes for one sample including all channels.
 *
 * @param header Pointer to the WAV header structure.
 * @return The calculated block alignment.
 */
int getBytesPerSample(WavHeader *header);

/**
 * @brief Get the number of bits per sample for a WAV header.
 *
 * This function calculates the total number of bits per sample, taking
 * into account the bit depth and the number of audio channels specified
 * in the given WAV header.
 *
 * @param header Pointer to the WAV header structure.
 * @return The calculated number of bits per sample.
 */
int getBitsPerSample(WavHeader *header);

/**
 * @brief Create a WavHeader struct, exiting the program if allocation fails.
 *
 * @param header Pointer to the WavHeader structure to be initialized.
 * @param fileLength Size of the audio subchunk1 in bytes.
 * @param audioFormat Audio format (e.g., PCM, IEEE floating point, etc.).
 * @param numChannels Number of audio channels (e.g., mono, stereo).
 * @param sampleRate The sample rate of the audio data.
 * @param bufferSize Size of the data buffer in samples.
 * @returns Pointer to the create WavHeader.
 */
WavHeader *createWavHeader(uint32_t fileLength, uint16_t audioFormat, uint16_t numChannels, uint32_t sampleRate, size_t bufferSize);

#endif
