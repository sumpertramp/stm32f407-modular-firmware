#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "systick_timer.h"

/* ================= CONFIG ================= */
#define LED_PORT    GPIOD
#define LED_PIN     15      // STM32F407 Discovery Blue LED

#define LA_PORT     GPIOA
#define LA_PIN      0       // Logic Analyzer output pin

int main(void)
{
    /* ---- HAL ---- */
    HAL_Init();                 // SysTick burada kuruluyor
    SystemCoreClockUpdate();
    __enable_irq();

    /* ---- GPIO CLOCKS ---- */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* ---- GPIO CONFIG ---- */
    LED_PORT->MODER &= ~(3U << (LED_PIN * 2));
    LED_PORT->MODER |=  (1U << (LED_PIN * 2));

    LA_PORT->MODER &= ~(3U << (LA_PIN * 2));
    LA_PORT->MODER |=  (1U << (LA_PIN * 2));

    while (1)
    {
        LED_PORT->ODR ^= (1U << LED_PIN);
        LA_PORT->ODR  ^= (1U << LA_PIN);

        SysTick_DelayMs(500);
    }
}
