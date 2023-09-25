#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

int main(void)
{
	tim2_pa1_output_compare();

	while(1)
	{

	}
}
