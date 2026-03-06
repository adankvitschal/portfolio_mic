/*
 * main.c
 *
 * Created: 3/6/2026 2:36:35 PM
 *  Author: Adan Kvitschal
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

/**
 *	@brief Pisca um led ligado ao pino PC2 enquanto a chave
 *    ligada ao pino PD3 estiver pressionada.
 */

void atividade1() {
	DDRC |= (1<<DDC2); // Configurar o pino PC2 como saída
	DDRD &= (1<<DDD3); // Configura pino PD3 como entrada
    while(1) {
        if((PIND & (1<<PIND3)) != 0) { //Ler o valor da chave (PD3)
			//Chave pressionada
			PORTC |= (1<<PORTC2); //acende led
			_delay_ms(300);
			PORTC &= ~(1<<PORTC2); //apaga led
			_delay_ms(700);
		} else {
			//Chave aberta
			PORTC &= ~(1<<PORTC2); //apaga led
		}
	}
}

/**
 * @brief Controla 6 leds (PB0 a PB5) em uma lógica de "pinheirinho de natal"
 *    enquanto a chave (PD3) está acionada
 */

void atividade2() {
	DDRD &= (1<<DDD3); // Configura pino PD3 como entrada
	//Configurar pinos PB0-PB5 como saída
	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	uint8_t tState = 0b00010101; //Guarda estado de acionamento dos LEDs
	while(1) {
		tState = tState << 1;
		if(tState == 0b10101000) tState = 0b00010101;
        if((PIND & (1<<PIND3)) != 0) { //Ler o valor da chave (PD3)
			//Chave fechada
			PORTB = tState;
		} else {
			//Chave aberta
			PORTB = 0;
		}
		_delay_ms(200);
	}
}

int main(void) {
	atividade2();	
}