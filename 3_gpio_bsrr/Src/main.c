#include "stm32f4xx.h"


#define GPIOAEN				(1U<<0)

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1)
	{
		GPIOA->BSRR = (1U<<5);
		GPIOA->BSRR = (1U<<21);
	}
}
