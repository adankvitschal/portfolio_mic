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

ISR(INT0_vect) {
	PORTC = (1<<PORTC0); //Alterna LED
	_delay_ms(100);
	PORTC = 0;
}

int main(void) {
	DDRC = (1<<DDC0);				// configura pino PC0 como saída (LED)
	EICRA = (0<<ISC01)|(1<<ISC00);	// INT0: Ambas as bordas
	EIMSK = (0<<INT1)|(1<<INT0);	// INT0 habilitada, INT1 desabilitada
	sei();
    while(1) {
        //TODO:: Please write your application code 
    }
}