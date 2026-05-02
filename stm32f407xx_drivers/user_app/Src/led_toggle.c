/*
 * LED_Toggle.c
 *
 *  Created on: May 2, 2026
 *      Author: Bilal Laiadi
 */

#include "led_toggle.h"
#include "stm32f407xx_gpio_driver.h"

/**
 * @brief  Generates a software busy-wait delay.
 * @param  ms:      Delay duration in milliseconds.
 * @param  clk_mhz: System clock frequency in MHz (e.g. 16 for HSI, 168 for PLL).
 * @note   The loop count is estimated assuming ~5 CPU cycles per iteration at -O0.
 *         Accuracy degrades at higher optimisation levels; use a hardware timer
 *         (SysTick or TIMx) for precision delays.
 * @retval None
 */
void delay(uint32_t ms, uint32_t clk_mhz)
{
    uint32_t cycles = (uint32_t)((ms * (clk_mhz * 1000)) / 5); /* ~5 cycles per loop iteration at -O0 */
    for(uint32_t i = 0; i < cycles; i++);
}

void LED_Toggle_App(void)
{
    GPIO_Handle_t GPIO_LED;
    GPIO_LED.pGPIOx = GPIOD;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;  /* Pin number 12 */
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;   /* Output mode */
    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST; /* Fast speed */
    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP; /* Push-pull output */
    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;    /* Push-pull actively drives both states; internal pull resistors are not needed */

    GPIO_Init(&GPIO_LED);

    while(1)
    {
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
        delay(500, 16); /* 500 ms delay at 16 MHz HSI */
    }
}
