#include "user_pwr.h"
#include "rtc.h"
#include <stdio.h>
#include "user_buzzer.h"
#include "Tones_Pitches.h"
#include "user_sevensegment.h"
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
//-----------------------------------------------------
static __IO uint8_t awu_wakup_cnt=0;
__IO uint8_t awu_flag=0;
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	RTC_TimeTypeDef sTime = {0};
	SYSCLKConfig_FromSTOP();
	awu_wakup_cnt++;
	if(awu_wakup_cnt>7) awu_wakup_cnt=0;
	awu_flag=1;
//  if (HAL_RTC_SetTime(hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
//  {
//    Error_Handler();
//  }	
	
}
//-----------------------------------------------------
void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin)
{
	if(gpio_pin==KeySS_Pin || gpio_pin ==KeyPower_Pin)
	{
		SYSCLKConfig_FromSTOP();
		keypadRead();		
		HAL_ResumeTick();
		HAL_GPIO_WritePin(LedAlarm_GPIO_Port,LedAlarm_Pin,GPIO_PIN_SET);
		HAL_PWR_DisableSleepOnExit();
	}
}
// ---------------------------------------------------------------
void gotoStopMode(void)
{
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
	

  RTC_AlarmTypeDef  RTC_AlarmStruct;
  RTC_AlarmStruct.AlarmTime.Hours=0x00;
	RTC_AlarmStruct.AlarmTime.Minutes=0x00;
	RTC_AlarmStruct.AlarmTime.Seconds=20;
	RTC_AlarmStruct.Alarm=RTC_ALARM_A;
//  HAL_RTC_SetAlarm_IT(&hrtc, &RTC_AlarmStruct,RTC_FORMAT_BIN);

	HAL_GPIO_WritePin(LedBat_GPIO_Port,LedBat_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LedAlarm_GPIO_Port,LedAlarm_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LedSS_GPIO_Port,LedSS_Pin,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_SET);	
	
	HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_SET);
	keypadRead();
	HAL_SuspendTick();
	HAL_PWR_EnableSleepOnExit();
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);

}
// ---------------------------------------------------------------
void gotoStandbyMode(uint8_t mute)
{
	  /* Disable all used wakeup sources: PWR_WAKEUP_PIN1 */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Clear all related wakeup flags*/
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	if(!mute)
		playToneReverse(tonePowerWake);
	HAL_Delay(500);
	blinkSegs(0);
	clearSegs(0);	
  	printf("Bye!goto standby\r\n");
	/* Enable WakeUp Pin PWR_WAKEUP_PIN1 connected to PA.00 */
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);	
  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();
	
}