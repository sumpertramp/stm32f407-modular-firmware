#include "stm32f4xx.h"
#include "advanced_pwm.h"

static void GPIO_TIM1_Init(void);

int main(void)
{
    GPIO_TIM1_Init();

    /* 20 kHz motor-friendly PWM */
    TIM1_PWM_Init(20000);

    /* %50 duty */
    TIM1_PWM_SetDuty(1, TIM1->ARR / 2);

    TIM1_PWM_Enable();

    while (1)
    {
        /* Duty sweep – logic analyzer test */
        for (uint16_t d = 0; d < TIM1->ARR; d += 200)
        {
            TIM1_PWM_SetDuty(1, d);
            for (volatile uint32_t i = 0; i < 50000; i++);
        }
    }
}

static void GPIO_TIM1_Init(void)
{
    /* Enable GPIOA & GPIOB clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* PA8 – TIM1_CH1 */
    GPIOA->MODER &= ~(3U << (8 * 2));
    GPIOA->MODER |=  (2U << (8 * 2));      /* AF mode */
    GPIOA->AFR[1] |= (1U << ((8 - 8) * 4)); /* AF1 */

    /* PB13 – TIM1_CH1N */
    GPIOB->MODER &= ~(3U << (13 * 2));
    GPIOB->MODER |=  (2U << (13 * 2));      /* AF mode */
    GPIOB->AFR[1] |= (1U << ((13 - 8) * 4)); /* AF1 */
}
