CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -std=c17 -g

# List of source files
GET_WAVE_SRC = src/get_wave.c src/waveforms.c src/wav.c src/validation.c src/notes.c

# List of object files
GET_WAVE_OBJ = $(GET_WAVE_SRC:.c=.o)

# The main target
get_wave: $(GET_WAVE_OBJ)
	$(CC) $(CFLAGS) -o get_wave $(GET_WAVE_OBJ) $(LDLIBS)

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

.PHONY: clean

clean:
	rm -f src/*.o $(objects) cynth *.wav
