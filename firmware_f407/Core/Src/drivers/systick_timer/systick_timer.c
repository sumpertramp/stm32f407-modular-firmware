/*
 * systick_timer.c
 *
 *  Created on: 25 Ara 2025
 *      Author: sumeyye unal
 */

#include "systick_timer.h"
#include "stm32f4xx_hal.h"

static volatile uint32_t systick_ms = 0;

void SysTick_Init(uint32_t tick_hz)
{
    /* HAL must be initialized before this */
    HAL_SYSTICK_Config(SystemCoreClock / tick_hz);
}

void HAL_SYSTICK_Callback(void)
{
    SysTick_TickInc();
}

void SysTick_TickInc(void)
{
    systick_ms++;
}

uint32_t SysTick_GetTick(void)
{
    return systick_ms;
}

void SysTick_DelayMs(uint32_t ms)
{
    uint32_t start = SysTick_GetTick();
    while ((SysTick_GetTick() - start) < ms);
}
