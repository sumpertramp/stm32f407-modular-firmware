/*
 * advanced_pwm.c
 *
 *  Created on: 24 Ara 2025
 *      Author: smyyd
 */

#include "stm32f4xx.h"
#include "advanced_pwm.h"
#include "advanced_pwm_regs.h"

/* =========================================================
 * TIM1 Advanced PWM Driver – Implementation
 * ========================================================= */

void TIM1_PWM_Init(uint32_t pwm_freq)
{
    /* Enable TIM1 clock */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /* Reset TIM1 configuration */
    TIM1->CR1  = 0;
    TIM1->CR2  = 0;
    TIM1->SMCR = 0;

    /* Prescaler = 0 (full speed) */
    TIM1->PSC = 0;

    /* Auto-reload for desired PWM frequency */
    TIM1->ARR = (SystemCoreClock / pwm_freq) - 1;

    /* Center-aligned mode (optional but motor-friendly) */
    TIM1->CR1 |= TIM_CR1_CMS_0;

    /* PWM Mode 1 on CH1, CH2, CH3 */
    TIM1->CCMR1 |=
        (TIM_PWM_MODE_1 << TIM_CCMR_OC1M_Pos) |
        (TIM_PWM_MODE_1 << TIM_CCMR_OC2M_Pos) |
        TIM_CCMR_OC1PE |
        TIM_CCMR_OC2PE;

    TIM1->CCMR2 |=
        (TIM_PWM_MODE_1 << TIM_CCMR_OC3M_Pos) |
        TIM_CCMR_OC3PE;

    /* Enable main and complementary outputs */
    TIM1->CCER |=
        TIM_CCER_CC1E_BIT  | TIM_CCER_CC1NE_BIT |
        TIM_CCER_CC2E_BIT  | TIM_CCER_CC2NE_BIT |
        TIM_CCER_CC3E_BIT  | TIM_CCER_CC3NE_BIT;

    /* Dead-time + Main Output Enable */
    TIM1->BDTR |=
        TIM1_DEADTIME_TICKS |
        TIM_BDTR_MOE_BIT;

    /* Enable counter */
    TIM1->CR1 |= TIM_CR1_CEN;
}

void TIM1_PWM_Enable(void)
{
    TIM1->BDTR |= TIM_BDTR_MOE_BIT;
}

void TIM1_PWM_Disable(void)
{
    TIM1->BDTR &= ~TIM_BDTR_MOE_BIT;
}

void TIM1_PWM_SetDuty(uint8_t channel, uint16_t duty)
{
    if (duty > TIM1->ARR)
        duty = TIM1->ARR;

    switch (channel)
    {
        case TIM1_CHANNEL_1:
            TIM1->CCR1 = duty;
            break;

        case TIM1_CHANNEL_2:
            TIM1->CCR2 = duty;
            break;

        case TIM1_CHANNEL_3:
            TIM1->CCR3 = duty;
            break;

        default:
            /* Invalid channel */
            break;
    }
}

void TIM1_PWM_SetDeadTime(uint8_t dt_ticks)
{
    TIM1->BDTR &= ~0xFFU;
    TIM1->BDTR |= dt_ticks;
}

