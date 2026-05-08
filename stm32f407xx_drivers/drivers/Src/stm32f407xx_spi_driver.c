/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: May 6, 2026
 *      Author: Bilal Laiadi
 */

#include "stm32f407xx_spi_driver.h"

/* API supported by this driver */

/* Peripheral Clock setup */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        switch((uintptr_t)pSPIx)
        {
            case (uintptr_t)SPI1: SPI1_PCLK_EN(); break;
            case (uintptr_t)SPI2: SPI2_PCLK_EN(); break;
            case (uintptr_t)SPI3: SPI3_PCLK_EN(); break;
            case (uintptr_t)SPI4: SPI4_PCLK_EN(); break;
            default: break;
        }
    }
    else
    {
        switch((uintptr_t)pSPIx)
        {
            case (uintptr_t)SPI1: SPI1_PCLK_DI(); break;
            case (uintptr_t)SPI2: SPI2_PCLK_DI(); break;
            case (uintptr_t)SPI3: SPI3_PCLK_DI(); break;
            case (uintptr_t)SPI4: SPI4_PCLK_DI(); break;
            default: break;
        }
    }
}


/* Initialization */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // Enable the peripheral clock
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    // Configure the SPI_CR1 register based on the settings in SPIConfig
    pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_MSTR); // Clear the MSTR bit
    pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR; // Set the device mode (master/slave)

    // Configure the bus configuration
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX)
    {
        pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE); // Clear BIDIMODE for full-duplex
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX)
    {
        pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_BIDIMODE); // Set BIDIMODE for half-duplex
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE); // Clear BIDIMODE for full-duplex
        pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_RXONLY); // Set RXONLY for simplex receive-only mode
    }

    // Configure the SCLK speed
    pSPIHandle->pSPIx->CR1 &= ~(0x7 << SPI_CR1_BR); // Clear the baud rate control bits  
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR); // Set the baud rate control bits

    // Configure the data frame format
    pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_DFF); // Clear the DFF bit
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF); // Set the DFF bit for 8-bit or 16-bit data frame format

    // Configure the clock polarity
    pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_CPOL); // Clear the CPOL bit  
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL); // Set the CPOL bit for clock polarity

    // Configure the clock phase
    pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_CPHA); // Clear the CPHA bit  
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA); // Set the CPHA bit for clock phase

    // Configure software slave management
    pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SSM); // Clear the SSM bit
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM); // Set or clear SSM based on configuration
}


/**
 * @brief  De-initializes the SPI peripheral.
 * @param  pSPIx: Pointer to the SPI peripheral.
 * @retval None
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    switch((uintptr_t)pSPIx)
    {
        case (uintptr_t)SPI1: SPI1_REG_RESET(); break;
        case (uintptr_t)SPI2: SPI2_REG_RESET(); break;
        case (uintptr_t)SPI3: SPI3_REG_RESET(); break;
        case (uintptr_t)SPI4: SPI4_REG_RESET(); break;
        default: break;
    }
}

/**
 * @brief  Sends data through the SPI peripheral.
 * @param  pSPIx: Pointer to the SPI peripheral.
 * @param  pTxBuffer: Pointer to the data buffer to be transmitted.
 * @param  Len: Length of the data to be transmitted.
 * @retval None
 * @note   This function is blocking and will wait until the transmission is complete.
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        // Wait until TXE (Transmit buffer empty) flag is set
        while(!(pSPIx->SR & (1 << 1))); // 1: Tx buffer empty, 0: Tx buffer not empty

        // Check the DFF (Data Frame Format) bit in CR1
        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            // 16-bit DFF
            pSPIx->DR = *((uint16_t*)pTxBuffer);
            Len -= 2;
            pTxBuffer += 2; // Move the pointer by 2 bytes for 16-bit data
        }
        else
        {
            // 8-bit DFF
            pSPIx->DR = *pTxBuffer;
            Len--;
            pTxBuffer++;
        }
    }

    // Wait until SPI is not busy
    while(pSPIx->SR & (1 << 7));
}


/* Other peripheral control APIs */

/**
 * @brief  Enables or disables the SPI peripheral.
 * @param  pSPIx: Pointer to the SPI peripheral.
 * @param  EnorDi: Enable or disable the SPI peripheral (ENABLE or DISABLE).
 * @retval None
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE); // Set the SPE bit to enable the SPI peripheral
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE); // Clear the SPE bit to disable the SPI peripheral
    }
}

/**
 * @brief  Configures the SSI (Internal Slave Select) bit of the SPI peripheral.
 * @param  pSPIx: Pointer to the SPI peripheral.
 * @param  EnorDi: Enable or disable the SSI bit (ENABLE or DISABLE).
 * @retval None
 * @note   This function is used only when software slave management (SSM) is enabled.
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI); // Set the SSI bit
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI); // Clear the SSI bit
    }
}

/**
 * @brief  Configures the direction of the SPI peripheral in half-duplex mode.
 * @param  pSPIx: Pointer to the SPI peripheral.
 * @param  TxOrRx: Direction of the SPI peripheral (SPI_BIDIRECTIONAL_LINE_TX or SPI_BIDIRECTIONAL_LINE_RX).
 * @retval None
 * @note   This function is used only in half-duplex mode.
 */
void SPI_SetHalfDuplexDirection(SPI_RegDef_t *pSPIx, uint8_t TxOrRx)
{
    if(TxOrRx == SPI_BIDIRECTIONAL_LINE_TX)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_BIDIOE); // Drive the single data line as output
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIOE); // Release the single data line for input
    }
}
