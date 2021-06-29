
# Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
# This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.


DEV        ?= /dev/ttyACM0
DEVICE     ?= atmega328p
PROGRAMMER ?= arduino

CC          = avr-gcc
CXX         = avr-g++
AVRDUDE    ?= avrdude
OBJCOPY    ?= avr-objcopy
SUDO       ?= sudo


CFLAGS     += -Wall -Os -mmcu=$(DEVICE)
CPPFLAGS   += $(CFLAGS)

SRCD       ?= src


.PHONY: all clean help


all: help


help:
	@echo ""
	@echo "This is a help page for this Makefile:"
	@echo ""
	@echo "Use \"make <name of the project without the extension>\""
	@echo "to build and flash the project"
	@echo ""
	@echo "Examples:"
	@echo "make blink"
	@echo "make cppexample"
	@echo "make main"
	@echo ""
	@echo "If you are using a board other than the atmega328p (arduino UNO), use"
	@echo "\"make DEVICE=<name of your processor> <target>\""
	@echo ""
	@echo "If you receive an error such as \"no such device $(DEV)\","
	@echo "search for the dev node for the board in /dev and use"
	@echo "\"make DEV=/dev/<your dev node> <target>\""
	@echo ""
	@echo "Other options:"
	@echo ""
	@echo "Use \"make $(SRCD)/<project>.S\" to create the gnu assembly file for that project"

%: $(SRCD)/%.hex
	@echo "flashing $@ to the board in $(DEV)"
	@$(SUDO) $(AVRDUDE) -p $(DEVICE) -c $(PROGRAMMER) -U flash:w:$<:i -F -P $(DEV)

%.hex: %.bin
	@echo "creating hex file $@"
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.bin: %.c
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -o $@ $<

%.bin: %.cpp
	@echo "compiling $<"
	@$(CXX) $(CPPFLAGS) -o $@ $<


%.S: %.c
	@echo "creating assembly file $@"
	@$(CC) $(CFLAGS) -S -o $@ $<

%.S: %.cpp
	@echo "creating assembly file $@"
	$(CXX) $(CPPFLAGS) -S -o $@ $<

