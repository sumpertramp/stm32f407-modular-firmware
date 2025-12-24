/*
 * advanced_pwm.h
 *
 *  Created on: 24 Ara 2025
 *      Author: sumeyye unal
 */

#ifndef ADVANCED_PWM_H
#define ADVANCED_PWM_H

#include <stdint.h>

/* =========================================================
 * TIM1 Advanced PWM Driver – Public API
 * ========================================================= */

/**
 * @brief Initialize TIM1 for advanced PWM generation
 * @param pwm_freq PWM frequency in Hz
 */
void TIM1_PWM_Init(uint32_t pwm_freq);

/**
 * @brief Enable TIM1 PWM outputs (MOE)
 */
void TIM1_PWM_Enable(void);

/**
 * @brief Disable TIM1 PWM outputs
 */
void TIM1_PWM_Disable(void);

/**
 * @brief Set PWM duty cycle
 * @param channel TIM1_CHANNEL_1 / 2 / 3
 * @param duty Duty value (0 … ARR)
 */
void TIM1_PWM_SetDuty(uint8_t channel, uint16_t duty);

/**
 * @brief Set dead-time
 * @param dt_ticks Dead-time ticks (BDTR)
 */
void TIM1_PWM_SetDeadTime(uint8_t dt_ticks);

#endif /* ADVANCED_PWM_H */
