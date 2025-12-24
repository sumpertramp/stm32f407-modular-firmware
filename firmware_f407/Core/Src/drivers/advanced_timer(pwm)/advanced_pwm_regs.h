/*
 * advanced_pwm_regs.h
 *
 *  Created on: 24 Ara 2025
 *      Author: smyyd
 */

#ifndef ADVANCED_PWM_REGS_H
#define ADVANCED_PWM_REGS_H

/* =========================================================
 * TIM1 Advanced PWM – Register Definitions
 * STM32F407
 * ========================================================= */

/* PWM mode value (PWM Mode 1) */
#define TIM_PWM_MODE_1          (6U)

/* CCMR Output Compare Mode bit positions */
#define TIM_CCMR_OC1M_Pos       (4U)
#define TIM_CCMR_OC2M_Pos       (12U)
#define TIM_CCMR_OC3M_Pos       (4U)

/* Enable preload for CCR registers */
#define TIM_CCMR_OC1PE          (1U << 3)
#define TIM_CCMR_OC2PE          (1U << 11)
#define TIM_CCMR_OC3PE          (1U << 3)

/* CCER enable bits */
#define TIM_CCER_CC1E_BIT       (1U << 0)
#define TIM_CCER_CC1NE_BIT      (1U << 2)
#define TIM_CCER_CC2E_BIT       (1U << 4)
#define TIM_CCER_CC2NE_BIT      (1U << 6)
#define TIM_CCER_CC3E_BIT       (1U << 8)
#define TIM_CCER_CC3NE_BIT      (1U << 10)

/* BDTR bits */
#define TIM_BDTR_MOE_BIT        (1U << 15)

/* Default dead-time (approx.) */
#define TIM1_DEADTIME_TICKS     (50U)

/* Channel identifiers */
#define TIM1_CHANNEL_1          (1U)
#define TIM1_CHANNEL_2          (2U)
#define TIM1_CHANNEL_3          (3U)

#endif /* ADVANCED_PWM_REGS_H */
