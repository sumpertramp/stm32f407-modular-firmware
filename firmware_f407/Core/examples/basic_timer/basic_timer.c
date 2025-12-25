#include "stm32f4xx.h"
#include "basic_timer.h"

int main(void)
{
    /* LED örneği: PD12 (Discovery) */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER &= ~(3 << (12 * 2));
    GPIOD->MODER |=  (1 << (12 * 2));

    basic_timer_init();

    uint32_t last = 0;

    while (1)
    {
        if (basic_timer_get_tick() - last >= 500)
        {
            last = basic_timer_get_tick();
            GPIOD->ODR ^= (1 << 12);   // LED toggle
        }
    }
}
