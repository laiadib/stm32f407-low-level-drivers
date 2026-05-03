/*
 * user_app.c
 *
 *  Created on: May 3, 2026
 *      Author: Bilal Laiadi
 */

#include "user_app.h"
#include "app_select.h"
#include "stm32f407xx_gpio_driver.h"

/* ============================================================
 * APP: LED_TOGGLE
 * ============================================================ */
#if APP_SELECTED == APP_LED_TOGGLE

static void delay(uint32_t ms, uint32_t clk_mhz)
{
    uint32_t cycles = (uint32_t)((ms * (clk_mhz * 1000)) / 5);
    for(uint32_t i = 0; i < cycles; i++);
}

static void LED_Toggle_App(void)
{
    GPIO_Handle_t GPIO_LED;
    GPIO_LED.pGPIOx = GPIOD;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP;
    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GPIO_LED);

    while(1)
    {
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
        delay(500, 16); /* 500 ms delay at 16 MHz HSI */
    }
}

#define USER_APP_RUN() LED_Toggle_App()

/* ============================================================
 * APP: LED_TOGGLE_BUTTON
 * ============================================================ */
#elif APP_SELECTED == APP_LED_TOGGLE_BUTTON

static void delay(uint32_t ms, uint32_t clk_mhz)
{
    uint32_t cycles = (uint32_t)((ms * (clk_mhz * 1000)) / 5);
    for(uint32_t i = 0; i < cycles; i++);
}

static void LED_Toggle_Button_App(void)
{
    GPIO_Handle_t GPIO_LED, GPIO_BUTTON;
    GPIO_LED.pGPIOx = GPIOD;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP;
    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_BUTTON.pGPIOx = GPIOA;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_0;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IN;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    
    GPIO_Init(&GPIO_LED);
    GPIO_Init(&GPIO_BUTTON);

    while(1)
    {
        if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == GPIO_PIN_SET)
        {
            GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
            delay(500, 16); /* 500 ms delay at 16 MHz HSI */
        }
    }
}

#define USER_APP_RUN() LED_Toggle_Button_App()

/* ============================================================
 * APP: NONE — explicit no-op, runs an empty infinite loop
 * ============================================================ */
#elif APP_SELECTED == APP_NONE

static void None_App(void) { while(1); }

#define USER_APP_RUN() None_App()

#else
/* Unknown APP_SELECTED value — fallback to safe infinite loop */
#warning "APP_SELECTED not recognized, falling back to empty infinite loop"

static void None_App(void) { while(1); }

#define USER_APP_RUN() None_App()
#endif

/* ============================================================
 * Dispatcher — called from main()
 * ============================================================ */
void UserApp_Run(void)
{
    USER_APP_RUN();
}
