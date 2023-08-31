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
#include "user_hall.h"
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
	EE_Init();   
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
    /* Clear Standby flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU|PWR_FLAG_SB);
			printf("hello!WakeupState\r\n");
			machineState=WakeupState;
  }	
	else
	{
		printf("hello!NormalState\r\n");
		machineState=NormalState;
		uint16_t firstTimeCheck;
		EE_ReadVariable(EE_ADD_FIRSTTIME,&firstTimeCheck);
		if(firstTimeCheck!=0xA5)
		{
			printf("write default value\r\n");
			EE_WriteVariable(EE_ADD_FIRSTTIME,0xA5);
			eepromWriteDefaults();
		}
	}
	__HAL_RTC_ALARM_ENABLE_IT(&hrtc,RTC_IT_SEC);
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcRawValue,4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		keypadRead();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		switch(machineState)
		{
			//---------------------NoneState------------------------------------//
			case NoneState:
				break;
			//---------------------StandbyState------------------------------------//
			case StandbyState:
				gotoStandbyMode(0);
				break;
			//---------------------WakeupState------------------------------------//
			case WakeupState:
				if(isKeyHold(KeyPower))
				{
					playTone(toneBeep);
					machineState=UpState;
					EE_WriteVariable(EE_ADD_MSTATE,(uint16_t)machineState);
					eepromReadValues();
					printf("change to UpState\r\n");
					playTone(tonePowerWake);
					
					GoStandbyCnt=DELAY_GOSTANDBY;
					typeSwitchcnt=1;
					submenuIndex=0;
					sprintf(msg,"%02d",syringeTimes[EEValue_TIMEINDEX]);
					printSegs(msg,0);					
				}
				if(isKeyPress(KeyPower))
				{
					gotoStandbyMode(1);
				}
				break;
			//---------------------NormalState------------------------------------//
			case NormalState:
				eepromReadValues();
				if(mPinRead(KeyType_GPIO_Port,KeyType_Pin)==GPIO_PIN_RESET && mPinRead(KeyTime_GPIO_Port,KeyTime_Pin)==GPIO_PIN_RESET )
				{
					playTone(toneEnterSetup);
					printf("enter Setup\r\n");
					machineState=SetupState;
					submenuIndex=0;
					tmp_uint16t=EEValue_PWM;
					sprintf(msg,"%02d",tmp_uint16t);
					printSegs(msg,1);
				}
				else if(mPinRead(KeyType_GPIO_Port,KeyType_Pin)==GPIO_PIN_RESET && mPinRead(KeySS_GPIO_Port,KeySS_Pin)==GPIO_PIN_RESET )
				{
					playTone(toneSave);
					setLED(LedAlarm,1);
					printf("write defaults\r\n");
					eepromWriteDefaults();
					setLED(LedAlarm,0);
					machineState=StandbyState;
				}
				else
				{
					machineState=EEValue_MSTATE;
					if(machineState==UpState)
					{
						checkingSystem();
						printf("goto Upstate\r\n");
						
						GoStandbyCnt=DELAY_GOSTANDBY;
						typeSwitchcnt=1;
						submenuIndex=0;
						sprintf(msg,"%02d",syringeTimes[EEValue_TIMEINDEX]);
						printSegs(msg,0);								
					}
					else if(machineState==StandbyState)
					{
						printf("goto StandbyState\r\n");
					}
				}
				break;
			//---------------------UpState------------------------------------//
			case UpState:
				if(isKeyPress(KeyTime))
				{
					playTone(toneBeep);
					typeSwitchcnt=1;
					submenuIndex=0;
					EEValue_TIMEINDEX++;
					if(EEValue_TIMEINDEX>=MAX_TIMEINDEX)
						EEValue_TIMEINDEX=0;
					EE_WriteVariable(EE_ADD_TIMEINDEX,EEValue_TIMEINDEX);
					sprintf(msg,"%02d",syringeTimes[EEValue_TIMEINDEX]);
					printSegs(msg,0);
					GoStandbyCnt=DELAY_GOSTANDBY;
				}
				if(isKeyPress(KeyType))
				{
					playTone(toneBeep);
					typeSwitchcnt=1;
					submenuIndex=1;
					EEValue_TYPEINDEX++;
					if(EEValue_TYPEINDEX>=MAX_TYPEINDEX)
						EEValue_TYPEINDEX=0;
					EE_WriteVariable(EE_ADD_TYPEINDEX,EEValue_TYPEINDEX);
					sprintf(msg,"%02d",syringeTypes[EEValue_TYPEINDEX]);
					printSegs(msg,0);
					rtc_flag=0;
					GoStandbyCnt=DELAY_GOSTANDBY;
				}
				if(submenuIndex==1)
				{
					if(rtc_flag)
					{
						rtc_flag=0;
						if(typeSwitchcnt)
						{
							sprintf(msg,"%02d",syringeTypes[EEValue_TYPEINDEX]);
						}
						else
						{
							sprintf(msg,"cc");
						}
						printSegs(msg,0);
						typeSwitchcnt=1-typeSwitchcnt;
					}
				}
				if(isKeyHold(KeySS))
				{
					playTone(toneBeep);
					machineState=RunState;
					playTone(toneStartRun);
				}
				if(isKeyHold(KeyPower))
				{
					playTone(toneBeep);
					machineState=StandbyState;
				}
				if(GoStandbyCnt==0)
				{
					machineState=StandbyState;
				}
				break;
			//---------------------RunState------------------------------------//
			case RunState:
				break;
			//---------------------SetupState------------------------------------//
			case SetupState:
				switch(submenuIndex)
				{
					//---------------------0:PWM setting-------------------------------//
					case 0:
						if(rtc_flag2s && motorIsStart())
						{
							rtc_flag2s=0;
							printf("BatCur:%.2f (mA)\r\n",(double)adcGetValue(adcBATCUR));
							printf("MotCur:%.2f(mA)\r\n",(double)adcGetValue(adcMOTCUR));
							printf("HallVolt:%.1f (mv)\r\n",(double)adcGetValue(adcHALVOLT));
							printf("BatVolt:%.1f (mv)\r\n",(double)adcGetValue(adcBATVOLT));
							printf("=====================================================\r\n");
						}			
						if(isKeyHold(KeyTime)&& !motorIsStart())
						{
							playTone(toneBeep);
							tmp_uint16t+=10;
							if(tmp_uint16t>MAX_PWM)
								tmp_uint16t=MIN_PWM;
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,1);
						}						
						if(isKeyPress(KeyTime)&& !motorIsStart())
						{
							playTone(toneBeep);
							tmp_uint16t++;
							if(tmp_uint16t>MAX_PWM)
								tmp_uint16t=MIN_PWM;
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,1);
						}
						if(isKeyHold(KeyType)&& !motorIsStart())
						{
							playTone(toneBeep);
							if(tmp_uint16t<MIN_PWM+10)
								tmp_uint16t=MAX_PWM+10;
							tmp_uint16t-=10;
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,1);
						}						
						if(isKeyPress(KeyType)&& !motorIsStart())
						{
							playTone(toneBeep);
							if(tmp_uint16t==MIN_PWM)
								tmp_uint16t=MAX_PWM+1;
							tmp_uint16t--;
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,1);
						}
						if(isKeyPress(KeySS))
						{
							playTone(toneBeep);
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,0);
							printDPSegs(" .");
							if(motorIsStart()) //motor ON->OFF
							{
								motorStop();
								setLED(LedSS,0);
							}
							else //motor OFF->ON
							{
								motorStart((double)tmp_uint16t);
								setLED(LedSS,1);							
							}
						}						
						if(isKeyHold(KeySS)&& motorIsStart())
						{
							playTone(toneBeep);
							playTone(toneSave);
							EE_WriteVariable(EE_ADD_PWM,(uint16_t)tmp_uint16t);
							EE_WriteVariable(EE_ADD_VOLBAT,(uint16_t)adcGetRaw(adcBATVOLT));
							eepromReadValues();
							motorStop();
							setLED(LedSS,0);
							hallON();
							submenuIndex=1;
							printSegs("HF",1);
						}
					break;
					//---------------------1:VOLTHALLF setting-------------------------------//
					case 1:
						if(rtc_flag2s)
						{
							rtc_flag2s=0;
							printf("HallVolt:%.1f (mv)\r\n",(double)adcGetValue(adcHALVOLT));
							printf("BatVolt:%.1f (mv)\r\n",(double)adcGetValue(adcBATVOLT));
							printf("=====================================================\r\n");
						}	
						if(isKeyHold(KeySS))
						{
							playTone(toneBeep);
							playTone(toneSave);
							EE_WriteVariable(EE_ADD_VHALLF,(uint16_t)adcGetRaw(adcHALVOLT));
							setLED(LedSS,1);
							rtc_flag=0;
							while(!rtc_flag);
							setLED(LedSS,0);
							hallON();
							submenuIndex=2;
							printSegs("HE",1);
						}
						break;
					//---------------------2:VOLTHALLE setting-------------------------------//
					case 2:
						if(rtc_flag2s)
						{
							rtc_flag2s=0;
							printf("HallVolt:%.1f (mv)\r\n",(double)adcGetValue(adcHALVOLT));
							printf("BatVolt:%.1f (mv)\r\n",(double)adcGetValue(adcBATVOLT));
							printf("=====================================================\r\n");
						}						
						if(isKeyHold(KeySS))
						{
							playTone(toneBeep);
							playTone(toneSave);
							EE_WriteVariable(EE_ADD_VHALLE,(uint16_t)adcGetRaw(adcHALVOLT));
							setLED(LedSS,1);
							rtc_flag=0;
							while(!rtc_flag);
							setLED(LedSS,0);
							hallOFF();
							submenuIndex=0;
							tmp_uint16t=EEValue_PWM;
							sprintf(msg,"%02d",tmp_uint16t);
							printSegs(msg,1);
						}
						break;						
				}
					//----------------------Exit Setup(standby)------------------------------//
				if(isKeyHold(KeyPower))
				{
					playTone(toneBeep);
					machineState=StandbyState;
				}					
				
				break;
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
