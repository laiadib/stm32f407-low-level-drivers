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
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR); // Set the baud rate control bits

    // Configure the data frame format
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF); // Set the DFF bit for 8-bit or 16-bit data frame format

    // Configure the clock polarity
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL); // Set the CPOL bit for clock polarity

    // Configure the clock phase
    pSPIHandle->pSPIx->CR1 |= (pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA); // Set the CPHA bit for clock phase

}

/* De-initialization */
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

