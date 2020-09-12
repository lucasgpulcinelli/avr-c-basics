/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

#define F_CPU 20000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00100000;
	PORTB = 0;

	while(1)
	{
		PORTB ^= 0b00100000;
	}
}
