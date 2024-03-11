CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c17 -g
INCLUDE = -Iinclude
SRC = src
BUILD = build

GET_WAVE = get_wave
GET_FOUR_CHORDS = get_four_chords
GET_SCALE = get_scale

GET_WAVE_SRC = $(filter-out $(SRC)/$(GET_FOUR_CHORDS).c $(SRC)/$(GET_SCALE).c $(SRC)/chords.c, $(wildcard $(SRC)/*.c))
GET_WAVE_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_WAVE_SRC))

GET_FOUR_CHORDS_SRC = $(filter-out $(SRC)/$(GET_WAVE).c $(SRC)/$(GET_SCALE).c, $(wildcard $(SRC)/*.c))
GET_FOUR_CHORDS_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_FOUR_CHORDS_SRC))

GET_SCALE_SRC = $(filter-out $(SRC)/$(GET_FOUR_CHORDS).c $(SRC)/$(GET_WAVE).c $(SRC)/chords.c, $(wildcard $(SRC)/*.c))
GET_SCALE_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_SCALE_SRC))

$(shell mkdir -p $(BUILD))

all: $(GET_WAVE) $(GET_FOUR_CHORDS) $(GET_SCALE)

$(GET_WAVE): $(GET_WAVE_OBJ)
	$(CC) $(CFLAGS) -o $(GET_WAVE) $(GET_WAVE_OBJ) $(LDLIBS)

$(GET_FOUR_CHORDS): $(GET_FOUR_CHORDS_OBJ)
	$(CC) $(CFLAGS) -o $(GET_FOUR_CHORDS) $(GET_FOUR_CHORDS_OBJ) $(LDLIBS)

$(GET_SCALE): $(GET_SCALE_OBJ)
	$(CC) $(CFLAGS) -o $(GET_SCALE) $(GET_SCALE_OBJ) $(LDLIBS)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o $(GET_WAVE) $(GET_FOUR_CHORDS) $(GET_SCALE) *.wav
