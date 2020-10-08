/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

#define __AVR_ATmega328P__
#define F_CPU 20000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int duty_cycle = 0; //

int main(void)
{
	DDRD = 0b01000000; //sets pin X to output

	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);

	OCR0A = duty_cycle;

	sei(); //enable interrupts (ISR)
	TCCR0B = (1 << CS00) | (1 << CS02);

	while(1)
	{
		_delay_ms(50);
		if((duty_cycle += 5) >= 255)
		{
			duty_cycle = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = duty_cycle;
}
