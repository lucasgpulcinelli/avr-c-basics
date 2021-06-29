/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program tha blinks an LED (connected on pin 6) with half the brightness it would normally have
//also works perfectly with a low power DC motor, the speed difference is easier to see


//OC0A: value that is connected to pin 6 and is the output for this pin when pwm on timer0 is used 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
    //pwm setting part
	TCCR0A = 0b10000011; //fast pwm with clear OC0A mode, meaning as soon as the timer hits OCR0A the output will turn to 0V
    TCCR0B = 0b00000001; //prescaler of 1/1, leading to more accuracy
	//because PD6 will be used for pwm output, it's basic I/O functionality will be overriden in the previous line of code


	//as only some special pins have access to pwm (only those with a ~ by the pin number in the arduino UNO), the buitin LED cannot be used as it does not have this capability
	//the OC0A is used because it corresponds to PD6, all pwm pins have an output compare register associated (can be seen in docs/arduino_layout.png file)
    DDRD = 0b01000000;   //setting pin 6 to output

	while(1)             //we could run the blink part in an interrupt (to make the main loop run something more important) by controlling the prescaler and with an extra counter (like in interrupt-8-bit-timer.c) but it is harder to understand how pwm works so it is better to keep it simple 
	{
    	OCR0A = 127;     //half of 255 - 1, meaning the LED will turn on for half of the time
        _delay_ms(1000);
        OCR0A = 0;
        _delay_ms(1000);
    }
}

