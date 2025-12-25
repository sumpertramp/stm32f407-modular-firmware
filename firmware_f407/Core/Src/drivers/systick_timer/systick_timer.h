/*
 * systick_timer.h
 *
 *  Created on: 25 Ara 2025
 *      Author: sumeyye unal
 */
#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include <stdint.h>

uint32_t SysTick_GetTick(void);
void SysTick_DelayMs(uint32_t ms);

#endif
