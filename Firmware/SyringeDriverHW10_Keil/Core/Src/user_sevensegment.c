#include "user_sevensegment.h"
#include <ctype.h>
	__IO uint8_t seg_value=0;
	__IO uint8_t current_dp[2]={0,0};

void showSeg(char ch,uint8_t dp)
{
	switch(ch)
	{
		case ' ':
			seg_value=0x00;
			break;
		case '0':
			seg_value=0x3f;
			break;
		case '1':
			seg_value=0x06;
			break;	
		case '2':
			seg_value=91;
			break;
		case '3':
			seg_value=79;
			break;
		case '4':
			seg_value=102;
			break;
		case '5':
			seg_value=109;
			break;
		case '6':
			seg_value=125;
			break;
		case '7':
			seg_value=7;
			break;
		case '8':
			seg_value=0x7F;
			break;
		case '9':
			seg_value=111;
			break;
		case 'C':
			seg_value=0x39;
			break;
		case 'c':
			seg_value=88;
			break;		
		default:
			seg_value=127;			
		break;
	}
	seg_value|=dp;
	//Common anode 
#if defined(CA_SEG)
	if(seg_value &0x80)
		HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_SET);
	
	if(seg_value &0x01)
		HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_SET);

	if(seg_value &0x02)
		HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_SET);

	if(seg_value &0x04)
		HAL_GPIO_WritePin(SegC_GPIO_Port,SegC_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegC_GPIO_Port,SegC_Pin,GPIO_PIN_SET);

	if(seg_value &0x08) //wrong in PCB so to solve problem I change here F instead of D
		HAL_GPIO_WritePin(SegF_GPIO_Port,SegF_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegF_GPIO_Port,SegF_Pin,GPIO_PIN_SET);

	if(seg_value &0x10)
		HAL_GPIO_WritePin(SegE_GPIO_Port,SegE_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegE_GPIO_Port,SegE_Pin,GPIO_PIN_SET);

	if(seg_value &0x20)
		HAL_GPIO_WritePin(SegD_GPIO_Port,SegD_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegD_GPIO_Port,SegD_Pin,GPIO_PIN_SET);

	if(seg_value &0x40)
		HAL_GPIO_WritePin(SegG_GPIO_Port,SegG_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(SegG_GPIO_Port,SegG_Pin,GPIO_PIN_SET);

#endif
#if defined(CC_SEG)
	if(seg_value &0x80)
		HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegDP_GPIO_Port,SegDP_Pin,GPIO_PIN_RESET);
	
	if(seg_value &0x40)
		HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegA_GPIO_Port,SegA_Pin,GPIO_PIN_RESET);

	if(seg_value &0x20)
		HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegB_GPIO_Port,SegB_Pin,GPIO_PIN_RESET);

	if(seg_value &0x10)
		HAL_GPIO_WritePin(SegC_GPIO_Port,SegC_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegC_GPIO_Port,SegC_Pin,GPIO_PIN_RESET);

	if(seg_value &0x08)
		HAL_GPIO_WritePin(SegD_GPIO_Port,SegD_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegD_GPIO_Port,SegD_Pin,GPIO_PIN_RESET);

	if(seg_value &0x04)
		HAL_GPIO_WritePin(SegE_GPIO_Port,SegE_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegE_GPIO_Port,SegE_Pin,GPIO_PIN_RESET);

	if(seg_value &0x02)
		HAL_GPIO_WritePin(SegF_GPIO_Port,SegF_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegF_GPIO_Port,SegF_Pin,GPIO_PIN_RESET);

	if(seg_value &0x01)
		HAL_GPIO_WritePin(SegG_GPIO_Port,SegG_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(SegG_GPIO_Port,SegG_Pin,GPIO_PIN_RESET);	
#endif
	
	
}
/*-----------------------------------------------------------------*/
static __IO uint8_t blink_active=0;
static __IO uint8_t blink_state=0;
static __IO uint16_t blink_cnt=0;
static __IO uint8_t index_digit=0;
static __IO char 		current_ch[2];
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==SEGMENT_INSTANCE)
	{
		if(blink_active)
		{
			blink_cnt++;
			if(blink_state==0) //BLINK ON state
			{
				if(blink_cnt>BLINKON_DELAY)
				{
					blink_cnt=0;
					blink_state=1; //off the segment & start off period
					HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_SET);						
				}
			}
			else //BLINK OFF state 
			{
				if(blink_cnt>BLINKOFF_DELAY)
				{
					blink_cnt=0;
					blink_state=0;
				
				}				
			}
		}
		if(!blink_active || !blink_state)
		{
				showSeg(current_ch[index_digit],current_dp[index_digit]);		
			if(index_digit)
			{
				HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_RESET);
				index_digit=0;
			}
			else
			{
				HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_RESET);
				index_digit=1;			
			}
		}
	}
}
/*-----------------------------------------------------------------*/
void initSegs(void)
{	
	clearSegs();
	HAL_TIM_Base_Start_IT(&SEGMENT_TIMER);
	
	
}
/*-----------------------------------------------------------------*/
void printSegs(char *str,uint8_t blink)
{
	index_digit=0;
	blink_active=blink;
	blink_state=0;
	blink_cnt=0;
	current_ch[0]=str[0];
	current_ch[1]=str[1];
	current_dp[0]=0;
	current_dp[1]=0;
}
/*-----------------------------------------------------------------*/
void printDPSegs(char *str)
{
	current_dp[0]=(str[0]==' ')?0:0x80;
	current_dp[1]=(str[1]==' ')?0:0x80;	
}
/*-----------------------------------------------------------------*/
void blinkSegs(uint8_t blink)
{
	index_digit=0;
	blink_active=blink;
	blink_state=0;
	blink_cnt=0;
	
}
/*-----------------------------------------------------------------*/
void clearSegs()
{
	index_digit=0;
	blink_active=0;
	blink_state=0;
	blink_cnt=0;
	current_ch[0]=' ';
	current_ch[1]=' ';
	current_dp[0]=0;	
	current_dp[1]=0;	
	HAL_GPIO_WritePin(SegNum2_GPIO_Port,SegNum2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SegNum1_GPIO_Port,SegNum1_Pin,GPIO_PIN_SET);	
}