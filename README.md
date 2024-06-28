# MicroSD API

## Descripción

Esta API proporciona una interfaz para interactuar con una tarjeta microSD utilizando el sistema de archivos FatFs y la comunicación UART en un microcontrolador STM32. La API permite inicializar la tarjeta microSD, obtener el tamaño total y el espacio libre, escribir datos, leer datos y agregar líneas a un archivo en la tarjeta microSD.

## Características

- **Inicialización**: Monta el sistema de archivos y configura la UART.
- **Lectura y Escritura**: Permite leer y escribir datos en archivos en la tarjeta microSD.
- **Añadir Líneas**: Agrega nuevas líneas a un archivo existente.
- **Obtener Tamaño**: Obtiene el tamaño total y el espacio libre de la tarjeta microSD.

## Requisitos

- STM32 HAL Library
- FatFs Library
- UART para la comunicación

## Uso

### 1. Inicializar la API

Primero, inicializa la microSD y la UART.

```c
#include "microSD.h"
#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart3;
MicroSD sd;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART3_UART_Init();

    microSD_init(&sd, &huart3, "contador.txt");

    // Tu código aquí...

    while (1) {
        // Bucle principal...
    }

    microSD_deinit(&sd);
}


##fuente 
https://www.youtube.com/watch?v=EW38SwdRktI
# Tesis_SD
