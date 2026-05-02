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
/**
 * @brief  Initializes the GPIO pin according to the configuration in the handle.
 * @note   Enables the peripheral clock automatically, then configures mode,
 *         speed, pull-up/pull-down, output type, and alternate function.
 * @param  pGPIOHandle: Pointer to the GPIO handle containing the port base
 *                      address and the pin configuration settings
 * @retval None
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    // 1. Enable the peripheral clock
     GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    // 2. Configure the mode of the GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) // Non-interrupt mode
    {
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the bits
        pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // Set the bits
    }
    else // Interrupt mode
    {
        // TODO: Configure interrupt mode
    }

    // 3. Configure the speed
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the bits
    pGPIOHandle->pGPIOx->OSPEEDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // Set the bits

    // 4. Configure the pupd settings
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear the bits
    pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ); // Set the bits

    // 5. Configure the optype
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear the bit
    pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // Set the bit

    // 6. Configure the alternate functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t afrIndex, afrBitPos;
        afrIndex  = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // Determine AFR[0] or AFR[1]
        afrBitPos = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // Determine the position within the AFR register
        pGPIOHandle->pGPIOx->AFR[afrIndex] &= ~(0xF << (4 * afrBitPos)); // Clear the bits
        pGPIOHandle->pGPIOx->AFR[afrIndex] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * afrBitPos)); // Set the bits
    }
    
}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    uint8_t portIndex = ((uint32_t)pGPIOx - (uint32_t)GPIOA) / 0x400;

    switch(portIndex)
    {
        case 0: GPIOA_REG_RESET(); break;
        case 1: GPIOB_REG_RESET(); break;
        case 2: GPIOC_REG_RESET(); break;
        case 3: GPIOD_REG_RESET(); break;
        case 4: GPIOE_REG_RESET(); break;
        case 5: GPIOF_REG_RESET(); break;
        case 6: GPIOG_REG_RESET(); break;
        case 7: GPIOH_REG_RESET(); break;
        case 8: GPIOI_REG_RESET(); break;
        default: break;
    }
}

/**
 * @brief  This function reads the state of a specific GPIO pin.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @param  PinNumber: The pin number to read (0-15)
 * @retval The state of the pin (0 or 1)
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001); // Read the specific bit and mask out the rest
    return value;
} 

/**
 * @brief  This function reads the state of all 16 pins of a GPIO port at once.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @retval 16-bit value representing the state of all pins (bit 0 = pin 0, bit 15 = pin 15)
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;
    value = (uint16_t)(pGPIOx->IDR);
    return value;
}