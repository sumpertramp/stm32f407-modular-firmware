#include "stm32f4xx.h"
#include "timer_pwm.h"

/* PD13 = TIM4_CH2 */
static void LED_PD13_PWM_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* Alternate Function */
    GPIOD->MODER &= ~(3U << (13 * 2));
    GPIOD->MODER |=  (2U << (13 * 2));

    /* AF2 = TIM4 */
    GPIOD->AFR[1] &= ~(0xF << ((13 - 8) * 4));
    GPIOD->AFR[1] |=  (2U  << ((13 - 8) * 4));

    GPIOD->OTYPER  &= ~(1U << 13);
    GPIOD->OSPEEDR |=  (3U << (13 * 2));
}

int main(void)
{
    LED_PD13_PWM_Init();
    TIM4_PWM_Init(1000); // 1 kHz

    uint8_t duty = 0;
    int8_t step = 1;

    while (1)
    {
        TIM4_PWM_SetDuty(TIM4_CH2, duty);

        duty += step;
        if (duty == 100 || duty == 0)
            step = -step;

        for (volatile uint32_t i = 0; i < 15000; i++);
    }
}
