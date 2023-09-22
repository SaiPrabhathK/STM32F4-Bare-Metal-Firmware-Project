#include "stm32f4xx.h"


#define GPIOAEN				(1U<<0)
#define PIN1 				(1U<<1)
#define LED_PIN				PIN1

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	while(1)
	{
		GPIOA->ODR |= LED_PIN;
		for (int i = 0; i < 1000000; i++);
		GPIOA->ODR &= ~(LED_PIN);
		for (int i = 0; i < 1000000; i++);
	}
}
