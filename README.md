# cynth

A suite of programs for synthesising sound implemented in C, drawing inspiration from the works of [kaizen](https://kaizen.place/music-tails/writing-wav-files-in-c-659462b3cc1c84922166019e) and Harvard's [CS50 course](https://www.edx.org/cs50), in particular week 4 on memory in C.

All programs are written for linux using the gcc compiler

## Programs

### get_wave
Create a wav file consisting of a waveform of a single note for a given amount of time 

To compile the program, run `make get_wave`, then to generate a sound run:

```
./get_wave <OUTFILE> <WAVEFORM> <NOTE> <SECONDS>
```

Where OUTFILE is a wav file and WAVEFORM is one of the following:
- pulse  
- sawtooth
- sine
- square
- triangle

NOTE is the name of a valid note from c0 to b8, using 'b' to denote a flat (e.g. 'db3'), and SECONDS is the length of time in seconds for the generated wavform.
