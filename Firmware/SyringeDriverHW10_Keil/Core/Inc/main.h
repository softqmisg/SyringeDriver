/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_pwr.h"
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
#define KeySS_Pin GPIO_PIN_13
#define KeySS_GPIO_Port GPIOC
#define KeyPower_Pin GPIO_PIN_1
#define KeyPower_GPIO_Port GPIOA
#define SegNum2_Pin GPIO_PIN_2
#define SegNum2_GPIO_Port GPIOA
#define SegNum1_Pin GPIO_PIN_3
#define SegNum1_GPIO_Port GPIOA
#define BatCur_Pin GPIO_PIN_4
#define BatCur_GPIO_Port GPIOA
#define MotCur_Pin GPIO_PIN_5
#define MotCur_GPIO_Port GPIOA
#define NearEnd_Pin GPIO_PIN_6
#define NearEnd_GPIO_Port GPIOA
#define BatVolt_Pin GPIO_PIN_7
#define BatVolt_GPIO_Port GPIOA
#define SegA_Pin GPIO_PIN_0
#define SegA_GPIO_Port GPIOB
#define SegB_Pin GPIO_PIN_1
#define SegB_GPIO_Port GPIOB
#define SegC_Pin GPIO_PIN_2
#define SegC_GPIO_Port GPIOB
#define LedBat_Pin GPIO_PIN_12
#define LedBat_GPIO_Port GPIOB
#define SwitchFB_Pin GPIO_PIN_15
#define SwitchFB_GPIO_Port GPIOB
#define MOTORP_Pin GPIO_PIN_8
#define MOTORP_GPIO_Port GPIOA
#define LedAlarm_Pin GPIO_PIN_11
#define LedAlarm_GPIO_Port GPIOA
#define LedSS_Pin GPIO_PIN_12
#define LedSS_GPIO_Port GPIOA
#define SegD_Pin GPIO_PIN_3
#define SegD_GPIO_Port GPIOB
#define SegE_Pin GPIO_PIN_4
#define SegE_GPIO_Port GPIOB
#define SegF_Pin GPIO_PIN_5
#define SegF_GPIO_Port GPIOB
#define SegG_Pin GPIO_PIN_6
#define SegG_GPIO_Port GPIOB
#define SegDP_Pin GPIO_PIN_7
#define SegDP_GPIO_Port GPIOB
#define KeyTime_Pin GPIO_PIN_8
#define KeyTime_GPIO_Port GPIOB
#define KeyType_Pin GPIO_PIN_9
#define KeyType_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define DELAY_GOSTANDBY		30

typedef enum {NoneState=0,WakeupState,NormalState,UpState,BolusState,RunState,StandbyState,SetupState} mState_t;
typedef enum {RunNoneState=0,RunOnState,RunOffState} rState_t;
typedef enum {LedBat,LedAlarm,LedSS} Led_t;
extern mState_t machineState;
extern rState_t runState;
extern __IO uint8_t rtc_flag;
extern __IO uint8_t rtc_flag2s;
extern __IO uint8_t rtc_cnt2s;
extern __IO uint8_t rtc_flag5s;
extern __IO uint8_t rtc_cnt5s;
extern __IO uint8_t sysTick_flag2s;
extern __IO uint16_t sysTick_cnt2s;
extern __IO uint8_t sysTick_flag1s;
extern __IO uint16_t sysTick_cnt1s;
void setLED(Led_t led,uint8_t state);

#define __DEBUG__	0
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
