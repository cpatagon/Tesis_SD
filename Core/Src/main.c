/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "time_rtc.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include <stdio.h>  // Añade esto para sprintf
#include <string.h> // Añade esto para strlen
#include "uart.h"
#include "microSD.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */



// I2C_HandleTypeDef hi2c2;

// UART_HandleTypeDef huart1;

//	struct sps30_measurement m;
//	char serial[SPS30_MAX_SERIAL_LEN];
//	const uint8_t AUTO_CLEAN_DAYS = 4;
//	    int16_t ret;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

    // SPS30_Init(&huart5);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_I2C2_Init();
  MX_FATFS_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  //UART_HandleTypeDef huart3;


  // Crea una nueva instancia de MicroSD
      MicroSD *sd = microSD_create(&huart3, "contador.txt", "/"); // Inicialización con el directorio raíz
      if (sd == NULL) {
          // Manejar error de creación
          Error_Handler();
      }
  microSD_setDirectory(sd, "/"); // Cambia el directorio según sea necesario

  //microSD_read(&sd);
  //microSD_deinit(&sd);

  int contador = 1;
  char buffer[100];  // Buffer para la cadena del contador

    //	uint32_t counter = 0; // Variable del contador
    //	char buffer[50]; // Buffer para almacenar el mensaje a enviar
    /* mensaje con los parametros de configuracion de la UART */
    /*static uint8_t * message =
        (uint8_t *)"\n\n"
                   "-----------------------------------------------------------\n"
                   "*** UART port initialization successful !!! ***\n"
                   "-----------------------------------------------------------\n";

    HAL_UART_Transmit(&huart3, (uint8_t *)message, strlen((char *)message), HAL_MAX_DELAY);

    uart_print("\n*********************************************\n");
*/

    /* Start DS1307 timing. Pass user I2C handle pointer to function. */

  //  time_rtc_Init(&hi2c2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    /*buffer donde se imprimira la fecha */
  //  char buffer[100] = {0};

    while (1) {
    	  snprintf(buffer, sizeof(buffer), "%d", contador);  // Convierte el contador a cadena
    	  microSD_appendLine(sd, buffer);  // Escribe la cadena en el archivo
    	  contador++;  // Incrementa el contador
    	  HAL_Delay(5000);  // Espera 5 segundos

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        // Enviar mensaje a través de UART
        // uart_print(buffer);
     //   uart_print("\n*********************************************\n");
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
