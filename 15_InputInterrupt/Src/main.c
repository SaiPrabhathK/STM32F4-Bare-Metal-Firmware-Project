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

int timestamp = 0;

static void exti_callback(void);

int main(void)
{
	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA1 as output pin */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	pa0_exti_init();
	uart2_tx_init();

	while(1)
	{

	}
}

static void exti_callback(void)
{
	printf("BTN Pressed... \n\r");
	GPIOA->ODR ^= LED_PIN;
}

void EXTI0_IRQHandler(void)
{
	if((EXTI->PR & LINE0) != 0)
	{
		/* Clear PR flag */
		EXTI->PR |= LINE0;

		/* Do something.... */
		exti_callback();
	}
}
