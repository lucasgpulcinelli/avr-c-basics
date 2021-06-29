/*
Copyright (c) 2020, Lucas Eduardo Gulka Pulcinelli
This file is licensed under the BSD-3-Clause ("New" or "Revised" BSD) License.
*/

//simply beeps a buzzer (connected on pin 13) with an increasing frequency for half a second, then sleeps half a second, then repeats forever


#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void play_note(const unsigned int freq, const float seconds); //function to set the timer properties such that a note is played for an specific amount of time
unsigned long int freqs[6] = {262, 294, 329, 349, 392, 440};  //all the frequencies that will be played (from C3 to A4)
unsigned long long int notes_count = 0;                       //the amount of times the interrupt will occur, usigned long long int to make it the highest possible integer, as this number can be huge depending on the time and frequency


int main(void)
{
    DDRB = 0b00100000;   //sets pin 13 to output

    TCCR2A = 0b00000011; //fast pwm mode with the max value equal to ORC2A (in practice the same as CTC mode with the TIMER2_COMPA interrupt, but this shows another way to do it)
    TCCR2B = 0b00001101; //prescaler of 1/128
    //of course, setting an specific prescaler and not being able to change it narrows the amount of frequencies we can use, but it is fine in our case

    TIMSK2 = 0b00000001; //enable timer2 overflow interrupt
    sei();               //enable global interrupts

    OCR2A = 0;
    while(1)
    {
        for(int i = 0; i < 6; i++)    //loops from the first to last frequency in the freqs array
        {
            play_note(freqs[i], 0.5); //one very important aspect of this code: this function only sets the frequency and time for the interrupt, so the CPU can do another computation while playing music!
            _delay_ms(1000);          //in our case we will not use this functionality to keep everything simple, but for an arduino game this would be necessary, otherwise the CPU would only play music and not run the game itself
        }
    }

}

ISR(TIMER2_OVF_vect)
{
    if(notes_count > 0)
    {
        PORTB ^= 0b00100000; //once more the port is hard coded, depending on the application and flexibility wanted this can be changed
        notes_count--;       //just counts the amount of interrupts we have left
    }
    else
    {
        PORTB = 0;           //does nothing for the actual sound, as normally buzzers generate it when voltage changes (goes from high to low), but this turns off the builtin LED to make obvious when we are sleeping
    }
    
}



void play_note(const unsigned int freq, const float seconds)
{
    OCR2A = 62500 / freq; //the OCR2A value is F_CPU / (2 * prescaler * frequency), but the value F_CPU/(2 * prescaler) is precomputed
    notes_count = (seconds <= 0) ? 0: (freq * 2) * seconds; //the formula for the amount of interrupts is the frequency (whole waves per second) times 2 (interrupts per wave, because a wave has a high part and a low part) times the amount of seconds
}
