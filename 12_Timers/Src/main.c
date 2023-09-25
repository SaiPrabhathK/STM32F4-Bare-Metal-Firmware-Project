#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOA_EN			(1U<<0)
#define PIN1				(1U<<1)
#define LED_PIN				PIN1

int main(void)
{
	RCC->AHB1ENR |= GPIOA_EN;

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	uart2_tx_init();
	tim2_1hz_init();

	while(1)
	{
		/* Wait for UIF */
		while(!(TIM2->SR & TIMx_SR_UIF));

		/* Clear UIF */
		TIM2->SR &= ~(TIMx_SR_UIF);

		printf("A second passed !! \n\r");
		GPIOA->ODR ^= LED_PIN;
	}
}
