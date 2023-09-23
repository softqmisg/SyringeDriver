#include "user_adc.h"
#include "tim.h"
	uint16_t adcRawValue[4];
	uint16_t adcCompleteValue[4];
	double coeff[4]={1.611,1.611,1.788,4.63}; //batcur,motcur,halvolt,batvolt

#define coeffBATCUR 	1.611
#define coeffMOTCUR 	1.611	//
#define coeffHALVOLT 	1.788 //mv
#define coeffBATVOLT 	4.6 //mv
	/*--------------------------------------------------------------------------*/
	__IO uint8_t adcCnvCmpflag=0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)	
{
	adcCompleteValue[3]=adcRawValue[3];
	adcCompleteValue[2]=adcRawValue[2];
	adcCompleteValue[1]=adcRawValue[1];
	adcCompleteValue[0]=adcRawValue[0];
	adcCnvCmpflag=1;
	
	
}
	/*--------------------------------------------------------------------------*/
	uint16_t adcGetRaw(uint8_t channel)
	{
		adcCnvCmpflag=0;
		while(!adcCnvCmpflag);
		adcCnvCmpflag=0;
		return adcCompleteValue[channel];
	}
	/*--------------------------------------------------------------------------*/
	double adcGetValue(uint8_t channel)
	{
		adcCnvCmpflag=0;
		while(!adcCnvCmpflag);
		adcCnvCmpflag=0;		
		return (double)adcCompleteValue[channel]*coeff[channel];
	}