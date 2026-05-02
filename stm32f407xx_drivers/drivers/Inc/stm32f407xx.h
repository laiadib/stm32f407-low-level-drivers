/*
 * stm32f407xx.h
 *
 *  Created on: May 2, 2026
 *      Author: Bilal Laiadi
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>

#define __vo volatile


#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U /* 112 KB */
#define SRAM2_BASEADDR			0x2001C000U /* 16 KB */
#define ROM_BASEADDR			0x1FFF0000U /* system memory */
#define SRAM_BASEADDR			SRAM1_BASEADDR


/* AHBx and APBx Peripheral base addresses */
#define PERIPH_BASEADDR		    0x40000000U
#define APB1PERIPH_BASEADDR	    PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR	    0x40010000U
#define AHB1PERIPH_BASEADDR	    0x40020000U
#define AHB2PERIPH_BASEADDR	    0x50000000U


/* Base addresses of peripherals of AHB1 Bus*/
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000U)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400U)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800U)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00U)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2000U)

#define RCC_BASEADDR            (AHB1PERIPH_BASEADDR + 0x3800U)


/* Base addresses of peripherals of APB1 Bus*/
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00U)

#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00U)

#define USART2_BASEADDR		    (APB1PERIPH_BASEADDR + 0x4400U)
#define USART3_BASEADDR		    (APB1PERIPH_BASEADDR + 0x4800U)
#define UART4_BASEADDR		    (APB1PERIPH_BASEADDR + 0x4C00U)
#define UART5_BASEADDR		    (APB1PERIPH_BASEADDR + 0x5000U)


/* Base addresses of peripherals of APB2 Bus*/
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000U)
#define USART1_BASEADDR		    (APB2PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR		    (APB2PERIPH_BASEADDR + 0x1400U)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00U)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800U)



/* GPIO Register Definition Structure */
typedef struct
{
	__vo uint32_t MODER;             /* GPIO port mode register,                    	        Address offset: 0x00      */                   
	__vo uint32_t OTYPER;            /* GPIO port output type register,            	        Address offset: 0x04      */
	__vo uint32_t OSPEEDR;           /* GPIO port output speed register,           	        Address offset: 0x08      */
	__vo uint32_t PUPDR;             /* GPIO port pull-up/pull-down register,      	        Address offset: 0x0C      */
	__vo uint32_t IDR;               /* GPIO port input data register,             	        Address offset: 0x10      */
	__vo uint32_t ODR;               /* GPIO port output data register,            	        Address offset: 0x14      */
	__vo uint32_t BSRR;              /* GPIO port bit set/reset register,          	        Address offset: 0x18      */
	__vo uint32_t LCKR;              /* GPIO port configuration lock register,     	        Address offset: 0x1C      */
	__vo uint32_t AFR[2];	         /* AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function high register    	Address offset: 0x20-0x24 */
}GPIO_RegDef_t;


/* RCC Register Definition Structure */
typedef struct
{
    __vo uint32_t CR;               /* Address offset: 0x00 */
    __vo uint32_t PLLCFGR;          /* Address offset: 0x04 */
    __vo uint32_t CFGR;             /* Address offset: 0x08 */
    __vo uint32_t CIR;              /* Address offset: 0x0C */
    __vo uint32_t AHB1RSTR;         /* Address offset: 0x10 */
    __vo uint32_t AHB2RSTR;         /* Address offset: 0x14 */
    __vo uint32_t AHB3RSTR;         /* Address offset: 0x18 */
    uint32_t      RESERVED0;        /* Reserved, 0x1C */
    __vo uint32_t APB1RSTR;         /* Address offset: 0x20 */
    __vo uint32_t APB2RSTR;         /* Address offset: 0x24 */
    uint32_t      RESERVED1[2];     /* Reserved, 0x28-0x2C */
    __vo uint32_t AHB1ENR;          /* Address offset: 0x30 */
    __vo uint32_t AHB2ENR;          /* Address offset: 0x34 */
    __vo uint32_t AHB3ENR;          /* Address offset: 0x38 */
    uint32_t      RESERVED2;        /* Reserved, 0x3C */
    __vo uint32_t APB1ENR;          /* Address offset: 0x40 */
    __vo uint32_t APB2ENR;          /* Address offset: 0x44 */
    uint32_t      RESERVED3[2];     /* Reserved, 0x48-0x4C */
    __vo uint32_t AHB1LPENR;        /* Address offset: 0x50 */
    __vo uint32_t AHB2LPENR;        /* Address offset: 0x54 */
    __vo uint32_t AHB3LPENR;        /* Address offset: 0x58 */
    uint32_t      RESERVED4;        /* Reserved, 0x5C */
    __vo uint32_t APB1LPENR;        /* Address offset: 0x60 */
    __vo uint32_t APB2LPENR;        /* Address offset: 0x64 */
    uint32_t      RESERVED5[2];     /* Reserved, 0x68-0x6C */
    __vo uint32_t BDCR;             /* Address offset: 0x70 */
    __vo uint32_t CSR;              /* Address offset: 0x74 */
    uint32_t      RESERVED6[2];     /* Reserved, 0x78-0x7C */
    __vo uint32_t SSCGR;            /* Address offset: 0x80 */
    __vo uint32_t PLLI2SCFGR;       /* Address offset: 0x84 */
    __vo uint32_t PLLSAICFGR;       /* Address offset: 0x88 */
    __vo uint32_t DCKCFGR;          /* Address offset: 0x8C */
    __vo uint32_t CKGATENR;         /* Address offset: 0x90 */
    __vo uint32_t DCKCFGR2;         /* Address offset: 0x94 */
} RCC_RegDef_t;


/* GPIO Peripheral Definitions */
#define GPIOA               ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB               ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC               ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD               ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE               ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF               ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG               ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH               ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI               ((GPIO_RegDef_t*)GPIOI_BASEADDR)


/* RCC Peripheral Definition */
#define RCC                 ((RCC_RegDef_t*)RCC_BASEADDR)


/* Clock Enable Macros for GPIOx peripherals */
#define GPIOA_PCLK_EN()  (RCC->AHB1ENR |= (1 << 0))   /* Enable clock for GPIOA */
#define GPIOB_PCLK_EN()  (RCC->AHB1ENR |= (1 << 1))   /* Enable clock for GPIOB */
#define GPIOC_PCLK_EN()  (RCC->AHB1ENR |= (1 << 2))   /* Enable clock for GPIOC */
#define GPIOD_PCLK_EN()  (RCC->AHB1ENR |= (1 << 3))   /* Enable clock for GPIOD */
#define GPIOE_PCLK_EN()  (RCC->AHB1ENR |= (1 << 4))   /* Enable clock for GPIOE */
#define GPIOF_PCLK_EN()  (RCC->AHB1ENR |= (1 << 5))   /* Enable clock for GPIOF */
#define GPIOG_PCLK_EN()  (RCC->AHB1ENR |= (1 << 6))   /* Enable clock for GPIOG */
#define GPIOH_PCLK_EN()  (RCC->AHB1ENR |= (1 << 7))   /* Enable clock for GPIOH */
#define GPIOI_PCLK_EN()  (RCC->AHB1ENR |= (1 << 8))   /* Enable clock for GPIOI */

/* Clock Disable Macros for GPIOx peripherals */
#define GPIOA_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 0))   /* Disable clock for GPIOA */
#define GPIOB_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 1))   /* Disable clock for GPIOB */
#define GPIOC_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 2))   /* Disable clock for GPIOC */
#define GPIOD_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 3))   /* Disable clock for GPIOD */
#define GPIOE_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 4))   /* Disable clock for GPIOE */
#define GPIOF_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 5))   /* Disable clock for GPIOF */
#define GPIOG_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 6))   /* Disable clock for GPIOG */
#define GPIOH_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 7))   /* Disable clock for GPIOH */
#define GPIOI_PCLK_DI()  (RCC->AHB1ENR &= ~(1 << 8))   /* Disable clock for GPIOI */



/* Clock Enable Macros for I2C peripherals */
#define I2C1_PCLK_EN()  (RCC->APB1ENR |= (1 << 21))   /* Enable clock for I2C1 */
#define I2C2_PCLK_EN()  (RCC->APB1ENR |= (1 << 22))   /* Enable clock for I2C2 */
#define I2C3_PCLK_EN()  (RCC->APB1ENR |= (1 << 23))   /* Enable clock for I2C3 */

/* Clock Disable Macros for I2C peripherals */
#define I2C1_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 21))   /* Disable clock for I2C1 */
#define I2C2_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 22))   /* Disable clock for I2C2 */
#define I2C3_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 23))   /* Disable clock for I2C3 */


/* Clock Enable Macros for SPIx peripherals */
#define SPI1_PCLK_EN()  (RCC->APB2ENR |= (1 << 12))   /* Enable clock for SPI1 */
#define SPI2_PCLK_EN()  (RCC->APB1ENR |= (1 << 14))   /* Enable clock for SPI2 */
#define SPI3_PCLK_EN()  (RCC->APB1ENR |= (1 << 15))   /* Enable clock for SPI3 */
#define SPI4_PCLK_EN()  (RCC->APB2ENR |= (1 << 13))   /* Enable clock for SPI4 */

/* Clock Disable Macros for SPIx peripherals */
#define SPI1_PCLK_DI()  (RCC->APB2ENR &= ~(1 << 12))   /* Disable clock for SPI1 */
#define SPI2_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 14))   /* Disable clock for SPI2 */
#define SPI3_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 15))   /* Disable clock for SPI3 */
#define SPI4_PCLK_DI()  (RCC->APB2ENR &= ~(1 << 13))   /* Disable clock for SPI4 */


/* Clock Enable Macros for USARTx peripherals */
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1 << 4))    /* Enable clock for USART1 */
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1 << 17))   /* Enable clock for USART2 */
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1 << 18))   /* Enable clock for USART3 */
#define UART4_PCLK_EN()  (RCC->APB1ENR |= (1 << 19))   /* Enable clock for UART4 */
#define UART5_PCLK_EN()  (RCC->APB1ENR |= (1 << 20))   /* Enable clock for UART5 */
#define USART6_PCLK_EN() (RCC->APB1ENR |= (1 << 5))    /* Enable clock for USART6 */

/* Clock Disable Macros for USARTx peripherals */
#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1 << 4))    /* Disable clock for USART1 */
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 17))   /* Disable clock for USART2 */
#define USART3_PCLK_DI() (RCC->APB1ENR &= ~(1 << 18))   /* Disable clock for USART3 */
#define UART4_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 19))   /* Disable clock for UART4 */
#define UART5_PCLK_DI()  (RCC->APB1ENR &= ~(1 << 20))   /* Disable clock for UART5 */
#define USART6_PCLK_DI() (RCC->APB1ENR &= ~(1 << 5))    /* Disable clock for USART6 */


/* Clock Enable Macros for SYSCFG peripheral */
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1 << 14))   /* Enable clock for SYSCFG */

/* Clock Disable Macros for SYSCFG peripheral */
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1 << 14))   /* Disable clock for SYSCFG */


/* Generic macros */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET

#endif /* INC_STM32F407XX_H_ */
