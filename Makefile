CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -std=c17 -g

# List of source files
SRC = src/main.c src/waveforms.c src/wav.c src/validation.c src/notes.c

# List of object files
OBJ = $(SRC:.c=.o)

# The main target
cynth: $(OBJ)
	$(CC) $(CFLAGS) -o cynth $(OBJ) $(LDLIBS)

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

.PHONY: clean

clean:
	rm -f src/*.o $(objects) cynth *.wav