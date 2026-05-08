/*
 * main.c
 *
 * Created: 5/8/2026 5:07:32 PM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "avr/interrupt.h"

uint8_t gTWIData = 5;

ISR(TWI_vect) {
	uint8_t tState = (TWSR & 0b11111000);
	switch(tState) {
		case 0x60: { //Slave receiver
			gTWIData = TWDR;
			TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		} break;
		case 0xA8: { //slave transmitter
			TWDR = gTWIData;
			TWCR = (1<<TWINT)|(1<<TWEN);
		} break;
		default: {
			TWCR = (1<<TWINT)|(1<<TWEN);
		} break;
	}
}

void TWI_slave_config() {
	TWSR = (0<<TWPS1)|(0<<TWPS0);	//Prescaler=1
	TWBR = 12;	//bit rate 400 kHz
	TWAR = (0x55<<1);
	TWCR = (1<<TWEN)|(1<<TWIE);
	sei();
}


int main(void) {
	TWI_slave_config();
	while(1) {
	}
}