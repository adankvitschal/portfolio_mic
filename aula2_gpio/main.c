/*
 * main.c
 *
 * Created: 3/6/2026 2:36:35 PM
 *  Author: Adan Kvitschal
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

/* O que este código faz:
 *    Pisca um led ligado ao pino PC2 enquanto a chave
 *    ligada ao pino PD3 estiver pressionada.
 */

int main(void) {
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