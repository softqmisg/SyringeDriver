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
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <keypad.h>
#include <stdio.h>
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
// ---------------------------------------------------------------
__STATIC_INLINE void SYSCLKConfig_FromSTOP(void)
{
  /* Customize process using LL interface to improve the performance 
     (wake-up time from STOP quicker in LL than HAL)*/  
  /* HSE configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1) {};

  /* Main PLL activation */
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  };
  
  /* SYSCLK activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
  {
  };
}
// ----------------------Systick callback-----------------------------------------
enum {NoneState,UpState,RunState} state=NoneState;
#define LED_TOGGLE_DELAY	100 //2000*1ms=2s
static __IO uint32_t TimingDelay=0;
void HAL_SYSTICK_Callback(void)
{	
	if(state==RunState)
	{
		HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_RESET);
	}
	else if(state==UpState)
	{
		if(TimingDelay!=0)
		{
			TimingDelay--;
		}
		else
		{
			HAL_GPIO_TogglePin(LedSS_GPIO_Port,LedSS_Pin);
			TimingDelay = LED_TOGGLE_DELAY;		
		}
	}	
}
//-----------------------------------------------------
void HAL_RTCEx_RTCEventErrorCallback(RTC_HandleTypeDef *hrtc)
{
		SYSCLKConfig_FromSTOP();
	HAL_GPIO_TogglePin(LedBat_GPIO_Port,LedBat_Pin);
}
//-----------------------------------------------------
static __IO uint8_t awu_wakup_cnt=0;
__IO uint8_t awu_wakup=0;
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	RTC_TimeTypeDef sTime = {0};
	SYSCLKConfig_FromSTOP();
	HAL_ResumeTick();
	HAL_GPIO_TogglePin(LedAlarm_GPIO_Port,LedAlarm_Pin);
	awu_wakup_cnt++;
	if(awu_wakup_cnt>7) awu_wakup_cnt=0;
		awu_wakup=1;
}
//-----------------------------------------------------
void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin)
{
		keypadRead();		
	if(gpio_pin==KeySS_Pin || gpio_pin ==KeyPower_Pin)
	{
		SYSCLKConfig_FromSTOP();
		HAL_ResumeTick();
		HAL_GPIO_WritePin(LedAlarm_GPIO_Port,LedAlarm_Pin,GPIO_PIN_SET);
		HAL_PWR_DisableSleepOnExit();
	}
}
// ---------------------------------------------------------------
void gotoStopMode(void)
{
	state=RunState;
  __IO uint32_t index = 0;
  GPIO_InitTypeDef  GPIO_InitStruct;
	
  GPIO_InitStruct.Pin = KeySS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KeySS_GPIO_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);//PORTC.13

  GPIO_InitStruct.Pin = KeyPower_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(KeyPower_GPIO_Port, &GPIO_InitStruct);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);//PORTA.1
	
	RTC_TimeTypeDef sTime = {0};
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
  RTC_AlarmTypeDef  RTC_AlarmStruct;
  RTC_AlarmStruct.AlarmTime.Hours=0x00;
	RTC_AlarmStruct.AlarmTime.Minutes=0x00;
	RTC_AlarmStruct.AlarmTime.Seconds=10;
	RTC_AlarmStruct.Alarm=RTC_ALARM_A;
  HAL_RTC_SetAlarm_IT(&hrtc, &RTC_AlarmStruct,RTC_FORMAT_BIN);
	

	HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LedAlarm_GPIO_Port,LedAlarm_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_SET);	
	
	HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_SET);
	keypadRead();
//after stop clock source is 32768 for 2S interrupt,reload value is 2*32768=65536=	0x10000
//	HAL_SYSTICK_Config(6553); 
//	HAL_PWR_EnableSleepOnExit();
printf("Bye!goto stop\r\n");
HAL_Delay(1000);
	HAL_SuspendTick();
HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
printf("Hi!Wakeup\r\n");
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);
	__HAL_RTC_ALARM_DISABLE_IT(&hrtc,RTC_IT_SEC);
state=UpState;
}
// ---------------------------------------------------------------
void gotoStandByMode(void)
{
	  /* Disable all used wakeup sources: PWR_WAKEUP_PIN1 */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Clear all related wakeup flags*/
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  	state=RunState;
	HAL_Delay(1000);
  	printf("Bye!goto standby\r\n");
	/* Enable WakeUp Pin PWR_WAKEUP_PIN1 connected to PA.00 */
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);	
  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();
	
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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	RTC_TimeTypeDef sTime = {0};
	uint8_t wakeupstate=0;
			keypadRead();
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
    /* Clear Standby flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU|PWR_FLAG_SB);
			printf("hello!wake up from standby\r\n");
			wakeupstate=1;
  }	
	else
	{
		printf("hello!\r\n");
		state=UpState;
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		 GPIO_PinState SwitchFB_prvState=HAL_GPIO_ReadPin(SwitchFB_GPIO_Port,SwitchFB_Pin);
  while (1)
  {
		keypadRead();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(isKeyHold(KeyPower))
		{
			__HAL_RTC_ALARM_ENABLE_IT(&hrtc,RTC_IT_SEC);
			gotoStopMode();
		}
#if 0		
		if(isKeyHold(KeyPower))
		{
			if(wakeupstate)
			{
				wakeupstate=0;
				state=UpState;
			}
			else
			{
				gotoStandByMode();
			}
		}
#endif
#if 0
		if(awu_wakup)
		{
			awu_wakup=0;
			HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_SET);	
			HAL_Delay(30);
			HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_RESET);	
			if(1)//awu_wakup_cnt==3)
			{
				SwitchFB_prvState=HAL_GPIO_ReadPin(SwitchFB_GPIO_Port,SwitchFB_Pin);
				HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,80-1);			
				HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
				while(SwitchFB_prvState==HAL_GPIO_ReadPin(SwitchFB_GPIO_Port,SwitchFB_Pin));
				HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
				HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_RESET);		
			}
			if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
			{
				Error_Handler();
			}				
			state=RunState;
			gotoStopMode();			
		}
		if(isKeyPress(KeySS) && state==UpState)  //goto stop
		{
			HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_SET);
			HAL_Delay(30);
			HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_RESET);
			if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
			{
				Error_Handler();
			}			
			state=RunState;
			gotoStopMode();
		}
		 if(isKeyPress(KeySS)&& state==RunState)
		{
			HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_RESET);	
			HAL_Delay(30);		
			HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_SET);	
			state=RunState;
			gotoStopMode();			
		}		
		 if(isKeyHold(KeySS) && state==RunState)	//wake up pin & stop
		{
			HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_RESET);	
			state=UpState;
		}
		if(isKeyPress(KeyPower)&& state==RunState)//wake up pin
		{
			HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_RESET);	
			HAL_Delay(3000);
			if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
			{
				Error_Handler();
			}					
			state=RunState;
			gotoStopMode();
		}
		 if(isKeyHold(KeyPower)&& state==RunState)
		{
			HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_RESET);	
			HAL_Delay(30);		
			HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_SET);				
			state=RunState;
			gotoStopMode();			
		}

#endif
//#if 0
//		if(isKeyPress(KeyType))
//		{
//			HAL_GPIO_TogglePin(SegA_GPIO_Port,SegA_Pin);
//			HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_RESET);
//		}
//		else if(isKeyHold(KeyType))
//		{
//			HAL_GPIO_TogglePin(SegNum1_GPIO_Port,SegNum1_Pin);
//		}
//		else if(isKeyPress(KeySS))
//		{
////			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
////			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,50-1);			
////			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
////			HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_SET);
//			
//		}
//		else if(isKeyHold(KeySS))
//		{
//			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
//			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,50-1);			
//			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
//			HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_SET);			
//		}		
//		if(SwitchFB_prvState!=HAL_GPIO_ReadPin(SwitchFB_GPIO_Port,SwitchFB_Pin))
//		{
//			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
//			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
//			HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_RESET);		
//			SwitchFB_prvState=HAL_GPIO_ReadPin(SwitchFB_GPIO_Port,SwitchFB_Pin);		
//		}
//#endif
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
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
