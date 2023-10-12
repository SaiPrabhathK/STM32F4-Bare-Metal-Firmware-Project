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

static void dma_callback(void);

int main(void)
{
	char message[31] = "Hello from STM32 DMA transfer \n\r";
	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA1 as output pin */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	uart2_tx_init();
	dma1_stream6_ch4_init((uint32_t) message, (uint32_t) &USART2->DR, (uint32_t) 31);

	while(1)
	{

	}
}

static void dma_callback(void)
{
	GPIOA->ODR &= ~(LED_PIN);
}

void DMA1_Stream6_IRQHandler(void)
{
	/* Check for transfer complete interrupt */
	if(DMA1->HISR & HISR_TCIF6)
	{
		/* Clear flag */
		DMA1->HIFCR |= HIFCR_CTCIF6;

		/* Do something */
		dma_callback();
	}
}

