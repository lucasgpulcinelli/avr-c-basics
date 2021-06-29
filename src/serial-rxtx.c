/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/


//program that echos the USART input to output with a formatted message

#define F_CPU 16000000L
#define BAUD 9600
#define UDRR0VAL (F_CPU/BAUD/16 - 1)
#define BUF_SIZE 32 //smaller buffer size to compensate the need for two buffers

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

//as we need to both read and write, two buffers are necessary
char buf_w[BUF_SIZE];
int write_start = 0;
int write_end = 0;
char buf_r[BUF_SIZE];
int read_start = 0;
int read_end = 0;


int serial_append(char c);
int serial_write(char* msg);
int serial_read(char *c);
int serial_read_str(char *msg, int max_size);


int serial_append(char c)
{
    if(!(UCSR0A & (1 << UDRE0)))
    {
        buf_w[write_end++] = c;

        if(write_end == BUF_SIZE)
        {
            write_end = 0;
        }
        else if(write_start == write_end)
        {
            return 1;
        }
    }
    else
    {
        UDR0 = c;
    }

    return 0;
}

int serial_write(char* msg)
{
    for(int i = 0; i < strlen(msg); i++)
    {
        if(serial_append(msg[i]) != 0)
        {
            return 1;
        }
    }
    return 0;
}

int serial_read(char *c)
{
    if(read_start == read_end)
    {
        return 0;
    }
    
    *c = buf_r[read_start++];

    if(read_start == BUF_SIZE)
    {
        read_start = 0;
    }

    return 1;
}

//reads a whole string of size max_size (including the null character) unless a tab character is reached or the buffer empties
//returns 0 if either max_size is reached or a tab character is encountered (exit conditions), -1 if nothing could be read and
//the index of the last write when the buffer empties during the loop
int serial_read_str(char *msg, int max_size)
{
    int i;
    for(i = 0; i < max_size-1; i++)
    {
        if(!serial_read(msg+i))
        {
            return (i == 0)?-1:i;
        }
        //we use tab characters instead of newlines because the code breaks for some reason,
        //i believe it has something to do with minicom
        else if(msg[i] == '\t')
        {
            // we *need* to null terminate when done bacause strlen needs it to determine the end of string in the serial_write function
            msg[i] = '\0';
            return 0;
        }
    }
    msg[max_size-1] = '\0';
    return 0;

}

int main(void)
{ 

    UBRR0H = (UDRR0VAL >> 8);
    UBRR0L = UDRR0VAL;

    UCSR0B = 0b11011000; //enabling rx pin, tx pin, rx interrupt and tx interrupt 
    UCSR0C = 0b00100110;
    sei();

    serial_write("Hello!\n"); //this just shows to the user that the main loop started
    
    while(1)
    {
        char msg[16];

        int i = 0;
        int ret;

        //the function serial_read_str does not block execution, but is written in a way that makes it easy to do so if wanted
        while((ret=serial_read_str(msg+i, 16-i)))
        {
            if(ret != -1)
            {
                i += ret;
            }
        }

        serial_write("\nWow! You said ");
        serial_write(msg);
        serial_write("!\n");

        _delay_ms(3000);
    }
}

ISR(USART_TX_vect)
{
    if(write_start != write_end)
    {
        UDR0 = buf_w[write_start++];

        if(write_start == BUF_SIZE)
        {
            write_start = 0;
        }
    }
}

ISR(USART_RX_vect)
{
    if(read_end != read_start - 1)
    {
        buf_r[read_end++] = UDR0;

        if(read_end == BUF_SIZE)
        {
            read_end = 0;
        }
    }
    else
    {
        UDR0;
    }
}
