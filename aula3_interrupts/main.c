/*
 * main.c
 *
 * Created: 3/13/2026 2:22:59 PM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000

#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

int gLedFlag = 0;

ISR(INT0_vect) {
	gLedFlag = 1;
}

ISR(INT1_vect) {
	gLedFlag = 1;
}

int main(void) {
	DDRC = (1<<DDC0);				// configura pino PC0 como saída (LED)
	EICRA = (0<<ISC01)|(1<<ISC00)	// INT0: Ambas as bordas
		  | (1<<ISC11)|(1<<ISC10);	// INT1: Na borda de subida
	EIMSK = (1<<INT1)|(1<<INT0);	// INT0 e INT1 habilitadas
	sei();
    while(1) {
        if(gLedFlag) {
	        PORTC = (1<<PORTC0);
	        _delay_ms(100);
	        PORTC = 0;
	        gLedFlag = 0;
        }
    }
}