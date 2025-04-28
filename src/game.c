/*
 * game.c
 *
 *  Created on: Mar 16, 2025
 *      Author: patry
 */
#include "stdint.h"
#include "stm32f4xx.h"
#include "gpio.h"

uint8_t ledstate = 0;

uint8_t check_win_condition(uint8_t led_state){
	if(led_state == 0b00011111){
		return 1;
	}
	return 0;
}


void adder_button(uint8_t *led_state){
	*led_state &= 0b00011011;
	*led_state |= 0b00010000;
}


void toggler_button(uint8_t *led_state){
	*led_state ^= 0b00000100;
}


void shifter_button(uint8_t *led_state){
	if((*led_state & 0b00000001) == 1){
		*led_state |= 0b00100000;
	}
	*led_state >>= 1;
}



void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR5){
		EXTI->PR |= EXTI_PR_PR5;
		adder_button(&ledstate);
		leds_update(ledstate);
	}
	else if(EXTI->PR & EXTI_PR_PR6){
		EXTI->PR |= EXTI_PR_PR6;
		toggler_button(&ledstate);
		leds_update(ledstate);
	}
	else if(EXTI->PR & EXTI_PR_PR7){
		EXTI->PR |= EXTI_PR_PR7;
		shifter_button(&ledstate);
		leds_update(ledstate);
	}
	EXTI->IMR &= ~(EXTI_IMR_IM5|EXTI_IMR_IM6|EXTI_IMR_IM7); //disable interupts
	TIM2->CR1 |= TIM_CR1_CEN; //enable counter
}


