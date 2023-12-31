/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
//Buses carry the clock to peripherals
// APB - Advanced Peripheral Bus
// AHB - Advanced High Performance Bus
// AHB is faster than APB
// LED Location?
// Port:
// Pin:

#include <stdint.h>

#define PERIPH_BASE_ADDR 	(0x40000000UL)
#define AHB1_PERIPH_OFFSET 	(0x00020000UL)
#define AHB1_PERIPH_BASE 	(PERIPH_BASE_ADDR + AHB1_PERIPH_OFFSET)

#define GPIOA_OFFSET 		(0x00000000UL)
#define GPIOA_BASE 			(AHB1_PERIPH_BASE + GPIOA_OFFSET)

//RCC - Reset and Clock Control
#define RCC_OFFSET 			(0x3800UL) //Same as 0x00003800 -
//taking out leading zeros doesn't affect the value in binary
#define RCC_BASE 			(AHB1_PERIPH_BASE + RCC_OFFSET)

// Bit 0 GPIOAEN: IO port A clock enable
#define GPIOAEN 			(1UL<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define __IO 				volatile
/*
 * (1U<<10) //Set bit 10 to 1
 * &=~(1U<<11) //Set bit 11 to 1 */

typedef struct
{
	__IO uint32_t CR; 		// RCC clock control register, Address offset: 0x00
	__IO uint32_t PLLCFGR; 	// RCC PLL configuration register, Address offset: 0x04
	__IO uint32_t CFGR;		// RCC clock configuration register, Address offset: 0x08
	__IO uint32_t CIR;		// RCC clock interrupt register, Address offset: 0x0C
	__IO uint32_t AHB1RSTR;	// RCC AHB1 peripheral reset register, Address offset: 0x10
	__IO uint32_t AHB2RSTR;	// RCC AHB2 peripheral reset register, Address offset: 0x14
	__IO uint32_t AHB3RSTR; // RCC AHB3 peripheral reset register, Address offset: 0x18
	uint32_t RESERVED0;		// Reserved, 0x1C
	__IO uint32_t APB1RSTR;	// RCC APB1 peripheral reset register, Address offset: 0x20
	__IO uint32_t APB2RSTR; // RCC APB2 peripheral reset register, Address offset: 0x24
	uint32_t RESERVED1[2];	// Reserved, 0x28
	__IO uint32_t AHB1ENR;	// RCC AHB1 peripheral clock register, Address offset: 0x30
	__IO uint32_t AHB2ENR;	// RCC AHB2 peripheral clock enable register, Address offset: 0x34
	__IO uint32_t AHB3ENR;	// RCC AHB3 peripheral clock enable register, Address offset: 0x38
	uint32_t RESERVED2;		// Reserved, 0x3C
	__IO uint32_t APB1ENR;	// RCC APB1 peripheral clock enable register, Address offset: 0x40
	__IO uint32_t APB2ENR;	// RCC APB2 peripheral clock enable register, Address offset: 0x44
	uint32_t RESERVED3[2];	// Reserved, 0x48
	__IO uint32_t AHB1LPENR;// RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50
    __IO uint32_t AHB2LPENR;// RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54
    __IO uint32_t AHB3LPENR;// RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58
    uint32_t RESERVED4;		// Reserved, 0x5C
    __IO uint32_t APB1LPENR;// RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60
    __IO uint32_t APB2LPENR;// RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64
    uint32_t RESERVED5[2];	// Reserved, 0x68
    __IO uint32_t BDCR;		// RCC Backup domain control register, Address offset: 0x70
    __IO uint32_t CSR;		// RCC clock control & status register, Address offset: 0x74
    uint32_t RESERVED6[2];	// Reserved, 0x78
    __IO uint32_t SSCGR;	// RCC spread spectrum clock generation register, Address offset: 0x80
    __IO uint32_t PLLI2SCFGR;// RCC PLLI2S configuration register, Address offset: 0x84
    __IO uint32_t PLLSAICFGR;// RCC PLL configuration register, Address offset: 0x88
    __IO uint32_t DCKCFGR;	// RCC dedicated clock configuration register, Address offset: 0x8C
} RCC_t;

#define RCC 				((RCC_t *) RCC_BASE)
typedef struct
{
	__IO uint32_t MODER; 	// GPIO port mode register, Address offset: 0x00
	__IO uint32_t OTYPER; 	// GPIO port output type register, Address offset: 0x04
	__IO uint32_t OSPEEDR;	// GPIO port output speed register, Address offset: 0x08
	__IO uint32_t PUPDR; 	// GPIO port pull-up/pull-down register, Address offset: 0x0C
	__IO uint32_t IDR;		// GPIO port input data register, Address offset: 0x10
	__IO uint32_t ODR;		// GPIO port output data register, Address offset: 0x14
	__IO uint32_t BSRR;		// GPIO port bit set/reset register, Address offset: 0x18
	__IO uint32_t LCKR; 	// GPIO port configuration lock register, Address offset: 0x1C
	__IO uint32_t AFRL;		// GPIO alternate function low register, Address offset: 0x20
	__IO uint32_t AFRH;		// GPIO alternate function high register, Address offset: 0x24
} GPIOx_t;

#define GPIOA 				((GPIOx_t *) GPIOA_BASE)
#define PIN1 				(1U<<1)
#define LED_PIN				PIN1

int main(void)
{
	//1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//2. Set PA1 as output pin
	GPIOA->MODER |= (1U<<2);	//Set bit 10 to 1
	GPIOA->MODER &= ~(1U<<3); //Set bit 11 to 0


	while(1)
	{
		GPIOA->ODR |= LED_PIN;
		for(int i = 0; i < 1000000; i++);
		GPIOA->ODR &= ~(LED_PIN);
		for(int i = 0; i < 1000000; i++);
	}
}
