CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -std=c17 -g
INCLUDE = -Iinclude
SRC = src
BUILD = build

GET_WAVE_SRC = $(filter-out $(SRC)/play.c $(SRC)/duration.c $(SRC)/four_chords.c, $(wildcard $(SRC)/*.c))
GET_WAVE_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_WAVE_SRC))

FOUR_CHORDS_SRC = $(filter-out $(SRC)/get_wave.c, $(wildcard $(SRC)/*.c))
FOUR_CHORDS_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(FOUR_CHORDS_SRC))

all: get_wave four_chords

get_wave: $(GET_WAVE_OBJ)
	$(CC) $(CFLAGS) -o get_wave $(GET_WAVE_OBJ) $(LDLIBS)

four_chords: $(FOUR_CHORDS_OBJ)
	$(CC) $(CFLAGS) -o four_chords $(FOUR_CHORDS_OBJ) $(LDLIBS)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o get_wave four_chords *.wav
