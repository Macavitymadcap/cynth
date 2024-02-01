#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "notes.h"

const float C0 = 16.35;
const float Db0 = 17.32;
const float D0 = 18.35;
const float Eb0 = 19.45;
const float E0 = 20.60;
const float F0 = 21.83;
const float Gb0 = 23.12;
const float G0 = 24.50;
const float Ab0 = 25.96;
const float A0 = 27.50;
const float Bb0 = 29.14;
const float B0 = 30.87;
const float C1 = 32.70;
const float Db1 = 34.65;
const float D1 = 36.71;
const float Eb1 = 38.89;
const float E1 = 41.20;
const float F1 = 43.65;
const float Gb1 = 46.25;
const float G1 = 49.00;
const float Ab1 = 51.91;
const float A1 = 55.00;
const float Bb1 = 58.27;
const float B1 = 61.74;
const float C2 = 65.41;
const float Db2 = 69.30;
const float D2 = 73.42;
const float Eb2 = 77.78;
const float E2 = 82.41;
const float F2 = 87.31;
const float Gb2 = 92.50;
const float G2 = 98.00;
const float Ab2 = 103.83;
const float A2 = 110.00;
const float Bb2 = 116.54;
const float B2 = 123.47;
const float C3 = 130.81;
const float Db3 = 138.59;
const float D3 = 146.83;
const float Eb3 = 155.56;
const float E3 = 164.81;
const float F3 = 174.61;
const float Gb3 = 185.00;
const float G3 = 196.00;
const float Ab3 = 207.65;
const float A3 = 220.00;
const float Bb3 = 233.08;
const float B3 = 246.94;
const float C4 = 261.63;
const float Db4 = 277.18;
const float D4 = 293.66;
const float Eb4 = 311.13;
const float E4 = 329.63;
const float F4 = 349.23;
const float Gb4 = 369.99;
const float G4 = 392.00;
const float Ab4 = 415.30;
const float A4 = 440.00;
const float Bb4 = 466.16;
const float B4 = 493.88;
const float C5 = 523.25;
const float Db5 = 554.37;
const float D5 = 587.33;
const float Eb5 = 622.25;
const float E5 = 659.25;
const float F5 = 698.46;
const float Gb5 = 739.99;
const float G5 = 783.99;
const float Ab5 = 830.61;
const float A5 = 880.00;
const float Bb5 = 932.33;
const float B5 = 987.77;
const float C6 = 1046.50;
const float Db6 = 1108.73;
const float D6 = 1174.66;
const float Eb6 = 1244.51;
const float E6 = 1318.51;
const float F6 = 1396.91;
const float Gb6 = 1479.98;
const float G6 = 1567.98;
const float Ab6 = 1661.22;
const float A6 = 1760.00;
const float Bb6 = 1864.66;
const float B6 = 1975.53;
const float C7 = 2093.00;
const float Db7 = 2217.46;
const float D7 = 2349.32;
const float Eb7 = 2489.02;
const float E7 = 2637.02;
const float F7 = 2793.83;
const float Gb7 = 2959.96;
const float G7 = 3135.96;
const float Ab7 = 3322.44;
const float A7 = 3520.00;
const float Bb7 = 3729.31;
const float B7 = 3951.07;
const float C8 = 4186.01;
const float Db8 = 4434.92;
const float D8 = 4698.63;
const float Eb8 = 4978.03;
const float E8 = 5274.04;
const float F8 = 5587.65;
const float Gb8 = 5919.91;
const float G8 = 6271.93;
const float Ab8 = 6644.88;
const float A8 = 7040.00;
const float Bb8 = 7458.62;
const float B8 = 7902.13;

float getFrequencyFromName(const char *noteName)
{
    if (strcmp(noteName, "c0") == 0)
        return C0;
    else if (strcmp(noteName, "db0") == 0)
        return Db0;
    else if (strcmp(noteName, "d0") == 0)
        return D0;
    else if (strcmp(noteName, "eb0") == 0)
        return Eb0;
    else if (strcmp(noteName, "e0") == 0)
        return E0;
    else if (strcmp(noteName, "f0") == 0)
        return F0;
    else if (strcmp(noteName, "gb0") == 0)
        return Gb0;
    else if (strcmp(noteName, "g0") == 0)
        return G0;
    else if (strcmp(noteName, "ab0") == 0)
        return Ab0;
    else if (strcmp(noteName, "a0") == 0)
        return A0;
    else if (strcmp(noteName, "bb0") == 0)
        return Bb0;
    else if (strcmp(noteName, "b0") == 0)
        return B0;
    else if (strcmp(noteName, "c1") == 0)
        return C1;
    else if (strcmp(noteName, "db1") == 0)
        return Db1;
    else if (strcmp(noteName, "d1") == 0)
        return D1;
    else if (strcmp(noteName, "eb1") == 0)
        return Eb1;
    else if (strcmp(noteName, "e1") == 0)
        return E1;
    else if (strcmp(noteName, "f1") == 0)
        return F1;
    else if (strcmp(noteName, "gb1") == 0)
        return Gb1;
    else if (strcmp(noteName, "g1") == 0)
        return G1;
    else if (strcmp(noteName, "ab1") == 0)
        return Ab1;
    else if (strcmp(noteName, "a1") == 0)
        return A1;
    else if (strcmp(noteName, "bb1") == 0)
        return Bb1;
    else if (strcmp(noteName, "b1") == 0)
        return B1;
    else if (strcmp(noteName, "c2") == 0)
        return C2;
    else if (strcmp(noteName, "db2") == 0)
        return Db2;
    else if (strcmp(noteName, "d2") == 0)
        return D2;
    else if (strcmp(noteName, "eb2") == 0)
        return Eb2;
    else if (strcmp(noteName, "e2") == 0)
        return E2;
    else if (strcmp(noteName, "f2") == 0)
        return F2;
    else if (strcmp(noteName, "gb2") == 0)
        return Gb2;
    else if (strcmp(noteName, "g2") == 0)
        return G2;
    else if (strcmp(noteName, "ab2") == 0)
        return Ab2;
    else if (strcmp(noteName, "a2") == 0)
        return A2;
    else if (strcmp(noteName, "bb2") == 0)
        return Bb2;
    else if (strcmp(noteName, "b2"))
        return B2;
    else if (strcmp(noteName, "c3") == 0)
        return C3;
    else if (strcmp(noteName, "db3") == 0)
        return Db3;
    else if (strcmp(noteName, "d3") == 0)
        return D3;
    else if (strcmp(noteName, "eb3") == 0)
        return Eb3;
    else if (strcmp(noteName, "e3") == 0)
        return E3;
    else if (strcmp(noteName, "f3") == 0)
        return F3;
    else if (strcmp(noteName, "gb3") == 0)
        return Gb3;
    else if (strcmp(noteName, "g3") == 0)
        return G3;
    else if (strcmp(noteName, "ab3") == 0)
        return Ab3;
    else if (strcmp(noteName, "a3") == 0)
        return A3;
    else if (strcmp(noteName, "bb3") == 0)
        return Bb3;
    else if (strcmp(noteName, "b3"))
        return B3;
    else if (strcmp(noteName, "c4") == 0)
        return C4;
    else if (strcmp(noteName, "db4") == 0)
        return Db4;
    else if (strcmp(noteName, "d4") == 0)
        return D4;
    else if (strcmp(noteName, "eb4") == 0)
        return Eb4;
    else if (strcmp(noteName, "e4") == 0)
        return E4;
    else if (strcmp(noteName, "f4") == 0)
        return F4;
    else if (strcmp(noteName, "gb4") == 0)
        return Gb4;
    else if (strcmp(noteName, "g4") == 0)
        return G4;
    else if (strcmp(noteName, "ab4") == 0)
        return Ab4;
    else if (strcmp(noteName, "a4") == 0)
        return A4;
    else if (strcmp(noteName, "bb4") == 0)
        return Bb4;
    else if (strcmp(noteName, "b4") == 0)
        return B4;
    else if (strcmp(noteName, "c5") == 0)
        return C5;
    else if (strcmp(noteName, "db5") == 0)
        return Db5;
    else if (strcmp(noteName, "d5") == 0)
        return D5;
    else if (strcmp(noteName, "eb5") == 0)
        return Eb5;
    else if (strcmp(noteName, "e5") == 0)
        return E5;
    else if (strcmp(noteName, "f5") == 0)
        return F5;
    else if (strcmp(noteName, "gb5") == 0)
        return Gb5;
    else if (strcmp(noteName, "g5") == 0)
        return G5;
    else if (strcmp(noteName, "ab5") == 0)
        return Ab5;
    else if (strcmp(noteName, "a5") == 0)
        return A5;
    else if (strcmp(noteName, "bb5") == 0)
        return Bb5;
    else if (strcmp(noteName, "b5"))
        return B5;
    else if (strcmp(noteName, "c6") == 0)
        return C6;
    else if (strcmp(noteName, "db6") == 0)
        return Db6;
    else if (strcmp(noteName, "d6") == 0)
        return D6;
    else if (strcmp(noteName, "eb6") == 0)
        return Eb6;
    else if (strcmp(noteName, "e6") == 0)
        return E6;
    else if (strcmp(noteName, "f6") == 0)
        return F6;
    else if (strcmp(noteName, "gb6") == 0)
        return Gb6;
    else if (strcmp(noteName, "g6") == 0)
        return G6;
    else if (strcmp(noteName, "ab6") == 0)
        return Ab6;
    else if (strcmp(noteName, "a6") == 0)
        return A6;
    else if (strcmp(noteName, "bb6") == 0)
        return Bb6;
    else if (strcmp(noteName, "b6"))
        return B6;
    else if (strcmp(noteName, "c7") == 0)
        return C7;
    else if (strcmp(noteName, "db7") == 0)
        return Db7;
    else if (strcmp(noteName, "d7") == 0)
        return D7;
    else if (strcmp(noteName, "eb7") == 0)
        return Eb7;
    else if (strcmp(noteName, "e7") == 0)
        return E7;
    else if (strcmp(noteName, "f7") == 0)
        return F7;
    else if (strcmp(noteName, "gb7") == 0)
        return Gb7;
    else if (strcmp(noteName, "g7") == 0)
        return G7;
    else if (strcmp(noteName, "ab7") == 0)
        return Ab7;
    else if (strcmp(noteName, "a7") == 0)
        return A7;
    else if (strcmp(noteName, "bb7") == 0)
        return Bb7;
    else if (strcmp(noteName, "b7"))
        return B7;
    else if (strcmp(noteName, "c8") == 0)
        return C8;
    else if (strcmp(noteName, "db8") == 0)
        return Db8;
    else if (strcmp(noteName, "d8") == 0)
        return D8;
    else if (strcmp(noteName, "eb8") == 0)
        return Eb8;
    else if (strcmp(noteName, "e8") == 0)
        return E8;
    else if (strcmp(noteName, "f8") == 0)
        return F8;
    else if (strcmp(noteName, "gb8") == 0)
        return Gb8;
    else if (strcmp(noteName, "g8") == 0)
        return G8;
    else if (strcmp(noteName, "ab8") == 0)
        return Ab8;
    else if (strcmp(noteName, "a8") == 0)
        return A8;
    else if (strcmp(noteName, "bb8") == 0)
        return Bb8;
    else if (strcmp(noteName, "b8"))
        return B8;

    return 0.0;
}

const size_t NOTE_SIZE = sizeof(Note);

Note *createNote(float frequency, float value)
{
    Note *newNote = malloc(NOTE_SIZE);
    if (newNote == NULL)
    {
        fprintf(stderr, "Error allocating Note. Frequency: %f Value: %f\n", frequency, value);
        exit(EXIT_FAILURE);
    }

    memset(newNote, 0, NOTE_SIZE);
    newNote->frequency = frequency;
    newNote->value = value;

    return newNote;
}
