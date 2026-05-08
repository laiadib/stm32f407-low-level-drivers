/*
 * user_app.c
 *
 *  Created on: May 3, 2026
 *      Author: Bilal Laiadi
 */

#include "user_app.h"
#include "app_select.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"

/* ============================================================
 * Common helpers
 * ============================================================ */
static void delay(uint32_t ms, uint32_t clk_mhz)
{
    uint32_t cycles = (uint32_t)((ms * (clk_mhz * 1000)) / 5);
    for(uint32_t i = 0; i < cycles; i++);
}

/* ============================================================
 * APP: LED_TOGGLE
 * ============================================================ */
#if APP_SELECTED == APP_LED_TOGGLE

static void LED_Toggle_App(void)
{
    GPIO_Handle_t GPIO_LED;

    MEMSET(&GPIO_LED, 0, sizeof(GPIO_Handle_t));

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

static void LED_Toggle_Button_App(void)
{
    GPIO_Handle_t GPIO_LED, GPIO_BUTTON;

    MEMSET(&GPIO_LED, 0, sizeof(GPIO_Handle_t));
    MEMSET(&GPIO_BUTTON, 0, sizeof(GPIO_Handle_t));

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
 * APP: LED_TOGGLE_BUTTON_IT
 * ============================================================ */
#elif APP_SELECTED == APP_LED_TOGGLE_BUTTON_IT

static void LED_Toggle_Button_IT_App(void)
{
    GPIO_Handle_t GPIO_LED, GPIO_BUTTON;

    MEMSET(&GPIO_LED, 0, sizeof(GPIO_Handle_t));
    MEMSET(&GPIO_BUTTON, 0, sizeof(GPIO_Handle_t));

    GPIO_LED.pGPIOx = GPIOD;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
    GPIO_LED.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_LOW;
    GPIO_LED.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP;
    GPIO_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_BUTTON.pGPIOx = GPIOA;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_0;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IT_FT;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_LOW;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GPIO_LED);
    GPIO_Init(&GPIO_BUTTON);

    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRI15); // this is optional, as we have only one interrupt.
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

    while(1);

}

void EXTI0_IRQHandler(void)
{
    delay(200, 16); /* 200 ms delay at 16 MHz HSI */
    GPIO_IRQHandling(GPIO_PIN_NO_0); // clear the EXTI line pending bit
    GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}

#define USER_APP_RUN() LED_Toggle_Button_IT_App()

/* ============================================================
 * APP: SPI_HALF_DUPLEX_TX
 * SPI2 (master TX only test): PB13=SCK, PB15=MOSI (AF5)
 * ============================================================ */
#elif APP_SELECTED == APP_SPI_HALF_DUPLEX_TX


static void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;
    MEMSET(&SPIPins, 0, sizeof(GPIO_Handle_t));

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5; /* AF5: SPI2 */
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13; /* SCK */
    GPIO_Init(&SPIPins);

    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15; /* MOSI */
    GPIO_Init(&SPIPins);

}

static void SPI2_Inits(void)
{
    SPI_Handle_t SPI2Handle;
    MEMSET(&SPI2Handle, 0, sizeof(SPI_Handle_t));

    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_HALF_DUPLEX; /* 1-line TX only: prevents RX overrun */
    SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; /* f_PCLK/2, generates 8 MHz SCK */
    SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

    SPI_Init(&SPI2Handle);
}

// add doxygen documentation:

/**
 * @brief  Application to send data over SPI2 in half-duplex mode (master TX only).
 *         PB13 is configured as SCK and PB15 as MOSI (AF5).
 *         The application initializes the GPIO pins and SPI2 peripheral, then sends a test string.
 *         Since software slave management is enabled, the SSI bit is set to avoid MODF error.
 *         The transmitted data can be checked using a logic analyzer.
 *         The application runs an infinite loop after sending the data.
 */
static void SPI_HalfDuplex_Tx_App(void)
{
    char user_data[] = "ABC";
    char user_data2[] = "DEF";

    /* Initialize GPIO pins for SPI2 */
    SPI2_GPIOInits();

    /* Initialize SPI2 peripheral */
    SPI2_Inits();
    
    /* Since we are using software slave management, we need to set the SSI bit to avoid MODF error */
    SPI_SSIConfig(SPI2, ENABLE);

    /* Select transmit direction in 1-line half-duplex mode */
    SPI_SetHalfDuplexDirection(SPI2, SPI_BIDIRECTIONAL_LINE_TX); // Configure the single data line for transmission

    /* Enable the SPI peripheral */
    SPI_PeripheralControl(SPI2, ENABLE);

    /* Send the user data over SPI2 */
    SPI_SendData(SPI2, (uint8_t*)user_data, (uint32_t)(sizeof(user_data) - 1U)); // exclude null terminator
    delay(1000, 16); /* 1 second delay at 16 MHz HSI */
    SPI_SendData(SPI2, (uint8_t*)user_data2, (uint32_t)(sizeof(user_data2) - 1U)); // exclude null terminator

    /* Disable the SPI peripheral after transmission is complete */
    SPI_PeripheralControl(SPI2, DISABLE);

    while(1);
}

#define USER_APP_RUN() SPI_HalfDuplex_Tx_App()

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
