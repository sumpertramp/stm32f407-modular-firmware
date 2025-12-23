/*
 * main_gpio_blinc.c
 *
 *  Created on: Dec 22, 2025
 *      Author: sumeyye_unal
 */

#include "main.h"
#include "board.h"
#include "gpio_drv.h"

int main(void)
{
    board_init();

    while (1)
    {
        gpio_drv_toggle(GPIO_LED1); // GREEN LED in STM32F407 DISC
        HAL_Delay(500);
    }
}

