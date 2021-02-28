/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//program that writes "Hello, World!" via the USART tx pin, usable via usb on arduino uno
//no error checking is made, this is the simplest possible USART data writing example

//UBRR0H and UBRR0L         high and low bytes of UBRR0, the baud rate register
//UCSR0A, UCSR0B and UCSR0C USART configuration registers
//UDR0                      the read/write register for USART usage

#define __AVR_ATmega328P__
#define F_CPU 16000000L
#define BAUD 9600                   //Baud rate, the speed (in bits per second) of data transferred
#define UBRR0VAL (F_CPU/BAUD/16-1)  //Formula given by datasheet for the value of UBRR0 register

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{ 

    UBRR0H = (UBRR0VAL >> 8); //the value need to be split between H and L bytes because the register is only 12 bits, not 16
    UBRR0L = UBRR0VAL;

                              //nothing is set in UCSR0A because we want the default settings, and most bits are status bits
    UCSR0B = 0b00001000;      //enable the tx pin for USART usage
    UCSR0C = 0b00100110;      //enable even parity (simple error checking) and set 8 bit USART, as opposed to the max 9 and min 5 bits


    char* msg = "Hello, World!\n";

	while(1)
	{
        //loop for every letter
        for(int i = 0; i < 14; i++)
        {
            UDR0 = msg[i]; //just write the data that will be sent
            _delay_ms(50); //and wait a while for the actual data sending, this is inefficient, but works for now
        }
        _delay_ms(1000);
	}
}
