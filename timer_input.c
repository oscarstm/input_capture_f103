/*
 * timer_input.c
 *
 *  Created on: Aug 6, 2022
 *      Author: oscar
 */

#include "timer_input.h"

void TIM3_Init(void) {
	/*
	 * GPIO settings PA6
	 */
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN);

	GPIOA->CRL |= (GPIO_CRL_CNF6_0);
	GPIOA->CRL &= ~(GPIO_CRL_CNF6_1);
	GPIOA->CRL &= ~(GPIO_CRL_MODE6);
	/*
	 * Counter settings
	 */
	RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);

	TIM3->PSC = 72 - 1; // CK_CNT = 1 MHz
	TIM3->ARR = 65536 - 1;
	/*
	 * Input capture channel 1
	 */
	TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S);
	TIM3->CCMR1 |= (TIM_CCMR1_CC1S_0);
	TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S_1);
	TIM3->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	TIM3->CCMR1 &= ~(TIM_CCMR1_IC1F);

	TIM3->CCER &= ~(TIM_CCER_CC1P);
	TIM3->CCER |= (TIM_CCER_CC1E);

	TIM3->DIER |= (TIM_DIER_CC1IE);

	TIM3->CR1 |= (TIM_CR1_CEN);

	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
}
