#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"



int main(void)
{
	uart2_tx_init();
	while(1)
	{
		printf("Hello from STM32F407VET6 \n\r");
	}
}
