/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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


// countdown_busy=1 durante semáforo; ignoras pulsos.
// race_active=0 antes del semáforo y tras ganador; ignoras pulsos.
// game_over=1 al declarar ganador; ignoras pulsos.


volatile uint8_t start_request   = 0;   // Pedir que arranque el semáforo
volatile uint8_t countdown_busy  = 0;	// bloquea durante semáforo (TRUE mientras corre el semáforo)
volatile uint8_t race_active     = 0;	// carrera habilitada tras semáforo (TRUE: se aceptan pulsos de jugadores)
volatile uint8_t game_over       = 0;	// TRUE cuando hay ganador, se bloquea todo

volatile uint32_t btn_last_ms    = 0;	// anti-rebote botón inicio
volatile uint32_t btn1_last_ms   = 0;	// anti-rebote botón J1
volatile uint32_t btn2_last_ms	 = 0;	// anti-rebote botón J2

volatile uint8_t  j1_mask = 0x01, j2_mask = 0x01;	// "posición del LED"
volatile uint8_t  j1_laps = 0,     j2_laps = 0;		// número de vueltas
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void Semaforo_ReadyGo(void);
static void J1_UpdateLeds(uint8_t mask);
static void J2_UpdateLeds(uint8_t mask);
static void Game_Reset(void);
static void DeclareWinner(uint8_t who);	// 1 = J1, 2 = J2
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Escribe mask (bits 0..7) en PB0..PB7
// mask para que solo un bit sea 1 y el resto sea 0
// 0x01 (LED en la posición 0)...0x80 (LED en la posición 7)
static void J1_UpdateLeds(uint8_t mask) { GPIOB->ODR = (GPIOB->ODR & ~0x00FF) | (mask & 0x00FF); }
static void J2_UpdateLeds(uint8_t mask) { GPIOC->ODR = (GPIOC->ODR & ~0x00FF) | (mask & 0x00FF); }

static void Game_Reset(void)
{
  // Apaga indicadores de ganador   b b
  HAL_GPIO_WritePin(LED_WIN_J1_GPIO_Port, LED_WIN_J1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_WIN_J2_GPIO_Port, LED_WIN_J2_Pin, GPIO_PIN_RESET);

  // Reinicia posiciones y vueltas
  j1_mask = 0x01; j2_mask = 0x01;
  j1_laps = 0;     j2_laps = 0;

  J1_UpdateLeds(j1_mask);
  J2_UpdateLeds(j2_mask);

  game_over   = 0;	// todavía no hay ganador
  race_active = 0;	// aún no se aceptan pulsos de los jugadores (los pulsos se ignoran)
}

static void DeclareWinner(uint8_t who)
{
  game_over = 1;     // congela la carrera
  race_active = 0;
// Parámetro who = 1; si el ganador es el J1. Who = 2; ganador es el J2.
// según el valor (jugador que gana) enciende el LED ganador
  if (who == 1) {
    HAL_GPIO_WritePin(LED_WIN_J1_GPIO_Port, LED_WIN_J1_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(LED_WIN_J2_GPIO_Port, LED_WIN_J2_Pin, GPIO_PIN_SET);
  }
}

// Función de semáforo
static void Semaforo_ReadyGo(void)
{
  countdown_busy = 1;	// bloquea callbacks mientras corre la secuencia

  // Rojo
  HAL_GPIO_WritePin(LED_ROJO_GPIO_Port, LED_ROJO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_AMARILLO_GPIO_Port, LED_AMARILLO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_VERDE_GPIO_Port, LED_VERDE_Pin, GPIO_PIN_RESET);
  HAL_Delay(1000);

  // Amarillo
  HAL_GPIO_WritePin(LED_ROJO_GPIO_Port, LED_ROJO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_AMARILLO_GPIO_Port, LED_AMARILLO_Pin, GPIO_PIN_SET);
  HAL_Delay(1000);

  // Verde
  HAL_GPIO_WritePin(LED_AMARILLO_GPIO_Port, LED_AMARILLO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_VERDE_GPIO_Port, LED_VERDE_Pin, GPIO_PIN_SET);
  HAL_Delay(1000);

  // Limpia
  HAL_GPIO_WritePin(LED_VERDE_GPIO_Port, LED_VERDE_Pin, GPIO_PIN_RESET);

  countdown_busy = 0;	// habilita los callbacks
}
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

  /* Reset of all peripheralsvuuvvvvvvvvvvvvvvvvvvvvvv666 c6               c, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  // Deja el juego en estado conocido, enciende la primera posición de cada pista de carrera
  J1_UpdateLeds(j1_mask);
  J2_UpdateLeds(j2_mask);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Lanzar carrera con semáforo
	  // el botón de inicio (PC13) en el callback pone start_request = 1, para ejecutar el semáforo...
	  // ...seguido del juego

	  if (start_request && !countdown_busy) {
	    start_request = 0;
	    Game_Reset();           // limpia ANTES del semáforo, se "reinicia" posiciones y vueltas
		Semaforo_ReadyGo();     // corre Rojo→Amarillo→Verde (bloquea con countdown_busy)
		race_active = 1;        // carrera habilitada, se aceptan pulsos
	  }

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint32_t now = HAL_GetTick();

  // Inicio (PC13)
  if (GPIO_Pin == BTN_INICIO_Pin) {	// PC13 (RISING, pull-down), btn_last_ms es la marca de tiempo del último pulso
    if ((now - btn_last_ms) > 200 && !countdown_busy) {	// asegura que hayan pasado al menos 200 ms desde la última vez
      // countdown_busy asegura que no se pueda reiniciar el semáforo, mientras este en secuencia.
    	start_request = 1;	// no arranca el semáforo aquí, solo levanta la bandera, el while activa el semáfor con la bandera
      btn_last_ms = now;	// guarda el tiempo de esta pulsación para el próximo chequeo
    }
  }

  // Jugador 1 (PA15)
  if (GPIO_Pin == BTN_J1_Pin) {	// PA15 (FALLING, pull-up)
    if ((now - btn1_last_ms) > 250) {
      btn1_last_ms = now;	// guarda el tiempo de esta pulsación para el próximo chequeo
      // cumplen las condiciones?...si se cumplen todas las condiciones, el jugador puede avanzar
      // ...race_active = 1; la carrera ya empezó.
      // ...!countdown_busy; no esta en el semáforo.
      // ...!game_over; no hay ganador aún.
      if (race_active && !countdown_busy && !game_over) {
    	  // Si j1_mask == 0x80 (último LED de la pista): se reinicia a 0x01 (primer LED) y aumenta cont de vueltas (j1_laps)
        if (j1_mask == 0x80) {j1_mask = 0x01; j1_laps++; } else { j1_mask <<= 1; }
        J1_UpdateLeds(j1_mask);	// Escribe el nuevo estado, asegura que se encienda un LED y el indicado.
        if (j1_laps >= 3) { DeclareWinner(1); }	// Si j1_laps >= 3, el jugador gana, enciende LED ganador y congela el juego.
        // ...game_over=1, race_active=0
      }
    }
  }

// 0x01 = 0000 0001 = PB0
// 0x02 = 0000 0010 = PB1
// 0x04 = 0000 0100 = PB2
// 0x08 = 0000 1000 = PB3
// 0x10 = 0001 0000 = PB4
// 0x20 = 0010 0000 = PB5
// 0x40 = 0100 0000 = PB6
// 0x80 = 1000 0000 = PB7

  // Jugador 2 (PB15) (misma lógica que el jugador1...)
  if (GPIO_Pin == BTN_J2_Pin) {	// PB14 (FALLING, pull-up)
    if ((now - btn2_last_ms) > 250) {
      btn2_last_ms = now;
      if (race_active && !countdown_busy && !game_over) {
        if (j2_mask == 0x80) { j2_mask = 0x01; j2_laps++; } else { j2_mask <<= 1; }
        J2_UpdateLeds(j2_mask);
        if (j2_laps >= 3) { DeclareWinner(2); }
      }
    }
  }
}

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
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
