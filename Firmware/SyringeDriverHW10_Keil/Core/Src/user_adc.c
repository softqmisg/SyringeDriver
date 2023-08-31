#include "user_adc.h"
#include "tim.h"
	uint16_t adcRawValue[4];
	double coeff[4]={1.611,1.611,1.788,4.6}; //batcur,motcur,halvolt,batvolt

#define coeffBATCUR 	1.611
#define coeffMOTCUR 	1.611	//
#define coeffHALVOLT 	1.788 //mv
#define coeffBATVOLT 	4.6 //mv
	uint16_t adcGetRaw(uint8_t channel)
	{
		return adcRawValue[channel];
	}
	double adcGetValue(uint8_t channel)
	{
		return (double)adcRawValue[channel]*coeff[channel];
	}