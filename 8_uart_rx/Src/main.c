#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOA_EN			(1U<<0)
#define GPIOA_PIN1			(1U<<1)
#define LED_PIN				GPIOA_PIN1

char key;

int main(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA1 as output pin */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	uart2_rxtx_init();
	while(1)
	{
		key = uart2_read();
		if(key == 'P')
		{
			GPIOA->ODR &= ~(LED_PIN);
		}
		else
		{
			GPIOA->ODR |= LED_PIN;
		}
	}
}
