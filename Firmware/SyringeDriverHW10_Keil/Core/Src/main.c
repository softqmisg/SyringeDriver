/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file           : main.c
	* @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "user_keypad.h"
#include "user_buzzer.h"
#include "Tones_Pitches.h"
#include "user_sevensegment.h"
#include "user_eeprom.h"
#include "user_pwr.h"
#include "user_syringe.h"
#include "user_motor.h"
#include "user_adc.h"
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
	
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
mState_t machineState=NoneState;
// ----------------------Systick callback-----------------------------------------
#define LED_TOGGLE_DELAY  100 //2000*1ms=2s
static __IO uint32_t TimingDelay=0;
void HAL_SYSTICK_Callback(void)
{  
//  if(state==UpState)
//  {
//    if(TimingDelay!=0)
//    {
//      TimingDelay--;
//    }
//    else
//    {
//      HAL_GPIO_TogglePin(LedBat_GPIO_Port,LedBat_Pin);
//      TimingDelay = LED_TOGGLE_DELAY;    
//    }
//  }  
}
/*----------------------------------------------------------------------*/
__IO uint8_t rtc_flag=0;
__IO uint8_t rtc_flag2s=0;
__IO uint8_t rtc_cnt2s=0;
__IO uint8_t GoStandbyCnt=0;
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
	rtc_flag=1;
	rtc_cnt2s++;
	if(rtc_cnt2s>1)
	{
		rtc_cnt2s=0;
		rtc_flag2s=1;
	}
	if(GoStandbyCnt)
		GoStandbyCnt--;	
}
/*----------------------------------------------------------------------*/
__IO uint8_t cnvCompleted=0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	cnvCompleted=1;
}
/*----------------------------------------------------------------------*/
typedef enum {LedBat,LedAlarm,LedSS} Led_t;
void setLED(Led_t led,uint8_t state)
{
	GPIO_TypeDef *port;
	uint16_t pin;
	switch(led)
	{
		case LedBat:
			port=LedBat_GPIO_Port;
			pin=LedBat_Pin;
			break;
		case LedAlarm:
			port=LedAlarm_GPIO_Port;
			pin=LedAlarm_Pin;			
			break;
		case LedSS:
			port=LedSS_GPIO_Port;
			pin=LedSS_Pin;			
		break;
	}
	GPIO_PinState pinstate=(state)?GPIO_PIN_SET:GPIO_PIN_RESET;
	HAL_GPIO_WritePin(port,pin,pinstate);
}
/*----------------------------------------------------------------------*/
void checkingSystem(void)
{
	char msg[3];
	setLED(LedBat,1);
	setLED(LedAlarm,1);
	setLED(LedSS,1);
	printDPSegs(" .");
	HAL_Delay(500);
	playTone(toneBeep);
	clearSegs();
	setLED(LedBat,0);
	setLED(LedAlarm,0);
	setLED(LedSS,0);
	for(uint8_t i=0;i<9;i++)
	{
		sprintf(msg,"%d%d",i,i);
		printSegs(msg,0);
		HAL_Delay(200);		
	}
	printDPSegs("..");HAL_Delay(200);
	clearSegs();	
	playTone(tonePowerWake);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char msg[3];
	uint8_t menu_index=0;
	uint16_t tmp_uint16t=0;
	uint8_t submenuIndex=0;
	uint8_t typeSwitchcnt;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	initSegs();
	HAL_FLASH_Unlock();
	__HAL_RTC_ALARM_ENABLE_IT(&hrtc,RTC_IT_SEC);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint16_t *tones[]={tonePowerWake,toneKeyPress,toneBeep,toneAlarm,toneSave,toneEnterSetup,toneStartRun};
	uint8_t tonenum=0;
sprintf(msg,"%02d",tonenum+1);
printSegs(msg,0);
//	playToneReverse(tones[tonenum]);
	playTone(toneStopRun);
	while (1)
	{
		keypadRead();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(isKeyHold(KeySS))
		{
			//muteTone();
			playTone(toneStopRun);
		}
		if(isKeyPress(KeyPower))
		{
			playToneReverse(tones[tonenum]);
		}
		if(isKeyPress(KeySS))
		{
			playTone(tones[tonenum]);
		}
		if(isKeyPress(KeyTime))
		{
			tonenum++;
			if(tonenum>=TONESNUMBER)
				tonenum=0;
			sprintf(msg,"%02d",tonenum+1);
			printSegs(msg,0);
		}
		if(isKeyPress(KeyType))
		{
			if(tonenum==0)
				tonenum=TONESNUMBER;
			tonenum--;
			sprintf(msg,"%02d",tonenum+1);
			printSegs(msg,0);			
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
	while (1)
	{
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
