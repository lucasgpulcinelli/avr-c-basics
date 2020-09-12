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
