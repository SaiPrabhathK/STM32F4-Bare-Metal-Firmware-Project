/*
 * exti.c
 *
 *  Created on: Sep 24, 2023
 *      Author: saipr
 */

#include "exti.h"

#define GPIOA_EN			(1U<<0)
#define SYSCFGEN			(1U<<14)

void pa0_exti_init(void)
{
	/* Disable global interrupts */
	__disable_irq();

	/* Enable clock access for GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA0 as input */
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);

	/* Enable clock access to SYSCFG */
	RCC->APB2ENR |= SYSCFGEN;

	/* Select PORTA for EXTI0 */
	SYSCFG->EXTICR[0] &= ~(1U<<0);
	SYSCFG->EXTICR[0] &= ~(1U<<1);
	SYSCFG->EXTICR[0] &= ~(1U<<2);
	SYSCFG->EXTICR[0] &= ~(1U<<3);

	/* Unmask EXTI0 */
	EXTI->IMR |= (1U<<0);

	/* Select falling edge trigger */
	EXTI->RTSR |= (1U<<0);

	/* Enable EXTI0 line in NVIC */
	NVIC_EnableIRQ(EXTI0_IRQn);

	/* Enable global interrupts */
	__enable_irq();
}

