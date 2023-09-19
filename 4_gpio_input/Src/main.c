#include "stm32f4xx.h"


#define GPIOAEN				(1U<<0)
#define PIN1				(0U<<1)
#define LED_PIN				PIN1 // LED D2 active low

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	while(1)
	{
		GPIOA->BSRR = LED_PIN;
		for(int i = 0; i < 100000000; i++) {}

		GPIOA->BSRR = (1U<<17);
		for(int i = 0; i < 100000000; i++) {}
	}
}
