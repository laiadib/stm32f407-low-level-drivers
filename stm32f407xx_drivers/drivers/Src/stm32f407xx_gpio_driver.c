/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: May 2, 2026
 *      Author: Bilal Laiadi
 */

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
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            // Configure falling edge trigger
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Enable falling edge trigger */
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Disable rising edge trigger */
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            // Configure rising edge trigger
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Enable rising edge trigger */
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Disable falling edge trigger */
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            // Configure both edge trigger
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Enable falling edge trigger */
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Enable rising edge trigger */
        }

        // Configure the GPIO port selection in SYSCFG_EXTICR
        uint8_t extiCRIndex = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4; // Determine which EXTICR register to use
        uint8_t extiCRBitPos = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4) * 4; // Determine the bit position within the EXTICR register
        SYSCFG->EXTICR[extiCRIndex] &= ~(0xF << extiCRBitPos); // Clear the bits
        uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx); // Calculate the port code based on the base address
        SYSCFG_PCLK_EN(); // Enable clock for SYSCFG peripheral
        SYSCFG->EXTICR[extiCRIndex] |= (portCode << extiCRBitPos); // Set the bits

        // Enable EXTI interrupt delivery using IMR
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); /* Enable interrupt delivery from the selected pin */
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

/**
 * @brief  This function writes a value to a specific GPIO output pin.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @param  PinNumber: The pin number to write to (0-15)
 * @param  Value: The value to write (GPIO_PIN_SET or GPIO_PIN_RESET)
 * @retval None
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

/**
 * @brief  This function writes a 16-bit value to all output pins of a GPIO port at once.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @param  Value: The 16-bit value to write (bit 0 = pin 0, bit 15 = pin 15)
 * @retval None
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{    
    pGPIOx->ODR |= Value;
}

/**
 * @brief  This function toggles the state of a specific GPIO output pin.
 * @param  pGPIOx: Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.)
 * @param  PinNumber: The pin number to toggle (0-15)
 * @retval None
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{    
    pGPIOx->ODR ^= (1 << PinNumber);
}


/* IRQ configuration */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            // Configure ISER0 register
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64) // Check if the IRQ number is between 32 and 63
        {
            // Configure ISER1 register
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            // Configure ISER2 register
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        if(IRQNumber <= 31)
        {
            // Configure ICER0 register
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            // Configure ICER1 register
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            // Configure ICER2 register
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }


}

/* IRQ priority configuration */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // Set the priority of the interrupt
    uint8_t iprx = IRQNumber / 4; // Determine which IPR register to use
    uint8_t iprxSection = IRQNumber % 4; // Determine the section within the IPR register
    uint8_t shiftAmount = (8 * iprxSection) + (8 - NO_PR_BITS_IMPLEMENTED); // Calculate the shift amount based on the number of priority bits implemented
    *(NVIC_IPR_BASEADDR + iprx) |= (IRQPriority << shiftAmount); // Set the priority
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
    // Clear the EXTI pending bit corresponding to the pin number
    if(EXTI->PR & (1 << PinNumber))
    {
        // Clear the pending bit by writing 1 to it
        EXTI->PR |= (1 << PinNumber);
    }
}
