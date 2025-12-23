/*
 * timer_pwm.c
 *
 *  Created on: 23 Ara 2025
 *      Author: sumeyye unal
 */

#include "timer_pwm.h"

static uint32_t arr_value;

void TIM4_PWM_Init(uint32_t freq_hz)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    /* 84 MHz / 84 = 1 MHz */
    TIM4->PSC = 83;

    arr_value = (1000000UL / freq_hz) - 1;
    TIM4->ARR = arr_value;

    /* PWM mode 1 */
    TIM4->CCMR1 = (6U << 12);   // CH2
    TIM4->CCMR1 |= (1U << 11);  // preload
    TIM4->CR1   |= TIM_CR1_ARPE;

    /* Enable CH2 */
    TIM4->CCER |= TIM_CCER_CC2E;

    /* Start timer */
    TIM4->CR1 |= TIM_CR1_CEN;
}

void TIM4_PWM_SetDuty(tim4_channel_t ch, uint8_t duty)
{
    if (duty > 100) duty = 100;
    TIM4->CCR2 = (arr_value * duty) / 100;
}


