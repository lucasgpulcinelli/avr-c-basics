/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//defines, definitions used in the included files or in the actual code for easier understanding
#define __AVR_ATmega328P__ //used in the avr/io.h file, defines the microcontroller cpu
#define F_CPU 16000000 //defines the cpu frequency, used in the ultil/delay.h file

//includes, files to include for basic and/or userful functions and definitions
#include <avr/io.h> //basic input/output include, essential for an userful program
#include <util/delay.h> //used for the delay function, userful to define the duty cycle

int main(void) //the special main function, will be the first user defined code to run (usually)
{
	//setup, will run when board is powered up or a reset happens

	while(1)
	{
		//main loop, will run after setup repeating itself until a power off, reset or an eventual interrupt (more on that later) happens
	}
}
