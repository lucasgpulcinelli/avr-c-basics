// program to toggle arduino builtin LED on and off every one second



//DDRX  = data direction register for port X
//PORTX = values for the 8 pins in port X


// defines the cpu frequency (used in the delay function)
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00100000; //sets the 6th B port to output and the others for input (pin 13, with the LED builtin)
	PORTB = 0; //sets the current in all B port to LOW

	while(1)
	{
		PORTB ^= 0b00100000; //toggle pin 13 (LED) from high to low and low to high with xor
		_delay_ms(1000); //wait for 1 second
	}
}
