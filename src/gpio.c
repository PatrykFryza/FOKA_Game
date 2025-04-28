/*
 * gpio.c
 *
 *  Created on: Mar 16, 2025
 *      Author: patry
 */

#include "stm32f4xx.h"


void leds_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //enable clock for port B
	GPIOB->MODER = 0x00000000; //make sure that all bits are at 0, since reset value is 0x0000 0280 for port B
	GPIOB->MODER |= (0b01)|(0b01 << 2)|(0b01 << 4)|(0b01 << 6)|(0b01 << 8); //set pins 1-5 as outputs
	GPIOB->ODR = 0b00000000; //all leds are off
}


void leds_update(uint8_t led_state){
	GPIOB->ODR = led_state;
}


void buttons_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //enable clock for port C
	//no need to change MODER register as it is in input
	GPIOC->PUPDR |= (1 << 10)|(1 << 12)|(1 << 14); //Pull-ups

	//exti at pins 5, 6, 7 of port C
	SYSCFG->EXTICR[1] |= (0b01 << 5);
	SYSCFG->EXTICR[1] |= (0b01 << 9);
	SYSCFG->EXTICR[1] |= (0b01 << 13);

	EXTI->IMR |= EXTI_IMR_IM5|EXTI_IMR_IM6|EXTI_IMR_IM7;
	EXTI->RTSR |= EXTI_IMR_IM5|EXTI_IMR_IM6|EXTI_IMR_IM7;

	NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}


