/*
 * timer_drv.c
 *
 *  Created on: 23 Ara 2025
 *      Author: sumeyye unal
 */

#include "basic_timer.h"
#include "stm32f4xx.h"

static volatile uint32_t tick_ms = 0;

void basic_timer_init(void)
{
    /* 1️⃣ TIM6 clock enable */
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    /* 2️⃣ Prescaler & ARR
       84 MHz / 84 = 1 MHz
       1 MHz / 1000 = 1 kHz → 1 ms
    */
    TIM6->PSC = 84 - 1;
    TIM6->ARR = 1000 - 1;

    /* 3️⃣ Update interrupt enable */
    TIM6->DIER |= TIM_DIER_UIE;

    /* 4️⃣ NVIC enable */
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
    NVIC_SetPriority(TIM6_DAC_IRQn, 1);

    /* 5️⃣ Counter enable */
    TIM6->CR1 |= TIM_CR1_CEN;
}

uint32_t basic_timer_get_tick(void)
{
    return tick_ms;
}

/* ⚠️ ISR burada YOK */
void basic_timer_irq_handler(void)
{
    tick_ms++;
}







