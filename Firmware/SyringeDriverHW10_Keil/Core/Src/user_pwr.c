#include <stdio.h>
#include "user_pwr.h"
#include "rtc.h"
#include "gpio.h"
#include "tim.h"
#include "user_adc.h"
#include "user_buzzer.h"
#include "Tones_Pitches.h"
#include "user_keypad.h"
#include "user_syringe.h"
#include "user_eeprom.h"
#include "user_hall.h"
#include "user_motor.h"
#include "user_sevensegment.h"
#include "usart.h"
#include <time.h>
RTC_TimeTypeDef stampTime;
volatile int numberofwakeup=0;
/*-----------------------------------------------------*/
void setAlarm(RTC_AlarmTypeDef *sAlarm,RTC_TimeTypeDef stamp, uint8_t delay)
{
		RTC_TimeTypeDef sTime;
		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	uint16_t cursec=(uint16_t) sTime.Hours*3600+(uint16_t) sTime.Minutes*60+(uint16_t) sTime.Seconds;
	uint16_t nextsec=(uint16_t) stamp.Hours*3600+(uint16_t) stamp.Minutes*60+(uint16_t) stamp.Seconds+(uint16_t)delay;
	while((int16_t)(nextsec-cursec)<2)
	{
		delay=delay*2;
		nextsec=(uint16_t) stamp.Hours*3600+(uint16_t) stamp.Minutes*60+(uint16_t) stamp.Seconds+(uint16_t)delay;
	}
	
	sAlarm->Alarm=RTC_ALARM_A;
	sAlarm->AlarmTime.Seconds=stamp.Seconds;
	sAlarm->AlarmTime.Minutes=stamp.Minutes;
	sAlarm->AlarmTime.Hours=stamp.Hours;

	sAlarm->AlarmTime.Seconds+=delay; //add ALARM every delay sec
	if(sAlarm->AlarmTime.Seconds>59)
	{
		sAlarm->AlarmTime.Seconds-=60;
		sAlarm->AlarmTime.Minutes++;
		if(sAlarm->AlarmTime.Minutes>59)
		{
			sAlarm->AlarmTime.Minutes=0;
			sAlarm->AlarmTime.Hours++;
			if(sAlarm->AlarmTime.Hours>23)
				sAlarm->AlarmTime.Hours=0;
		}
	}
	//printf("Set Alarm\r\n");
	//printf("T:%02d:%02d:%02d\r\n",sTime.Hours,sTime.Minutes,sTime.Seconds);
	//printf("A:%02d:%02d:%02d\r\n",sAlarm->AlarmTime.Hours,sAlarm->AlarmTime.Minutes,sAlarm->AlarmTime.Seconds);
}
/*-----------------------------------------------------*/
__STATIC_INLINE void SYSCLKConfig_FromSTOP(void)
{
  /* Customize process using LL interface to improve the performance 
     (wake-up time from STOP quicker in LL than HAL)*/  
  /* HSE configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1) {};

//  /* Main PLL activation */
//  LL_RCC_PLL_Enable();
//  while(LL_RCC_PLL_IsReady() != 1) 
//  {
//  };
  
  /* SYSCLK activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) 
  {
  };
	
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);


}
/*-----------------------------------------------------*/
uint8_t rtcCheckTime(RTC_HandleTypeDef *hrtc,uint16_t targetsec)
{
//	uint16_t cursec;
//	RTC_TimeTypeDef sTime;
//	RTC_DateTypeDef sDate;
//	HAL_RTC_WaitForSynchro(hrtc);
//	HAL_RTC_GetTime(hrtc,&sTime,RTC_FORMAT_BIN);
//	HAL_RTC_GetDate(hrtc,&sDate,RTC_FORMAT_BIN);
//	cursec=(uint16_t) sTime.Hours*3600+(uint16_t) sTime.Minutes*60+(uint16_t) sTime.Seconds;//(uint16_t) sTime.Minutes*60+(uint16_t) sTime.Seconds;//
//	if(cursec>=targetsec)
//		return 1;
//	return 0;
		numberofwakeup++;
	if(numberofwakeup>=targetsec/3)
	{
		numberofwakeup=0;
		return 1;
	}
	return 0;
	
}
/*-----------------------------------------------------*/
__IO uint8_t awu_flag=0;
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	RTC_AlarmTypeDef sAlarm;
	SYSCLKConfig_FromSTOP();
	HAL_ResumeTick();
	keyw_flag	=0;
	awu_flag=1;
	runState=RunOffState;
	if(rtcCheckTime(hrtc,syringWakeups[EEValue_TIMEINDEX][EEValue_TYPEINDEX]))
	{
//		awu_flag=1;
		runState=RunOnState;
	}
		HAL_PWR_DisableSleepOnExit();

}
/*-----------------------------------------------------*/
__IO uint8_t keyw_flag=0;
void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin)
{
	if(gpio_pin==KeySS_Pin || gpio_pin ==KeyPower_Pin)
	{
		SYSCLKConfig_FromSTOP();
		HAL_ResumeTick();	
		awu_flag=0;
		keyw_flag=1;
		HAL_PWR_DisableSleepOnExit();
	}
}

/*-----------------------------------------------------*/
uint8_t activeAlarm=1;
void gotoStopMode(void)
{
__IO uint32_t index = 0;
  GPIO_InitTypeDef  sGpio;
	RTC_TimeTypeDef sTime={0};
	RTC_DateTypeDef sDate={.Year=0x0,.Date=0x01,.Month=RTC_MONTH_JANUARY,.WeekDay=RTC_WEEKDAY_MONDAY};
	keypadRead();
	HAL_Delay(300);
	muteTone();
	printf("Bye!\r\n");
	keypadRead();
	MX_GPIO_DeInit();
	//----------------Init ExtI for wakeup----------------
  sGpio.Pin = KeySS_Pin;
  sGpio.Mode = GPIO_MODE_IT_FALLING;
  sGpio.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KeySS_GPIO_Port, &sGpio);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);//PORTC.13

  sGpio.Pin = KeyPower_Pin;
  sGpio.Mode = GPIO_MODE_IT_FALLING;
  sGpio.Pull = GPIO_NOPULL;
	sGpio.Speed=GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(KeyPower_GPIO_Port, &sGpio);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);//PORTA.1

	//-------------------stop Timers and ADC
	muteTone();
	motorStop();
	HAL_TIM_Base_Stop_IT(&SEGMENT_TIMER);
	HAL_TIM_Base_Stop_IT(&BUZZERPERIOD_TIMER);
	HAL_TIM_Base_Stop(&BUZZERFREQ_TIMER);
	HAL_ADC_Stop_DMA(&hadc1);
	
	//-------------------set Alaram-----------------------------------
	RTC_AlarmTypeDef  sAlarm;
	__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc, RTC_FLAG_ALRAF);
	HAL_NVIC_ClearPendingIRQ(RTC_IRQn);
	HAL_NVIC_ClearPendingIRQ(RTC_Alarm_IRQn);
	__HAL_RTC_ALARM_DISABLE_IT(&hrtc,RTC_IT_SEC);
	if(activeAlarm)
	{
		setAlarm(&sAlarm,stampTime,delayAlarwakups[EEValue_TYPEINDEX]); //every 3/3s
		HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm,RTC_FORMAT_BIN);
	}
	printf("\n\r");
	//---------------------------goto stop--------------------
	HAL_SuspendTick();
	HAL_PWR_EnableSleepOnExit();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	//---------------------------wakup stop and init peripheral--------------------
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);
	MX_GPIO_Init();		
	HAL_ADC_MspInit(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcRawValue,4);	
	HAL_TIM_MspPostInit(&BUZZERFREQ_TIMER);
	keypadRead();
	initSegs();
	HAL_RTC_WaitForSynchro(&hrtc);
	printf("Hi!\r\n");
	__HAL_RTC_ALARM_ENABLE_IT(&hrtc,RTC_IT_SEC);
	if(awu_flag)
	{
		if(runState==RunOnState)
		{
			awu_flag=0;
			printf("===========================\r\n");
			printf("AWU timeout Run On state!\r\n");
			HAL_RTC_SetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
			HAL_RTC_SetDate(&hrtc,&sDate,RTC_FORMAT_BIN);			
			hallON();
			HAL_TIM_MspPostInit(&htim1);
			#if __DEBUG__
			MX_USART3_UART_Init();
			#endif
		}
		HAL_RTC_GetTime(&hrtc,&stampTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);					
	}
	rtc_flag=0;
	rtc_flag2s=0;rtc_cnt2s=0;
	rtc_flag5s=0;rtc_cnt5s=0;
	sysTick_flag2s=0;	sysTick_cnt2s=0;	
	sysTick_flag1s=0;	sysTick_cnt1s=0;	

}
/*-----------------------------------------------------*/
void gotoStandbyMode(uint8_t mute)
{
	if(!mute)
		playToneReverse(tonePowerWake);
	HAL_Delay(500);
	printf("Bye!goto standby\r\n");
	/* Disable all used wakeup sources: PWR_WAKEUP_PIN1 */
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

	/* Clear all related wakeup flags*/
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	/* Enable WakeUp Pin PWR_WAKEUP_PIN1 connected to PA.00 */
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);	
	/* Enter the Standby mode */
	HAL_PWR_EnterSTANDBYMode();
	
}