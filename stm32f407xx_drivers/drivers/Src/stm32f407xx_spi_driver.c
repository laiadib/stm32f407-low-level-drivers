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


