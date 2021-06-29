/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program that writes via USART using an efficient interrupt method, first writing "Hello World!" and then "Goodbye World..."

#define F_CPU 16000000L
#define BAUD 9600
#define UBRR0VAL (F_CPU/BAUD/16-1)
#define BUF_SIZE 64 //write buffer size, big but that's not a problem

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h> //used for strlen function

//this buffer is actually a very simple circular queue
char buf[BUF_SIZE];  //buffer declaration needs to be global because of the ISR
int write_start = 0; //the index of the next write operation of UDR0
int write_end = 0;   //the index of the last write operation requested


int serial_append(char c);
int serial_write(char* msg);


//function to append a character to the buffer, returns nonzero if the buffer is full
int serial_append(char c)
{

    //the buffer is full when, after this request, the last write and the next are the same index
    if(write_start == write_end+1)
    {
        return 1; //signals that the write couldn't be queued
    }
    //UDRE0 is set when the UDR0 register is ready to recieve new data,
    //so the inverse is when we need to write the request to the buffer
    if(!(UCSR0A & (1 << UDRE0)))
    {
        //queue the request
        buf[write_end++] = c;

        //circular queue aspect, when we reach the end wrap around the buffer
        if(write_end == BUF_SIZE)
        {
            write_end = 0;
        }
    }
    else
    {
        //as the interrupt only happens after a write operation ends (look at the ISR comments),
        //we need to write to UDR0 outside of the interrupt otherwise it would never fire
        UDR0 = c;
    }

    return 0;
}

//writes a whole null terminated string to the output, basically a print function
//returns nonzero if the buffer became full after the request, very rudimentary but works
int serial_write(char* msg)
{
    //not at all complex, just loop and check if the buffer is full
    for(int i = 0; i < strlen(msg); i++) 
    {
        if(serial_append(msg[i]) != 0)
        {
            return 1;
        }
    }
    return 0;
}

int main(void)
{ 

    UBRR0H = (UBRR0VAL >> 8);
    UBRR0L = UBRR0VAL;

    UCSR0B = 0b01001000; //same as simple example, but with the tx interrupt enabled
    UCSR0C = 0b00100110; //same as simple example
    sei(); //enable interrupts (tx interrupt)

	while(1)
	{
        serial_write("Hello World!\n");
        _delay_ms(1000);
        serial_write("Goodbye World...\n");
        _delay_ms(1000);
	}
}

//this ISR fires when the last write operation ended, meaning the buffer is ready to be written again
//if UDR0 was never written to begin with or not written in the interrupt itself it stops firing until another UDR0 write happens
ISR(USART_TX_vect)
{
    //if these are equal the buffer no buffered requests happend, so nothing to do
    if(write_start != write_end)
    {
        UDR0 = buf[write_start++];

        //circular queue aspect
        if(write_start == BUF_SIZE)
        {
            write_start = 0;
        }
    }
}
