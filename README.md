# stm32f407-low-level-drivers

Low-level peripheral drivers for the STM32F407xx microcontrollers, written without HAL or CMSIS drivers.

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
| Peripheral | Status |
|------------|--------|
| GPIO       | Done   |

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
