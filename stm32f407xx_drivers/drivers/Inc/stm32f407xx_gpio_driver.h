/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: May 2, 2026
 *      Author: Bilal Laiadi
 */

#ifndef STM32F407XX_GPIO_DRIVER_H
#define STM32F407XX_GPIO_DRIVER_H
#include "stm32f407xx.h"


typedef struct
{
    uint8_t GPIO_PinNumber;  /* possible values from @GPIO_PIN_NUMBERS */
    uint8_t GPIO_PinMode;    /* possible values from @GPIO_PIN_MODES */
    uint8_t GPIO_PinSpeed;   /* possible values from @GPIO_PIN_SPEED */
    uint8_t GPIO_PinPuPdControl; /* possible values from @GPIO_PIN_PUPD */
    uint8_t GPIO_PinOPType;  /* possible values from @GPIO_OP_TYPE */
    uint8_t GPIO_PinAltFunMode; /* possible values from @GPIO_PIN_ALT_FUN_MODE */
} GPIO_PinConfig_t;
 
typedef struct
{
    GPIO_RegDef_t *pGPIOx; /* This holds the base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig; /* This holds GPIO pin configuration settings */
} GPIO_Handle_t;


/* GPIO pin possible modes */
/* @GPIO_PIN_MODES */
#define GPIO_MODE_IN            0 /* Input mode */
#define GPIO_MODE_OUT           1 /* Output mode */
#define GPIO_MODE_ALTFN         2 /* Alternate function mode */
#define GPIO_MODE_ANALOG        3 /* Analog mode */
#define GPIO_MODE_IT_FT         4 /* Interrupt mode - Falling edge trigger */
#define GPIO_MODE_IT_RT         5 /* Interrupt mode - Rising edge trigger */
#define GPIO_MODE_IT_RFT        6 /* Interrupt mode - Rising/Falling edge trigger */

/* GPIO pin possible output types */
/* @GPIO_OP_TYPE */
#define GPIO_OP_TYPE_PP        0 /* Push-pull output */
#define GPIO_OP_TYPE_OD        1 /* Open-drain output */

/* GPIO pin possible speeds */
/* @GPIO_PIN_SPEED */
#define GPIO_SPEED_LOW         0 /* Low speed */
#define GPIO_SPEED_MEDIUM      1 /* Medium speed */
#define GPIO_SPEED_FAST        2 /* Fast speed */
#define GPIO_SPEED_HIGH        3 /* High speed */

/* GPIO pin pull-up/pull-down configuration */
/* @GPIO_PIN_PUPD */
#define GPIO_NO_PUPD           0 /* No pull-up/pull-down */
#define GPIO_PIN_PU            1 /* Pull-up */
#define GPIO_PIN_PD            2 /* Pull-down */

/* GPIO pin numbers */
/* @GPIO_PIN_NUMBERS */
#define GPIO_PIN_NO_0          0
#define GPIO_PIN_NO_1          1
#define GPIO_PIN_NO_2          2
#define GPIO_PIN_NO_3          3
#define GPIO_PIN_NO_4          4
#define GPIO_PIN_NO_5          5
#define GPIO_PIN_NO_6          6
#define GPIO_PIN_NO_7          7
#define GPIO_PIN_NO_8          8
#define GPIO_PIN_NO_9          9
#define GPIO_PIN_NO_10         10
#define GPIO_PIN_NO_11         11
#define GPIO_PIN_NO_12         12
#define GPIO_PIN_NO_13         13
#define GPIO_PIN_NO_14         14
#define GPIO_PIN_NO_15         15


/* API supported by this driver */

/* Peripheral Clock setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Initialization and De-initialization */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/* IRQ configuration and handling */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* STM32F407XX_GPIO_DRIVER_H_ */
