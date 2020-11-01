#### This file has the main objetive of showing what code examples to follow and what each one covers.
All the examples are located in the src/ directory.

Note that the order of the files presented is the recommended order to follow as a beginner

The datasheet can be found [here](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) 



### main.c:
covers basic embedded code structure and essential include files

#### notes:       
a simple skeleton code example, made to play around   



### blink.c:
covers basic digital output and data direction registers

#### notes:
just blink an LED on and off forever, a kind of hello world for embedded systems 


    
### input.c:
covers basic logical operations (AND and XOR), digital input and making the code more responsive to the user

#### notes:
creating a responsive input while other events still happen is not that simple, pretty good to teach many basic ideas



### interrupt-8-bit-timer.c:
covers basic interrupt handling, timers, working around 8 bit restrictions and how the datasheet is important

#### notes:
interrupts are essential for multitasking in any system, however heavly dependent on the microcontroller used



### interrupt-16-bit-timer.c:
covers interrupt handling with another type of register
        
#### notes:
important for the future pwm handling as the same timer can be used, while also reafirming the importance of the datasheet



### pwm.c:
covers

#### notes:
