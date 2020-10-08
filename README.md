# AVR C Basics

Basic AVR-C programs made for testing and learning purposes, tested on Arduino UNO (atmega328p), with the objective of learning and teaching concepts of embedded software, with heavly commented examples (see the help/HELP file to get started)


Dependecies to build the project:
    avrdude
    avr-libc
    avr-gcc
    make


Build instructions: 
    issue "make FILE=<name of the source file inside src/ (without the .c)>" to build the file. To flash to a board use "sudo make flash" (the superuser privileges are necessary for avrdude).


Note:
    This is an early work-in-progress project, therefore parts of the project may not work on all systems 