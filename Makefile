SOURCE = main.c
OBJ_1 = motor.c

BUILD_DIR = build
LIB_DIR = lib
LIB_NAME = stepper
INCLUDE_DIR = include
SRC_DIR = src

PROGRAMMER = arduino
PORT = /dev/ttyACM0

CC = avr-gcc
OBJCOPY = avr-objcopy
MMCU = atmega328p
F_CPU = 16000000UL
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MMCU) -Wall
LDFLAGS = -mmcu=$(MMCU)

OUTPUT = main

OBJ_1_FILE = $(BUILD_DIR)/$(OBJ_1:.c=.o)

LIBRARY = $(LIB_DIR)/lib$(LIB_NAME).$(if $(filter Windows_NT, $(OS)), lib,a)

all: create_build_folder $(BUILD_DIR)/$(OUTPUT).hex

$(BUILD_DIR)/$(OUTPUT).hex: $(BUILD_DIR)/$(OUTPUT).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR)/$(OUTPUT).elf: $(BUILD_DIR)/$(OUTPUT).o $(LIBRARY)
	$(CC) $(LDFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)

$(BUILD_DIR)/$(OUTPUT).o: $(SOURCE)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

$(LIBRARY): $(OBJ_1_FILE)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $<

$(OBJ_1_FILE): $(SRC_DIR)/$(OBJ_1)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

flash: $(BUILD_DIR)/$(OUTPUT).hex
	avrdude -c $(PROGRAMMER) -p $(MMCU) -P $(PORT) -U flash:w:$<

create_build_folder:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(LIBRARY)

.PHONY: all flash create_build_folder clean
