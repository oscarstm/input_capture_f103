/*
 * clk_user.c
 *
 *  Created on: Jul 7, 2022
 *      Author: oscar
 */

#include "clk_user.h"

void clk_user(void) {
	RCC->CR |= (RCC_CR_HSEON);
	while ((RCC->CR & RCC_CR_HSERDY) == RESET) {
		//
	}
	/*
	 * System parameters
	 */
	FLASH->ACR &= ~(FLASH_ACR_PRFTBE);
	FLASH->ACR |= (FLASH_ACR_PRFTBE);
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR &= ~(FLASH_ACR_LATENCY_0);
	FLASH->ACR |= (FLASH_ACR_LATENCY_1);
	FLASH->ACR &= ~(FLASH_ACR_LATENCY_2);
	/*
	 * RCC parameters
	 */
	RCC->CFGR &= ~(RCC_CFGR_HPRE);

	RCC->CFGR &= ~(RCC_CFGR_PPRE2);

	RCC->CFGR &= ~(RCC_CFGR_PPRE1_0);
	RCC->CFGR &= ~(RCC_CFGR_PPRE1_1);
	RCC->CFGR |= (RCC_CFGR_PPRE1_2);

	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);

	RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE);

	RCC->CFGR |= (RCC_CFGR_PLLSRC);

	RCC->CFGR |= (RCC_CFGR_PLLMULL_0);
	RCC->CFGR |= (RCC_CFGR_PLLMULL_1);
	RCC->CFGR |= (RCC_CFGR_PLLMULL_2);
	RCC->CFGR &= ~(RCC_CFGR_PLLMULL_3);

	RCC->CR |= (RCC_CR_PLLON);
	while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) {
		// wait
	}

	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= (RCC_CFGR_SW_PLL);
	while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL) {
		// wait
	}
}
