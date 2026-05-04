# STM32F407 Low-level Drivers

Low-level peripheral drivers for the STM32F407xx microcontrollers, written without vendor abstraction layers.

## Target Hardware
- **MCU:** STM32F407xx 
- **Board:** STM32F4-Discovery

## Project Structure
```
stm32f407xx_drivers/
├── drivers/
│   ├── Inc/        # Driver header files
│   └── Src/        # Driver source files
├── Inc/            # Application headers (app_select.h, user_app.h)
├── Src/            # Application source (main.c, user_app.c)
└── Startup/        # Startup assembly file
```

## Implemented Drivers
| Peripheral | Status      |
|------------|-------------|
| GPIO       | Completed   |
| SPI        | In Progress |
| I2C        | Backlog     |
| USART      | Backlog     |

## GPIO Driver API

The GPIO driver currently exposes the following APIs:

### Peripheral clock
- `void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);`

### Initialization and de-initialization
- `void GPIO_Init(GPIO_Handle_t *pGPIOHandle);`
- `void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);`

### Data read and write
- `uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);`
- `uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);`
- `void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);`
- `void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);`
- `void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);`

### IRQ configuration and handling
- `void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);`
- `void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);`
- `void GPIO_IRQHandling(uint8_t PinNumber);`

## Demo Applications
Switch the active app by editing `APP_SELECTED` in `Inc/app_select.h`:

| Macro                     | Description                              |
|---------------------------|------------------------------------------|
| `APP_LED_TOGGLE`          | Blink LED on PD12 using a software delay |
| `APP_LED_TOGGLE_BUTTON`   | Toggle LED on PD12 when PA0 is pressed   |
| `APP_LED_TOGGLE_BUTTON_IT`| Toggle LED via EXTI0 interrupt on PA0    |
| `APP_NONE`                | Empty infinite loop (safe no-op)         |

## Build
Open the project in **STM32CubeIDE** and build using the `Debug` configuration.
