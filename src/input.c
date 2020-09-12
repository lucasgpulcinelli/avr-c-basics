//program to toggle the builtin LED on and off each one second, if the button connected on pin 8 is pressed the LED will not light until the button is disconnected


//PINX physical voltage states of all port X pins

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x20; //pin 13 output (LED) and 8 input
	PORTB = 0x01; //pin 8 can recive input (Button)

	while(1)
	{
		// mask needed to get only what pin 8 says
                // inverted because the signal will be high when the button is pressed
		if(!(PINB & 0x01))
		{
			PORTB ^= 0x20;
			_delay_ms(1000);
		
		}else
		{
			PORTB = 0x01;
		}
	}
}
