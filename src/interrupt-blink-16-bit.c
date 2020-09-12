
#define F_CPU 20000000L

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB = 0b00100000;

	TCCR1B = (1 << WGM12);
	OCR1A = 19531;
	TIMSK1 = (1 << OCIE1A);

	sei();

	TCCR1B |= (1 << CS12) | (1 << CS10);

	while(1)
	{

	}
}


ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 0b00100000; 
}
