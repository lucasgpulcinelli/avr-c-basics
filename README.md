# AVR C Basics

**Basic AVR-C programs made for testing and learning purposes with the objective of learning and teaching concepts of embedded software with heavly commented examples**, tested on Arduino UNO (atmega328p) (see the docs/HELP.md file to get started).


### Dependecies to build the project:
avrdude, avr-libc, avr-gcc, make
avr-gcc-c++ or avr-g++ if one wants to use c++ in projects


### Build instructions: 
After cloning the repository and installing dependencies, use a terminal to the root of the project (directy inside a folder named avr_c_basics) issue "make FILE=<name of the source file inside src/ (without the .c)>" to build an specific file. To flash to a board use "make flash" (the prompt for a password is necessary for avrdude).


### Notes:
1) It is not necessary for a reader to have any familiarity with C or arduino coding, as most of the basic C concepts and microcontroller essentials will be present as comments in the actual code, however, it can be harder to understand some parts if the reader needs to learn both the syntax and the connection with hardware, therefore following after learning basic coding skills is recommended.

2) This is an early work-in-progress project, therefore parts of the project may not work on all systems
    
3) The only operating system supported until further changes is GNU/Linux, meaning most will want to use WSL or a virtual machine if a Linux-based OS is not avaliable 
