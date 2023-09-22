#include "stm32f4xx.h"


#define GPIOAEN				(1U<<0)

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	while(1)
	{
		GPIOA->BSRR |= (1U<<17);
		for(int i = 0; i < 1000000; i++);
		GPIOA->BSRR |= (1U<<1);
		for(int i = 0; i < 1000000; i++);
	}
}
