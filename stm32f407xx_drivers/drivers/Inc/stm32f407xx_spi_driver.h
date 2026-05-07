/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: May 6, 2026
 *      Author: Bilal Laiadi
 */


#ifndef STM32F407XX_SPI_DRIVER_H
#define STM32F407XX_SPI_DRIVER_H
#include "stm32f407xx.h"

typedef struct
{
    uint8_t SPI_DeviceMode; /* possible values from @SPI_DEVICE_MODES */
    uint8_t SPI_BusConfig;  /* possible values from @SPI_BUS_CONFIG */
    uint8_t SPI_SclkSpeed;  /* possible values from @SPI_SCLK_SPEED */
    uint8_t SPI_DFF;        /* possible values from @SPI_DFF */
    uint8_t SPI_CPOL;       /* possible values from @SPI_CPOL */
    uint8_t SPI_CPHA;       /* possible values from @SPI_CPHA */
    uint8_t SPI_SSM;        /* possible values from @SPI_SSM */
} SPI_Config_t;

typedef struct
{
    SPI_RegDef_t *pSPIx; /* This holds the base address of the SPI peripheral to which the pin belongs */
    SPI_Config_t SPIConfig; /* This holds SPI configuration settings */
} SPI_Handle_t;

/* Macros for SPI device modes */
/* @SPI_DEVICE_MODES */
#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE  0

/* Macros for SPI bus configuration */
/* @SPI_BUS_CONFIG */
#define SPI_BUS_CONFIG_FULL_DUPLEX 1
#define SPI_BUS_CONFIG_HALF_DUPLEX 2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3 


/* Macros for SPI SCLK speed */
/* @SPI_SCLK_SPEED */
#define SPI_SCLK_SPEED_DIV2   0
#define SPI_SCLK_SPEED_DIV4   1
#define SPI_SCLK_SPEED_DIV8   2
#define SPI_SCLK_SPEED_DIV16  3
#define SPI_SCLK_SPEED_DIV32  4
#define SPI_SCLK_SPEED_DIV64  5
#define SPI_SCLK_SPEED_DIV128 6
#define SPI_SCLK_SPEED_DIV256 7

/* Macros for SPI data frame format */
/* @SPI_DFF */
#define SPI_DFF_8BITS  0
#define SPI_DFF_16BITS 1

/* Macros for SPI clock polarity */
/* @SPI_CPOL */
#define SPI_CPOL_LOW  0
#define SPI_CPOL_HIGH 1

/* Macros for SPI clock phase */
/* @SPI_CPHA */
#define SPI_CPHA_LOW  0
#define SPI_CPHA_HIGH 1

/* Macros for SPI software slave management */
/* @SPI_SSM */
#define SPI_SSM_EN  1
#define SPI_SSM_DI  0

/* API supported by this driver */

/* Peripheral Clock setup */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/* Initialization and De-initialization */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/* Data Send and Receive */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/* IRQ Configuration and ISR handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

#endif /* STM32F407XX_SPI_DRIVER_H */