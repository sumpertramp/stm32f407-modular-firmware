#include "stm32f4xx.h"
#include "systick_timer.h"

/* ================= CONFIG ================= */
#define LED_PORT    GPIOD
#define LED_PIN     15      // STM32F407 Discovery Blue LED

#define LA_PORT     GPIOA
#define LA_PIN      0       // Logic Analyzer output pin

int main(void)
{
    /* Enable GPIO clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Configure LED pin (PD15) */
    LED_PORT->MODER &= ~(3U << (LED_PIN * 2));
    LED_PORT->MODER |=  (1U << (LED_PIN * 2));

    /* Configure Logic Analyzer pin (PA0) */
    LA_PORT->MODER &= ~(3U << (LA_PIN * 2));
    LA_PORT->MODER |=  (1U << (LA_PIN * 2));

    /* Init SysTick driver (1 ms tick) */
    SysTick_Init(1000);

    while (1)
    {
        /* Toggle LED and logic analyzer pin */
        LED_PORT->ODR ^= (1U << LED_PIN);
        LA_PORT->ODR  ^= (1U << LA_PIN);

        /* SysTick-based delay */
        SysTick_DelayMs(500);
    }
}

