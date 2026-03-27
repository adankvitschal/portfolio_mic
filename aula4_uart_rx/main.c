/*
 * main.c
 *
 * Created: 3/27/2026 3:54:07 PM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

uint8_t gReceiveBuffer[3];

void UART_receiveMessage(uint8_t * pBuffer, int pSize) {
	uint8_t * tBufferPtr = pBuffer;
	for(int i=0; i<pSize; i++) {
		while( (UCSR0A & (1<<RXC0)) == 0); // Esperar uma mensagem chegar
		uint8_t tReceivedByte = UDR0;
		*tBufferPtr = tReceivedByte;
		tBufferPtr++;
	}
}

void UART_parseMessage(uint8_t *pMessage) {
	//Calcular checksum
	uint8_t tChecksum = 0;
	for(int i=0; i<2; i++) {
		tChecksum += pMessage[i];
	}
	if(pMessage[2] == tChecksum) {
		PORTB &= ~(1<<PORTB2); //apagar erro de checksum
		if(pMessage[0] == 0x20) {		//operação de ligar ou desligar LED0
			if(pMessage[1] == 0x01) {
				PORTB |= (1<<PORTB0);	//liga o LED
			} else
			if(pMessage[1] == 0x00) {
				PORTB &= ~(1<<PORTB0);	//desliga o LED
			}
		}
		if(pMessage[0] == 0x30) {		//operação de ligar ou desligar LED1
			if(pMessage[1] == 0x01) {
				PORTB |= (1<<PORTB1);	//liga o LED
			} else
			if(pMessage[1] == 0x00) {
				PORTB &= ~(1<<PORTB1);	//desliga o LED
			}
		}
	} else {
		//erro de checksum
		PORTB |= (1<<PORTB2); //acende led 3
	}

}

// Função principal UART RX
int main(void) {
	DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2);	// Configura pino PB0 como saída
	UBRR0 = 103;							//Configurar BAUD Rate para 9600
	UCSR0A = (0<<U2X0);
	UCSR0B = (1<<RXEN0)|(0<<UCSZ02);	// Habilita receptor
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)	// Modo assíncrono
		   | (1<<UPM01)|(0<<UPM00)		// Habilita paridade PAR
		   | (0<<USBS0)					// 1 bit de stop
		   | (1<<UCSZ01)|(1<<UCSZ00);	// frames de 8 bits
    while(1) {
		UART_receiveMessage(gReceiveBuffer, 3);
		UART_parseMessage(gReceiveBuffer);
		_delay_ms(1);
    }
}