/*
 * timer_pwm.h
 *
 *  Created on: 23 Ara 2025
 *      Author: sumeyye_unal
 */

#ifndef TIMER_PWM_H
#define TIMER_PWM_H

#include "stm32f4xx.h"
#include <stdint.h>

typedef enum {
    TIM4_CH2 = 2
} tim4_channel_t;

void TIM4_PWM_Init(uint32_t freq_hz);
void TIM4_PWM_SetDuty(tim4_channel_t ch, uint8_t duty);

#endif
