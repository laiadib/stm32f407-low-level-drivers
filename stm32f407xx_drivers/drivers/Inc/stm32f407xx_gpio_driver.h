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
} GPIO_PinConfig_t;
 
typedef struct
{
    GPIO_RegDef_t *pGPIOx; /* This holds the base address of the GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig; /* This holds GPIO pin configuration settings */
} GPIO_Handle_t;



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
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

#endif /* STM32F407XX_GPIO_DRIVER_H_ */