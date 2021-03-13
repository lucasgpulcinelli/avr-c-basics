
# Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
# This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.

DEV ?= /dev/ttyACM0 #device containing the arduino (for my machine always is this device no matter the linux distribution, if "no such file or directory" errors ocurr try to find the device in the /dev directory)
DEVICE ?= atmega328p
PROGRAMMER ?= arduino

FILE ?= main
BUILD_DIR = build
SRC_DIR = src

CFLAGS ?= -Os -Wall -mmcu=$(DEVICE)
CPPFLAGS ?= $(CFLAGS)

.PHONY: clean flash asm


all: $(BUILD_DIR)/$(FILE).hex


clean: 
	$(RM) -r build/


asm: $(BUILD_DIR)/$(FILE).asm


flash: $(BUILD_DIR)/$(FILE).hex
	sudo avrdude -p $(DEVICE) -c $(PROGRAMMER) -U flash:w:$<:i -F -P $(DEV)



$(BUILD_DIR)/$(FILE).hex: $(BUILD_DIR)/$(FILE).bin
	avr-objcopy -j .text -j .data -O ihex $< $@


$(BUILD_DIR)/%.bin: $(SRC_DIR)/%.c
	avr-gcc $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.bin: $(SRC_DIR)/%.cpp
	avr-g++ $(CPPFLAGS) -o $@ $<


$(BUILD_DIR)/%.asm: $(SRC_DIR)/%.c
	avr-gcc $(CFLAGS) -S -o $@ $<

$(BUILD_DIR)/%.asm: $(SRC_DIR)/%.cpp
	avr-g++ $(CPPFLAGS) -S -o $@ $<

