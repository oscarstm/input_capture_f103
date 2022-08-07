/*
 * gpio_user.c
 *
 *  Created on: Aug 6, 2022
 *      Author: oscar
 */

#include "gpio_user.h"

void GPIO_PC13_Init(void) {
	RCC->APB2ENR |= (RCC_APB2ENR_IOPCEN);

	GPIOC->CRH &= ~(GPIO_CRH_CNF13);
	GPIOC->CRH &= ~(GPIO_CRH_MODE13_0);
	GPIOC->CRH |= (GPIO_CRH_MODE13_1);
}
