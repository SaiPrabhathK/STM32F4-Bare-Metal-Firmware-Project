#include "stm32f4xx.h"


#define GPIOAEN				(1U<<0)
#define PIN1				(1U<<1)
#define LED_PIN				PIN1 // USER LED D2 active low, sink mode

#define PIN0				(1U<<0)
#define BUTTON_PIN			PIN0 // USER BUTTON is active high

int main(void)
{
	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA1 as output pin */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER &= ~(1U<<3);

	/* Set PA0 as input pin */
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);

	while(1)
	{
		/* Check if BUTTON is pressed, initial state is low, becomes high when pressed, detect a high signal to
		 * detect a press */
		if(GPIOA->IDR & BUTTON_PIN)
		{
			/* Turn off LED when BUTTON is pressed*/
			GPIOA->BSRR |= LED_PIN;
		}
		else
		{
			/* Turn on LED when BUTTON is not pressed/released*/
		GPIOA->BSRR |= (1U<<17);
		}
	}
}
