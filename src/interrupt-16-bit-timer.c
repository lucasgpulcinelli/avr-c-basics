/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program that runs the same code as interrupt-8-bit-timer.c, 
//however the timer used is 16 bit instead of 8 bit, making the ISR simpler because no extra counters will be needed

#define __AVR_ATmega328P__
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>

//TCCR1A: Timer/counter control register A, the 8 bit timer 1 control/configuring first register (not used for the purposes of this program)
//TCCR1B: Timer/counter control register B, the 8 bit timer 1 control/configuring second register 
//OCR1A:  First output compare register for timer 1, number that will be compared with the timer to generate an interrupt (in this case is a 16 bit register so the max value is 65535, not 255)
//TIMSK1: Timer mask 1, enables an specific interrupt depending on the set bits


int main(void)
{
	//setting the interrupt part
	
	OCR1A = F_CPU * 1 / 1024; //in this case we won't need to worry about a new counter because F_CPU / 1024 = 15625 < 65535, so an overflow won't occur

	TCCR1B = 0b00001000 | 0b00000101; //will set the CTC (clear timer on compare) mode (0x08), and with a preescalar of 1/1024 (0x05), as said in datasheet
	TIMSK1 = 0b00000010; //enable the timer 1 interrupt, starting the timer after sei() is called
	sei();



	//input.c code, but with pin 10 (PORTB2) as output too
	
	DDRB  = 0b00100100;
	PORTB = 0b00000001;

	int counter = 0;

	while(1)
	{
		if(PINB & 0b00000001)
		{
			PORTB = 0b00000001;
			counter = 200;
		}
		else
		{
			if(counter++ >= 200)
			{
				PORTB ^= 0b00100000;
				counter = 0;
			}
			_delay_ms(5);
		}
	}
}


ISR(TIMER1_COMPA_vect) //function called when OCR1A and timer 1 become equal, aka when the timer 1 interrupt occurs
{
	PORTB ^= 0b00000100; //much simpler interrupt service routine because an extra counter was not needed, leading to slightly more efficient code
}