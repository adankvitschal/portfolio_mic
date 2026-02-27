/*
 * gpio.c
 *
 * Created: 27/02/2026 13:59:46
 *  Author: Adan Kvitschal
 */ 

#include "gpio.h"
#include <xc.h>

void GPIO_initialize() {
	DDRB = (1<<DDB0); //configura a pino PB0 como sa�da
}

void GPIO_blinkLed() {
	PORTB = (1<<PORTB0); //aciona o pino PB0
}