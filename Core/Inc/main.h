/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_INICIO_Pin GPIO_PIN_13
#define BTN_INICIO_GPIO_Port GPIOC
#define BTN_INICIO_EXTI_IRQn EXTI15_10_IRQn
#define J2L0_Pin GPIO_PIN_0
#define J2L0_GPIO_Port GPIOC
#define J2L1_Pin GPIO_PIN_1
#define J2L1_GPIO_Port GPIOC
#define J2L2_Pin GPIO_PIN_2
#define J2L2_GPIO_Port GPIOC
#define J2L3_Pin GPIO_PIN_3
#define J2L3_GPIO_Port GPIOC
#define LED_WIN_J1_Pin GPIO_PIN_0
#define LED_WIN_J1_GPIO_Port GPIOA
#define LED_WIN_J2_Pin GPIO_PIN_1
#define LED_WIN_J2_GPIO_Port GPIOA
#define LED_VERDE_Pin GPIO_PIN_5
#define LED_VERDE_GPIO_Port GPIOA
#define LED_AMARILLO_Pin GPIO_PIN_6
#define LED_AMARILLO_GPIO_Port GPIOA
#define LED_ROJO_Pin GPIO_PIN_7
#define LED_ROJO_GPIO_Port GPIOA
#define J2L4_Pin GPIO_PIN_4
#define J2L4_GPIO_Port GPIOC
#define J2L5_Pin GPIO_PIN_5
#define J2L5_GPIO_Port GPIOC
#define J1L0_Pin GPIO_PIN_0
#define J1L0_GPIO_Port GPIOB
#define J1L1_Pin GPIO_PIN_1
#define J1L1_GPIO_Port GPIOB
#define J1L2_Pin GPIO_PIN_2
#define J1L2_GPIO_Port GPIOB
#define BTN_J2_Pin GPIO_PIN_14
#define BTN_J2_GPIO_Port GPIOB
#define BTN_J2_EXTI_IRQn EXTI15_10_IRQn
#define J2L6_Pin GPIO_PIN_6
#define J2L6_GPIO_Port GPIOC
#define J2L7_Pin GPIO_PIN_7
#define J2L7_GPIO_Port GPIOC
#define BTN_J1_Pin GPIO_PIN_15
#define BTN_J1_GPIO_Port GPIOA
#define BTN_J1_EXTI_IRQn EXTI15_10_IRQn
#define J1L3_Pin GPIO_PIN_3
#define J1L3_GPIO_Port GPIOB
#define J1L4_Pin GPIO_PIN_4
#define J1L4_GPIO_Port GPIOB
#define J1L5_Pin GPIO_PIN_5
#define J1L5_GPIO_Port GPIOB
#define J1L6_Pin GPIO_PIN_6
#define J1L6_GPIO_Port GPIOB
#define J1L7_Pin GPIO_PIN_7
#define J1L7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
