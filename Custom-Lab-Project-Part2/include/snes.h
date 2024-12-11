#ifndef _SNES_H_
#define _SNES_H_

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <util/delay.h>
#include "helper.h"
#include "periph.h"
#include "serialATmega.h"

// Sends 16 pulses (16.63 ms), only care for 1-12 (12 bits)
//https://gamesx.com/controldata/snesdat.htm

void SNES_pinSet() { 
//A2 latch
//A1 clock
//A0 serial data
    PORTC = SetBit(PORTC, 0, 0);
    PORTC = SetBit(PORTC, 1, 0);
    PORTC = SetBit(PORTC, 2, 0);
    DDRD = ~PORTD;
}

int SNES_IDLE() { //high means button is not depressed
    int input = 0xFFFF;

    //toggle latch
    PORTC = SetBit(PORTC, 2, 1);
    PORTC = SetBit(PORTC, 1, 0);


    input = SetBit(input, 0, ADC_read(0)); //1st input, B, toggles at latch

    PORTC = SetBit(PORTC, 2, 0);

    // input = SetBit(input, 0, ADC_read(0)); //1st input, B, toggles at latch

    for(int i = 0; i < 16; i++) {
        PORTC = SetBit(PORTC, 1, 1); //clock toggle
        input = SetBit(input, i, ADC_read(0));
        PORTC = SetBit(PORTC, 1, 0);
    }

    return input;
}

/*
0:B
1:B
2:Y
3:Select
4:Start      
5:up
6:down
7:left
8:right
9:A
10:X
11:L
12:R
*/

#endif