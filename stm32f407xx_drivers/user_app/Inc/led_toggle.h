/*
 * LED_Toggle.h
 *
 *  Created on: May 2, 2026
 *      Author: Bilal Laiadi
 */

#ifndef LED_TOGGLE_H
#define LED_TOGGLE_H

#include <stdint.h>

/**
 * @brief  Generates a delay in milliseconds.
 * @param  ms: Number of milliseconds to delay.
 * @param  clk_mhz: System clock frequency in MHz.
 * @note   Approximate delay — depends on compiler optimization level.
 */
void delay(uint32_t ms, uint32_t clk_mhz);

/**
 * @brief  Initializes the LED GPIO pin and runs the toggle loop.
 * @note   Configures GPIOD pin 12 as push-pull output and toggles it every 500 ms.
 */
void LED_Toggle_App(void);

#endif /* LED_TOGGLE_H */
