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
int gPD2State = 0;
int gPD3State = 0;

ISR(INT0_vect) {
	gLedFlag = 1;
}

ISR(INT1_vect) {
	gLedFlag = 1;
}

ISR(PCINT2_vect) {
	
	if((PIND & (1<<PIND2)) != 0) {
		//Pino D2 está no nível lógico alto
		if(gPD2State == 0) {
			//Ocorreu uma transição no PD2
			gLedFlag = 1;
		}
		gPD2State = 1;
	} else {
		//Pino D2 está no nível lógico baixo
		gPD2State = 0;
	}
	
	if((PIND & (1<<PIND3)) != 0) {
		//Pino D3 está no nível lógico alto
		if(gPD3State == 0) {
			//Ocorreu uma transição no PD3
			gLedFlag = 1;
		}
		gPD3State = 1;
	} else {
		//Pino D3 está no nível lógico baixo
		gPD3State = 0;
	}
}

void EXTINT_config() {
	EICRA = (0<<ISC01)|(1<<ISC00)	// INT0: Ambas as bordas
		  | (1<<ISC11)|(1<<ISC10);	// INT1: Na borda de subida
	EIMSK = (1<<INT1)|(1<<INT0);	// INT0 e INT1 habilitadas	
}

void PCINT_config() {
	PCMSK2 |= (1<<PCINT18)|(1<<PCINT19);	// Habilita PCINT18 e PCINT19 (equivale pinos PD2 e PD3)
	PCICR |= (1<<PCIE2);					// Habilita grupo 2 (equivale porta D)
}

int main(void) {
	DDRC = (1<<DDC0);				// Configura pino PC0 como saída (LED)
	PCINT_config(); //se quisermos usar INT0/1, trocar para EXTINT_config
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