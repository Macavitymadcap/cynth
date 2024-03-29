# cynth

A suite of programs for synthesising sound implemented in C, drawing inspiration from the works of [kaizen](https://kaizen.place/music-tails/writing-wav-files-in-c-659462b3cc1c84922166019e) and Harvard's [CS50 course](https://www.edx.org/cs50), in particular week 4 on memory in C.

All programs are written for linux/mac using the gcc compiler.

## Usage
To compile all programs, run `make`, or `make [PROGRAM_NAME]` to compile one specifically. To see full usage look in the `docs` directory, or run the programs without arguments to print the usage to the console.

## Programs

### get_wave
Create a wav file consisting of a waveform of a single note for a given amount of time.

Essentially a refactoring of kaizen's [middle-c](https://kaizen.place/music-tails/writing-wav-files-in-c-659462b3cc1c84922166019e). I have modularised the functionality for reuse, improved it's memory safety and added more options for what type of waveform, pitch and volume is generated.

### get_four_chords
Create a wav file playing the 'four chords' progression using variable key, waveforms, bpm and volume.

Another refactoring of the work of kaizen, this time [4-chords](https://kaizen.place/music-tails/writing-wav-files-in-c-630150ea1b3ccbc86a636770). More modularisation, memory safety and options.

### get_scale
Create a wav file that plays a given scale ascending then descending using variable tonic, waveform, bpm and volume.

Having got to grips with kaizen's work, this one is my own creation to prove out that melodies can be written to wav.