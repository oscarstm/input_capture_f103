#include "stm32f1xx.h"
#include "clk_user.h"
#include "timer_pwm.h"
#include "timer_input.h"
#include "gpio_user.h"

volatile uint32_t pulse_width = 0;
volatile uint32_t last_captured = 0;
volatile uint32_t signal_polarity = 0;
volatile uint32_t distance = 0;

int main(void) {
	clk_user();
	TIM4_init();
	TIM3_Init();
	GPIO_PC13_Init();

	while (1) {
		TIM4->CCR4 = 1; // 10%

		if (distance <= 50) {
			GPIOC->ODR &= ~(GPIO_ODR_ODR13);
		} else {
			GPIOC->ODR |= (GPIO_ODR_ODR13);
		}
	}

}

void TIM3_IRQHandler(void) {
	uint32_t current_captured;

	if ((TIM3->SR & (TIM_SR_CC1IF)) != 0) {
		if (signal_polarity == 0) {
			last_captured = TIM3->CCR1;
			signal_polarity = 1;
			TIM3->CCER |= (TIM_CCER_CC1P);
		} else if (signal_polarity == 1) {
			current_captured = TIM3->CCR1;
			TIM3->CNT = 0;
			if (current_captured > last_captured) {
				pulse_width = current_captured - last_captured;
			} else if (last_captured > current_captured) {
				pulse_width = (0xFFFF - last_captured) + current_captured;
			}
			distance = pulse_width / 58;
			signal_polarity = 0;
			TIM3->CCER &= ~(TIM_CCER_CC1P);
		}

	}

	if ((TIM3->SR & (TIM_SR_UIF)) != 0) {
		TIM3->SR &= ~(TIM_SR_UIF);
	}
}

