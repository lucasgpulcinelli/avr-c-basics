/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program that recieves input from USART rx pin, turning on and off the bultin LED  depending on the input

#define F_CPU 16000000L
#define BAUD  9600
#define UDRR0VAL (F_CPU/BAUD/16 - 1)
#define BUF_SIZE 64

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//same circular queue, but used to queue the read operations
char buf[BUF_SIZE];
int read_start = 0;
int read_end = 0;


int serial_read(char *c);


//reads a character, returning zero if there is nothing to read
int serial_read(char *c)
{
    //if this is the case the buffer is empty
    if(read_start == read_end)
    {
        return 0;
    }
    
    //we use the character pointer as input to let the return value be used for error checking
    *c = buf[read_start++];

    //circular queue aspect
    if(read_start == BUF_SIZE)
    {
        read_start = 0;
    }

    return 1;
}

int main(void)
{ 
    DDRB = 0b00100000; //pin 13 to output
	PORTB = 0;

    UBRR0H = (UDRR0VAL >> 8);
    UBRR0L = UDRR0VAL;

    UCSR0B = 0b10010000; //enabling both rx pin and rx interrupt
    UCSR0C = 0b00100110; //same base settings
    sei();

	while(1)
	{
        char c;
        
        if(serial_read(&c))
        {
            switch(c)
            {
            //if the character read is 1, turn on the LED 
            case '1':
                PORTB |= 0b00100000;
                break;

            //if it's 0, turn off
            case '0':
                PORTB &= 0b11011111;
                break;

            //if it's t, toggle
            case 't':
                PORTB ^= 0b00100000;
                break;

            //if it's invalid show a kind of error message (similar to a kernel panic because why not)
            default:
                for(int i = 0; i < 10; i++)
                {
                    PORTB ^= 0b00100000;
                    _delay_ms(250);
                }
                break;
            }
        }
        
        _delay_ms(100);
	}
}


//this ISR fires when there is unread data just written to UDR0
ISR(USART_RX_vect)
{
    if(read_end != read_start - 1) //seeing if an overflow would happen
    {
        //simply read the data
        buf[read_end++] = UDR0;

        //circular queue aspect
        if(read_end == BUF_SIZE)
        {
            read_end = 0;
        }
    }
    else
    {
        //reads the data but does not store it anywhere
        //this is needed because the interrupt would fire forever because UDR0 has unread data
        UDR0;
    }
}
