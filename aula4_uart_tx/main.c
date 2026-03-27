/*
 * main.c
 *
 * Created: 3/27/2026 1:54:12 PM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include "util/delay.h"

#include <xc.h>

uint8_t gMessage[3] = {200, 100, 50};

void UART_sendMessage(uint8_t * pData, int pSize) {
	uint8_t * tMsgPtr = pData;
	uint8_t tChecksum = 0;
	for(int i=0; i<pSize; i++) {
		while( (UCSR0A & (1<<UDRE0)) == 0);
		uint8_t tMessageByte = *tMsgPtr;
		tChecksum += tMessageByte;
		UDR0 = tMessageByte;
		tMsgPtr++;
	}
	while( (UCSR0A & (1<<UDRE0)) == 0);
	UDR0 = tChecksum;
}

// Função principal UART TX
int main(void) {
	UBRR0 = 103; //Configurar BAUD Rate para 9600
	UCSR0A = (0<<U2X0);
	UCSR0B = (1<<TXEN0)|(0<<UCSZ02);	// Habilita transmissor
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)	// Modo assíncrono
		   | (1<<UPM01)|(0<<UPM00)		// Habilita paridade PAR
		   | (0<<USBS0)					// 1 bit de stop
		   | (1<<UCSZ01)|(1<<UCSZ00);	// frames de 8 bits
    while(1) {
		UART_sendMessage(gMessage, 3);
		_delay_ms(10);
    }
}