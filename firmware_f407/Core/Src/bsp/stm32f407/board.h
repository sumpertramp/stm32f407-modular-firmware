/*
 * board.h
 *
 *  Created on: Dec 22, 2025
 *      Author: Sumeyye Unal
 */

#ifndef BOARD_H
#define BOARD_H

#include "stm32f4xx_hal.h"

/* ================= Board Identification ================= */
#define BOARD_NAME        "STM32F407"
#define BOARD_REVISION    "A"

/* ================= BSP Public API ================= */
void board_init(void);
void board_clock_init(void);
void board_error_handler(void);

#endif /* BOARD_H */
