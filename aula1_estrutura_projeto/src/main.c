/*
 * main.c
 *
 * Created: 2/27/2026 1:45:23 PM
 *  Author: Adan Kvitschal
 */ 

#include <xc.h>
#include "gpio.h"
#include "usart.h"

int main(void) {
    //Inicialização dos periféricos
	GPIO_initialize();
	USART_initialize();
    while(1) {
        GPIO_blinkLed();
		USART_send();
    }
}