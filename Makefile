CC = gcc
LDLIBS = -lm
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c17 -g
INCLUDE = -Iinclude
SRC = src
BUILD = build

GET_WAVE = get_wave
FOUR_CHORDS = four_chords
GET_SCALE = get_scale

GET_WAVE_SRC = $(filter-out $(SRC)/$(FOUR_CHORDS).c $(SRC)/$(GET_SCALE).c, $(wildcard $(SRC)/*.c))
GET_WAVE_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_WAVE_SRC))

FOUR_CHORDS_SRC = $(filter-out $(SRC)/$(GET_WAVE).c $(SRC)/$(GET_SCALE).c, $(wildcard $(SRC)/*.c))
FOUR_CHORDS_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(FOUR_CHORDS_SRC))

GET_SCALE_SRC = $(filter-out $(SRC)/$(FOUR_CHORDS).c $(SRC)/$(GET_WAVE).c, $(wildcard $(SRC)/*.c))
GET_SCALE_OBJ = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(GET_SCALE_SRC))

$(shell mkdir -p $(BUILD))

all: $(GET_WAVE) $(FOUR_CHORDS) $(GET_SCALE)

$(GET_WAVE): $(GET_WAVE_OBJ)
	$(CC) $(CFLAGS) -o $(GET_WAVE) $(GET_WAVE_OBJ) $(LDLIBS)

$(FOUR_CHORDS): $(FOUR_CHORDS_OBJ)
	$(CC) $(CFLAGS) -o $(FOUR_CHORDS) $(FOUR_CHORDS_OBJ) $(LDLIBS)

$(GET_SCALE): $(GET_SCALE_OBJ)
	$(CC) $(CFLAGS) -o $(GET_SCALE) $(GET_SCALE_OBJ) $(LDLIBS)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o $(GET_WAVE) $(FOUR_CHORDS) $(GET_SCALE) *.wav
