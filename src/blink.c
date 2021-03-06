/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

// program to toggle arduino builtin LED on and off every one second


//DDRX  = data direction register for port X, 0 for input and 1 for output
//PORTX = values for the 8 pins in port X, 0 for low current (0V) and 1 for high current (5V), no other values allowed
//as PORTA to PORTD pin numbers and arduino pin numbers do not match, see the help/arduino_layout.png file to know the port to pin correspondance for the ATMEGA328p (also with the capabilities of each pin)

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00100000; //sets the 6th pin of the B port to output and the others for input (pin 13 in arduino, with the LED builtin)
	PORTB = 0; //sets the voltage in all B port pins to low

	while(1)
	{
		PORTB = 0b00100000; //turn the 6th pin high (turns LED on)
		_delay_ms(1000); //wait for 1 second (1000 miliseconds)
		PORTB = 0b00000000; //turn all pins low (turns LED off)
		_delay_ms(1000);
	}
}
