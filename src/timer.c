/*
 * handlers.c
 *
 *  Created on: Mar 16, 2025
 *      Author: patry
 */
#include "stm32f4xx.h"

void timer_init(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    //16 MHz SysClock
    TIM2->PSC = 16000 - 1;  // Prescaler value
    TIM2->ARR = 100 - 1;  // Auto-reload value (100ms at 10kHz)

    // Enable update interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Configure NVIC
    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void){
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        EXTI->IMR |= EXTI_IMR_IM5|EXTI_IMR_IM6|EXTI_IMR_IM7; //enable interupts
        TIM2->CR1 &= ~TIM_CR1_CEN;	//disable counter
    }
}
