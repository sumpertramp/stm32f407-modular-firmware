#include "gpio_drv.h"
#include "stm32f4xx_hal.h"

/* =======================
 * GPIO mapping table
 * ======================= */
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} gpio_hw_t;

/* LED hardware mapping (STM32F407 Discovery) */
static const gpio_hw_t gpio_map[GPIO_LED_MAX] =
{
    [GPIO_LED_GREEN]  = { GPIOD, GPIO_PIN_12 },
    [GPIO_LED_ORANGE] = { GPIOD, GPIO_PIN_13 },
    [GPIO_LED_RED]    = { GPIOD, GPIO_PIN_14 },
    [GPIO_LED_BLUE]   = { GPIOD, GPIO_PIN_15 },
};

/* =======================
 * Initialization
 * ======================= */
void gpio_drv_init(void)
{
    GPIO_InitTypeDef gpio = {0};

    /* Enable GPIO clock */
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Configure all LED pins at once */
    gpio.Pin   = GPIO_PIN_12 |
                 GPIO_PIN_13 |
                 GPIO_PIN_14 |
                 GPIO_PIN_15;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOD, &gpio);

    /* Default state: all LEDs OFF */
    HAL_GPIO_WritePin(GPIOD,
                      GPIO_PIN_12 |
                      GPIO_PIN_13 |
                      GPIO_PIN_14 |
                      GPIO_PIN_15,
                      GPIO_PIN_RESET);
}

/* =======================
 * API implementations
 * ======================= */
void gpio_drv_set(gpio_id_t id)
{
    if (id >= GPIO_LED_MAX)
        return;

    HAL_GPIO_WritePin(gpio_map[id].port,
                      gpio_map[id].pin,
                      GPIO_PIN_SET);
}

void gpio_drv_reset(gpio_id_t id)
{
    if (id >= GPIO_LED_MAX)
        return;

    HAL_GPIO_WritePin(gpio_map[id].port,
                      gpio_map[id].pin,
                      GPIO_PIN_RESET);
}

void gpio_drv_toggle(gpio_id_t id)
{
    if (id >= GPIO_LED_MAX)
        return;

    HAL_GPIO_TogglePin(gpio_map[id].port,
                       gpio_map[id].pin);
}

