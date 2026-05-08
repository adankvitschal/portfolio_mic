/*
 * main.c
 *
 * Created: 5/8/2026 3:57:56 PM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void TWI_master_config() {
	//DDRC = (1<<DDC4)|(1<<DDC5);
	TWSR = (0<<TWPS1)|(0<<TWPS0);	//Prescaler=1
	TWBR = 12;	//bit rate 400 kHz
	TWCR = (1<<TWEN);
}

void TWI_master_write_byte(uint8_t pAddress, uint8_t pData) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Enviar condição de start
		
	while ((TWCR & (1<<TWINT)) == 0); //Esperar conclusão

	TWDR = (pAddress<<1) | 0; // 1 para leitura e  0 para escrita
	TWCR = (1<<TWINT)|(1<<TWEN); //limpar twint para próximo passo
	
	while((TWCR & (1<<TWINT)) == 0); //Esperar conclusão
	
	uint8_t tState = TWSR & 0b11111000;
	
	switch(tState) {
		case 0x18:	break; //ack recebido
		case 0x20:	break; // nenhum ack recebido
		default:	break;//outros erros		
	}
	
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); //Enviar condição de stop
}

int main(void) {
	TWI_master_config();
	_delay_ms(1000);
    while(1) {
        TWI_master_write_byte(0x55, 'a');
		_delay_ms(1000);
    }
}