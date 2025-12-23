#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include <stdint.h>

/* =======================
 * GPIO logical identifiers
 * ======================= */
typedef enum
{
    GPIO_LED_GREEN = 0,   /* PD12 */
    GPIO_LED_ORANGE,      /* PD13 */
    GPIO_LED_RED,         /* PD14 */
    GPIO_LED_BLUE,        /* PD15 */

    GPIO_LED_MAX
} gpio_id_t;

/* =======================
 * Public API
 * ======================= */
void gpio_drv_init(void);

void gpio_drv_set(gpio_id_t id);
void gpio_drv_reset(gpio_id_t id);
void gpio_drv_toggle(gpio_id_t id);

#endif /* GPIO_DRV_H */

