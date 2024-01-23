CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -std=c17 -g

GET_WAVE_SRC = src/get_wave.c src/waveforms.c src/wav.c src/validation.c src/notes.c
GET_WAVE_OBJ = $(GET_WAVE_SRC:.c=.o)

FOUR_CHORDS_SRC = src/four_chords.c src/waveforms.c src/wav.c src/validation.c src/play.c src/notes.c
FOUR_CHORDS_OBJ = $(FOUR_CHORDS_SRC:.c=.o)

all: get_wave four_chords

get_wave: $(GET_WAVE_OBJ)
	$(CC) $(CFLAGS) -o get_wave $(GET_WAVE_OBJ) $(LDLIBS)

four_chords: $(FOUR_CHORDS_OBJ)
	$(CC) $(CFLAGS) -o four_chords $(FOUR_CHORDS_OBJ) $(LDLIBS)

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

.PHONY: clean

clean:
	rm -f src/*.o $(objects) get_wave four_chords *.wav
