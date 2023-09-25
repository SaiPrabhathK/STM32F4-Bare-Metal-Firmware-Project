#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIOA_EN			(1U<<0)
#define GPIOA_PIN1			(1U<<1)
#define LED_PIN				GPIOA_PIN1

char key;

static void uart_callback(void);

int main(void)
{
	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA1 as output pin */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	uart2_rxtx_interrupt_init();

	while(1)
	{

	}
}

static void uart_callback(void)
{
		key = USART2->DR;
		if(key != 'P')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~(LED_PIN);
		}
		printf("%c \n\r", key);
}

void USART2_IRQHandler(void)
{
	/* Check if RXNE is set */
	if (USART2->SR & SR_RXNE)
	{
		/* Do Something */
		uart_callback();
	}
}

