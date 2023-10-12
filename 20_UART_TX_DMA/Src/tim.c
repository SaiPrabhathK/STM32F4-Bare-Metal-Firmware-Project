/*
 * tim.c
 *
 *  Created on: Sep 24, 2023
 *      Author: saipr
 */

#include "tim.h"
#include "stm32f4xx.h"

#define TIM2EN				(1U<<0)
#define TIM3EN				(1U<<1)
#define TIMX_CR1_CEN		(1U<<0)
#define OC2M_TOGGLE			(1U<<12) | (1U<<13) // OC1M for CH1 channel 1, OC2M for CH2 channel 2...
#define CCER_CC2E			(1U<<4)
#define CCER_CC1E			(1U<<0)
#define GPIOA_EN			(1U<<0)
#define AFRL1_TIM2			(1U<<4)
#define AFRL6_TIM3			(1U<<25)
#define CCER_CC1S			(1U<<0)

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
	TIM2->CR1 = TIMX_CR1_CEN;
}

void tim2_pa1_output_compare(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set pa1 mode to alternate function mode */
	GPIOA->MODER &= ~(1U<<2);
	GPIOA->MODER |= (1U<<3);

	/* Set pa1 alternate function type to TIM2_CH2 (AF1)*/
	GPIOA->AFR[0] |= AFRL1_TIM2;

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
	TIM2->CR1 = TIMX_CR1_CEN;
}

void tim3_pa6_input_capture(void)
{
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOA_EN;

	/* Set PA6 to alternate function */
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/* Set PA6 alternate function type to TIM3_CH1 (AF2) */
	GPIOA->AFR[0] |= AFRL6_TIM3;

	/* Enable clock access to tim3 */
	RCC->APB1ENR |= TIM3EN;

	/* Set Prescaler */
	TIM3->PSC = 16000 - 1; // 16 000 000 / 16000

	/* Set CH1 to input capture */
	TIM3->CCMR1 = CCER_CC1S;

	/* Set CH1 to capture at rising edge */
	TIM3->CCER = CCER_CC1E;

	/* Enable TIM3 */
	TIM3->CR1 = TIMX_CR1_CEN;
}
