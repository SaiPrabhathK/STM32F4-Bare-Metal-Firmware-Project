/*
 * tim.c
 *
 *  Created on: Sep 24, 2023
 *      Author: saipr
 */

#include "tim.h"
#include "stm32f4xx.h"

#define TIM2EN				(1U<<0)
#define TIMx_CR1_CEN		(1U<<0)
#define OC2M_TOGGLE			(1U<<12) | (1U<<13) // OC1M for CH1 channel 1, OC2M for CH2 channel 2...
#define CCER_CC2E			(1U<<4)
#define GPIOA_EN			(1U<<0)
#define AFRL1_TIM			(1U<<4)


void tim2_1hz_init(void)
{
	/* Enable clock access to APB1 TIM2 */
	RCC->APB1ENR |= TIM2EN;

	/* Set prescaler value */
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

	/* Set auto-reload value */
	TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1

	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	TIM2->CR1 = TIMx_CR1_CEN;
}

void tim2_pa1_output_compare(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set pa1 mode to alternate function mode */
	GPIOA->MODER &= ~(1U<<2);
	GPIOA->MODER |= (1U<<3);

	/* Set pa1 alternate function type to TIM2_CH2 (AF1)*/
	GPIOA->AFR[0] |= AFRL1_TIM;

	/* Enable clock access to APB1 TIM2 */
	RCC->APB1ENR |= TIM2EN;

	/* Set prescaler value */
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

	/* Set auto-reload value */
	TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1

	/* Set output compare toggle mode */
	TIM2->CCMR1 = OC2M_TOGGLE;

	/* Enable TIM2_CH2 in compare mode */
	TIM2->CCER |= CCER_CC2E;

	/* Clear counter */
	TIM2->CNT = 0;

	/* Enable timer */
	TIM2->CR1 = TIMx_CR1_CEN;
}
