/*
 * timer_pwm.c
 *
 *  Created on: Aug 5, 2022
 *      Author: oscar
 */

#include "timer_pwm.h"

void TIM4_init(void) {
	/*
	 * GPIO settings PB9
	 */
	RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN);

	GPIOB->CRH &= ~(GPIO_CRH_MODE9_0);
	GPIOB->CRH |= (GPIO_CRH_MODE9_1);
	GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOB->CRH |= (GPIO_CRH_CNF9_1);
	/*
	 * Counter settings
	 */
	RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN);

	TIM4->CR1 &= ~(TIM_CR1_DIR);

	TIM4->PSC = 720 - 1; // 100 KHz = 0.1 MHz

	TIM4->ARR = 10 - 1; // 100 us
	/*
	 * PWM generation channel 4
	 */
	TIM4->CCMR2 &= ~(TIM_CCMR2_OC4M);
	TIM4->CCMR2 &= ~(TIM_CCMR2_OC4M_0);
	TIM4->CCMR2 |= (TIM_CCMR2_OC4M_1);
	TIM4->CCMR2 |= (TIM_CCMR2_OC4M_2);
	TIM4->CCMR2 |= (TIM_CCMR2_OC4PE);

	TIM4->CCER &= ~(TIM_CCER_CC4P);
	TIM4->CCER |= (TIM_CCER_CC4E);

	TIM4->CR1 |= (TIM_CR1_CEN);
}
