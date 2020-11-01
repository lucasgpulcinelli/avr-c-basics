
# Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
# This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.

DEV ?= /dev/ttyACM0 #device containing the arduino (for my machine always is this device no matter the linux distribution, if "no such file or directory" errors ocurr try to find the device in the /dev directory)
DEVICE ?= atmega328p
PROGRAMMER ?= arduino


FILE ?= main
BUILD_DIR = build
OUT_FILE = $(BUILD_DIR)/$(FILE)
SRC_FILE = src/$(FILE).c

.PHONY: clean flash asm

all: output.hex
	
output.hex: $(OUT_FILE).bin
	avr-objcopy -j .text -j .data -O ihex $(OUT_FILE).bin $(BUILD_DIR)/output.hex

$(OUT_FILE).bin: $(SRC_FILE)
	avr-gcc -Wall -Os -mmcu=$(DEVICE) -o $(OUT_FILE).bin $(SRC_FILE)

clean: 
	rm -r build/*

asm: $(SRC_FILE)
	avr-gcc -Wall -Os -mmcu=$(DEVICE) -o $(OUT_FILE).asm -S $(SRC_FILE)

flash:
	avrdude -p $(DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/output.hex:i -F -P $(DEV)

