/*
 * systick.c
 *
 *  Created on: Sep 24, 2023
 *      Author: saipr
 */

#include "systick.h"
#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL	16000
#define SYST_CSR_ENABLE		(1U<<0)
#define SYST_CSR_CLKSRC		(1U<<2)
#define SYST_CSR_COUNTFLAG	(1U<<16)

void systickDelayMs(int delay)
{
	/* Configure systick */
	/* Reload with number of clocks per millisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear systick current value register */
	SysTick->VAL = 0;

	/* Enable systick and select internal clk src */
	SysTick->CTRL = SYST_CSR_ENABLE | SYST_CSR_CLKSRC;

	for (int i = 0; i < delay; i++)
	{
		/* Wait until the COUNTFLAG is set */
		while((SysTick->CTRL & SYST_CSR_COUNTFLAG) == 0);
	}

	SysTick->CTRL = 0;
}

