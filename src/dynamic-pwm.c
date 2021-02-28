/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program tha slowly increases an LED (connected on pin 6) brightness during 5 seconds then suddently turns it off, repeating the process forever


#define __AVR_ATmega328P__
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int duty_cycle = 0; //value from 0 to 255 proportional to the percetage of time (for this timer cicle) that the output will be 5V

int main(void)
{
	TCCR0A = 0b10000011; //fast pwm with clear OC0A mode, meaning as soon as the timer hits OCR0A the output will turn to 0V
	TCCR0B = 0b00000001; //prescaler of 1/1, leading to more accuracy

	OCR0A = duty_cycle;  //at first, the LED will be off (0% of the time on)

	TIMSK0 = 0b00000001; //enable overflow interrupt, triggering when timer0 = 255 (max value)
	sei();				 //enable global interrupts

	DDRD = 0b01000000;   //setting pin6 to output

	while(1)
	{
		if(duty_cycle >= 250)
		{
			duty_cycle = 0;
		}
		duty_cycle++;
		_delay_ms(20); //total delay time is 250 loops * 20ms delay per loop = 5000ms = 5s
	}
}


ISR(TIMER0_OVF_vect)    //interrupt for timer0 overflow, meaning when the timer is equal to the max value
{
	OCR0A = duty_cycle; //just update 0CR0A
}
