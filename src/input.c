/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program to toggle the builtin LED on and off each one second, if the button connected on pin 8 (in the arduino) is pressed the LED will turn off and not light until the button is unpressed


//PINX physical voltage states of all port X pins

#define __AVR_ATmega328P__
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB  = 0b00100000; //set PORTB5 (pin 13) as output and the rest as output (including pin 8)
	PORTB = 0b00000001; //PORTB0 can recive input (pin 8, Button)

	int counter = 0; //counts how many 5ms delays happend 

	while(1)
	{
		//if PINB0 is high (button IS pressed)
		if(PINB & 0b00000001) //the & operations is the logical AND for each bit, meaning getting only what PINB0 has
		{
			PORTB = 0b00000001; //set pin 13 to low, turning off the LED immedialy
			counter = 200; //sets the delay counter such that the LED will turn on as soon as the button is released
		}
		else
		{
			//the ++ increments the counter by one
			if(counter++ >= 200) //if 200 * 5ms seconds of delay happend (1s passed)
			{
				PORTB ^= 0b00100000; //^ is the logical XOR for each bit, making the LED turn on when it is off and vice-versa (0 ^ 1 = 1, 1 ^ 1 = 0)
				counter = 0; //resets the counter for the next second of delay
			}
			_delay_ms(5); //the delay is only of 5ms and not 1000ms because if the person pressed the button during the big delay it would be ignored
			
		}
	}
}
