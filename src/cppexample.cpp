
extern "C"
{
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
}


class AvrBlink
{      
    public:
        AvrBlink()
        {
            DDRB = 0b00100000;
            PORTB = 0;
        }

        void blink(void)
        {
            PORTB ^= 0b00100000;
            _delay_ms(500);
        }
};

int main()
{
    AvrBlink avr;

    while(1)
    {
        avr.blink();
    }
}
