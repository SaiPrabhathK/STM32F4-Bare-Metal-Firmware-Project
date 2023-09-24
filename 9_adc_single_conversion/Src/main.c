#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;

int main(void)
{

	uart2_rxtx_init();
	pa1_adc_init();
	while(1)
	{
		start_conversion();

		sensor_value = adc_read();
		printf("Sensor value : %d \n \r", (int)sensor_value);
	}
}
