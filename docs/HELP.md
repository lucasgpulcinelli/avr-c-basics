#### This file has the main objetive of showing what code examples to follow and what each one covers.
All the examples are located in the src/ directory.

Note that the order of the files presented is the recommended order to follow as a beginner

The datasheet for the ATMEGA328p (used in the arduino UNO) can be found [here](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) 

All notes provided inside the "notes" subtitle in each file description are more recommended to read after fully understanding the code, and sometimes features more complex ponderations, therefore consider them an extra, and not a requirement, to work with the code presented in this project.



## main.c:
A simple skeleton code example, made to play around

### concepts:
This is the most boring AVR-C code possible: it does nothing forever! Of course, the only purpose of this file is to show what is the "skeleton" of any file used in AVR-C.

For those unfamiliar to coding in the C programming language, everything after // or between /* and */ is considered a comment, meaning it is note code, but rather a note.

All parts of the file are:
1) the copyright notice, showing what you can and cannot do with this piece of code
2) the definitions, basically giving to the compiler an alias between one and other thing (F_CPU means the same as 16000000 and AVR_ATmega328P is defined, the latter only being used to keep errors from happening in some IDEs, even if the compiler itself does not trow errors)
3) the includes, showing to the compiler that we want to use code from the avr-libc library (as defined in the file avr/io.h or utils/delay.h), the comments explain what each one does
4) the main function, where the execution of code will start, being (artificially) devided in the setup, which runs code before everything only once, similar to arduino's setup function, and the main loop, running and repeating itself after the end forever, also similar to arduino's loop function.

#### notes:       
The include directory should be somewhere in the /usr/ filesystem if avr-libc was installed via a package manager like apt, dnf or pacman.
As any code compiled in C, code execution actually begins before main, (specifically in the __ctors_end label in asm code, after a jump directly from address 0x00).

To see the dissasembly of any program, build the file with "make asm FILE=file" or use "avr-objcopy -d build/file.bin" after building the program normally, the first method outputting the assembly code in build/file.asm with a gnu assembly style and the second in a more "raw assembly" format directly in the terminal window. (do NOT try to understand the assembly code as a complete beginner)



## blink.c:
The program just blink the builtin LED on pin 13 on and off forever, a kind of hello world for embedded systems.

### concepts
The first thing that is important to understand is the binary notation in C, which is basic for better understanding: all numbers that start with 0b are binary numbers, that is, a number composed of 0s and 1s, for embedded software this notation is userful because each 1 and 0 means that a certain part of the microcontroller (a fancy word for chip) has a 5V voltage or a 0V voltage, changing the behaviour of the microcontroller in some way, in our case to first set a certain pin in the arduino as an output and to then communicate with the LED.

The registers DDRA, DDRB, DDRC, DDRD and it's corresponding PORT registers are electrical components inside the ATMEGA328p that can be controlled by software, the first four are to define the direction (meaning if we are reading or writing in this pin) and the latter to actually write to the pin itself.

Another point of interest is the _delay_ms function/macro, which will be used many times in all examples to get a human to understand what part of the code the microcontroller is running or to get timing right, as the time of each instruction is in the order of hundreds of nanoseconds (16000000 instructions per second, the CPU frequency we see in the F_CPU definition).

#### notes:
An important side note is that, as the PORTX pins are electronics inside the chip, they are NOT made to withstand a high currents or voltages (anything higher than about 10 V or 0.5 A can possibly damage a standalone chip and force a reset in the arduino), the reason high power electronics, for instance electric motors, can be controlled by an arduino is because of the interface with gates, controllers, transistors or other devices that can work with high voltages/currents and recieve logical inputs to control it's behaviour; however, the project will not tackle such issues, as they are extremely application-dependant and the hardware required can be hard to find or costly.

For the curious, the _delay_ms and _delay_us functions are just definitions for a countdown from a number (or multiple numbers) to 0, the number being defined such that the time for the CPU to process it is equal to the specified time, as the ATMEGA328p does not have an actual way of stopping the execution of code, different from modern CPUs or other microcontrollers like the sparkfun edge Apollo3, for instance. 


    
### input.c:
A simple program to show input functionality, blinking the LED on pin 13 only when a button connected on pin 8 is not pressed.

### concepts
This example is much easier to understand if the previous one makes sense: apart from PORTX and DDRX, all pins have an PINX register associated in the same way, however PINX, instead of writing or enabling a certain pin it reads the voltage, showing in software in the perfect way for if else statements (as 1 means "true", it is easy to make the logic)

Also, this example shows another part of C code essentials: bit logic. The '&', '|', '^' and '~' meand the bit wise logical AND, OR, XOR and NOT, respectively. This just means that if we have "numA & numB", just transform the numbers into binary and apply the AND operation to each bit of numA with each bit of numB. For example, 12 & 5 = 0b1100 & 0b0101 = 0b0100 = 4, because 1 & 0 = 0, 1 & 1 = 1, 0 & 0 = 0 and 0 & 1 = 0. If this sounds confusing, think what you would answear if I asked "did you go to the marked AND to school today?", you can only answer "yes" (1) if you did both things (1 for market and 1 for school), so 1 & 1 = 1; the other possibilities will all result to you responding "no". The same idea applies to OR and NOT (note that NOT has only one input instead of two). The XOR is the same as saying (numA OR numB) AND (NOT (numA AND numB)), meaning it is 1 only when there is one, and only one, input with 1.

Another C code part is the number (operator)= value, like "val += 2", meaning the same as "val = val + 2", the same for any other operation.

The last thing to talk about this code is the 5ms delay: this value is used to add responsiveness, because during a big 1000ms delay a person can press the button and release it before the delay ends, appearing sluggish and unresponsive; by contrast, a 5ms delay feels much better. Now you can be asking "Then why not having an even smaller delay?", and the answer is in the fact that the ATMEGA328p is an 8bit processor, meaning the max value for a normal integer is 255 (0b11111111), and any higher value will add some overhead, desyncing the LED faster (of course in our case it would still take a long time, but it is a good idea to always prefer to use numbers below 255 for better overall performance) 

#### notes:
Another factor to use a certain amount of delay (that does not apply for the AMEGA328p but does for more modern processors) is to save energy (when this is a concern and possible to implement, for example in the sparkfun board talked about in blink.c note 2) and leaving the processor to do other things in a multi-processes environment (like your computer or phone CPU, which has (probably) more than 300 threads to execute in only a few cores, and the last thing you want is a simple program using 100% of a core with fans working and heating up because of a button)



### interrupt-8-bit-timer.c:
covers basic interrupt handling, timers, working around 8 bit restrictions and how the datasheet is important

#### notes:
interrupts are essential for multitasking in any system or pwm signals, however heavly dependent on the microcontroller used



### interrupt-16-bit-timer.c:
covers interrupt handling with another type of register
        
#### notes:
important for the future pwm handling as the same timer can be used, while also reafirming the importance of the datasheet



### pwm.c:
covers

#### notes:
