#include "stm32f407xx_gpio_driver.h"

/* API supported by this driver */

/* Peripheral Clock setup */
/**
 * @brief  This function enables or disables the peripheral clock for the given GPIO port.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @param  EnorDi: Enable or Disable macro (ENABLE or DISABLE)
 * @retval None
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    uint8_t portIndex = ((uint32_t)pGPIOx - (uint32_t)GPIOA) / 0x400;

    if(EnorDi == ENABLE)
    {
        switch(portIndex)
        {
            case 0: GPIOA_PCLK_EN(); break;
            case 1: GPIOB_PCLK_EN(); break;
            case 2: GPIOC_PCLK_EN(); break;
            case 3: GPIOD_PCLK_EN(); break;
            case 4: GPIOE_PCLK_EN(); break;
            case 5: GPIOF_PCLK_EN(); break;
            case 6: GPIOG_PCLK_EN(); break;
            case 7: GPIOH_PCLK_EN(); break;
            case 8: GPIOI_PCLK_EN(); break;
            default: break;
        }
    }
    else
    {
        switch(portIndex)
        {
            case 0: GPIOA_PCLK_DI(); break;
            case 1: GPIOB_PCLK_DI(); break;
            case 2: GPIOC_PCLK_DI(); break;
            case 3: GPIOD_PCLK_DI(); break;
            case 4: GPIOE_PCLK_DI(); break;
            case 5: GPIOF_PCLK_DI(); break;
            case 6: GPIOG_PCLK_DI(); break;
            case 7: GPIOH_PCLK_DI(); break;
            case 8: GPIOI_PCLK_DI(); break;
            default: break;
        }
    }
}

/* Initialization and De-initialization */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

}

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{

}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)  
{

}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

}

/* IRQ configuration and handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}
void GPIO_IRQHandling(uint8_t IRQNumber)
{

}