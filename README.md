# AVR C Basics

**Basic AVR-C programs made for testing and learning purposes with the objective of learning and teaching concepts of embedded software with heavly commented examples**, tested on Arduino UNO (atmega328p) (see the docs/HELP.md file to get started).


### Dependecies to build the project:
avrdude, avr-libc, avr-gcc, make



### Build instructions: 
issue "make FILE=<name of the source file inside src/ (without the .c)>" to build the file. To flash to a board use "sudo make flash" (the superuser privileges are necessary for avrdude).


### Notes:
1) This is an early work-in-progress project, therefore parts of the project may not work on all systems
    
2) The only operating system supported until further changes is GNU/Linux, meaning most will want to use WSL or a virtual machine if a Linux-based OS is not avaliable 
