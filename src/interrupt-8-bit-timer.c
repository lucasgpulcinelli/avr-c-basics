/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program that runs the same code as input.c, but also blinks pin 10, seemingly at the same time

#define __AVR_ATmega328P__
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h> //defines the sei() macro and the correct registers
#include <util/delay.h>

//TCCR0A: Timer/counter control register A, the 8 bit timer 0 control/configuring first register
//TCCR0B: Timer/counter control register B, the 8 bit timer 0 control/configuring second register 
//OCR0A:  First output compare register for timer 0, number that will be compared with the timer to generate an interrupt 
//TIMSK0: Timer mask 0, enables an specific interrupt depending on the set bits


int main(void)
{
	//setting the interrupt part
	
	OCR0A = F_CPU * 0.01 / 1024; //timer value to get an interrupt: frequency_clock * time_wanted / preescalar
        						 //as this register is 8 bits, the max value is 255. That's the reason for such small time_wanted, the ISR wil be tweaked to get more time

	TCCR0A = 0b00000010; //mode CLEAR ON COMPARE, value said on datasheet;
	TCCR0B = 0b00000101; //preescalar 1/1024, every 1024 cicles the timer increases by 1, value said on datasheet;
	TIMSK0 = 0b00000010; //enables the interrupt for timer 0, value said on datasheet
	sei(); //set the interrupt flag, enabling interrupts



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

int extra_counter = 0; //as the interrupt happens once every 0.01s, there needs to be a counter of interrupts to get the right time to blink the LED

ISR(TIMER0_COMPA_vect) //function called when OCR0A and timer 0 become equal, aka when the timer 0 interrupt occurs
{
	if(++extra_counter >= 100)
	{
		extra_counter = 0;
		PORTB ^= 0b00000100; 
	}
}


