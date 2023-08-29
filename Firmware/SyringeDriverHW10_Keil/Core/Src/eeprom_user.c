#include "eeprom_user.h"
int16_t TEMPH_Value;
int16_t TEMPL_Value;
int16_t HUMH_Value;
int16_t HUML_Value;
struct tm tm_Targetperiod_Value;
uint8_t	BACKLIGHT_PWM_Value;
uint8_t SENSORTYPE_Value;
struct tm tm_RentTimes[MAX_RENT];
uint8_t RentTimes_valid[MAX_RENT];
/////////////////////////////////////////////////////////////////////
///Read Times & current EGG stucture; 
void eeprom_read_structtm(uint16_t add,struct tm *r,uint8_t *v,uint8_t number)
{
	uint16_t tmp_read;
	for(uint8_t i=0;i<number;i++)
	{
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_year=(uint8_t)tmp_read;
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_mon=(uint8_t)tmp_read;
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_mday=(uint8_t)tmp_read;
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_hour=(uint8_t)tmp_read;
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_min=(uint8_t)tmp_read;
		EE_ReadVariable(add,&tmp_read);add++;
		r[i].tm_sec=(uint8_t)tmp_read; 
		EE_ReadVariable(add,&tmp_read);add++;
		v[i]=(uint8_t)tmp_read;
		if(!v[i]) break;
	}
}
/////////////////////////////////////////////////////////////////////
void eeprom_read_values(void)
{
	uint16_t tmp_read;
	EE_ReadVariable(ON_HR_TM_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	tm_Targetperiod_Value.tm_hour=(uint8_t)tmp_read;	
	
	EE_ReadVariable(ON_MIN_TM_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	tm_Targetperiod_Value.tm_min=(uint8_t)tmp_read;	
	
	EE_ReadVariable(ON_SEC_TM_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	tm_Targetperiod_Value.tm_sec=(uint8_t)tmp_read;	

	EE_ReadVariable(BACKLIGHT_PWM_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	BACKLIGHT_PWM_Value=(uint8_t)tmp_read;	

	EE_ReadVariable(TEMPH_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	TEMPH_Value=(int16_t)tmp_read;	

	EE_ReadVariable(TEMPL_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	TEMPL_Value=(int16_t)tmp_read;	

	EE_ReadVariable(HUMH_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	HUMH_Value=(int16_t)tmp_read;	
	
	EE_ReadVariable(HUML_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	HUML_Value=(int16_t)tmp_read;	

	EE_ReadVariable(SENSORTYPE_ADD,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	SENSORTYPE_Value=(uint8_t)tmp_read;	
	
	eeprom_read_structtm(RENT_TIMESTRUCT_BASE_ADD,tm_RentTimes,RentTimes_valid,MAX_RENT);
}
/////////////////////////////////////////////////
void eeprom_write_structtm(uint16_t add,struct tm r,uint8_t v,uint8_t number)
{
		uint16_t address=(uint16_t)add+(uint16_t)(7*number);
		EE_WriteVariable(address,(uint16_t)r.tm_year);address++;
		EE_WriteVariable(address,(uint16_t)r.tm_mon);address++;
		EE_WriteVariable(address,(uint16_t)r.tm_mday);address++;		
		EE_WriteVariable(address,(uint16_t)r.tm_hour);address++;
		EE_WriteVariable(address,(uint16_t)r.tm_min);address++;
		EE_WriteVariable(address,(uint16_t)r.tm_sec);address++;
 		EE_WriteVariable(address,(uint16_t)v);address++;
}
/////////////////////////////////////////////////////////////////////
void eeprom_write_defaults(void)
{
		EE_WriteVariable(ON_HR_TM_ADD,(uint16_t)ON_HR_TM_DEFAULT);
		EE_WriteVariable(ON_MIN_TM_ADD,(uint16_t)ON_MIN_TM_DEFAULT);
		EE_WriteVariable(ON_SEC_TM_ADD,(uint16_t)ON_SEC_TM_DEFAULT);
		EE_WriteVariable(BACKLIGHT_PWM_ADD,(uint16_t)BACKLIGHT_PWM_DEFAULT);
		EE_WriteVariable(TEMPH_ADD,(uint16_t)TEMPH_DEFAULT);
		EE_WriteVariable(TEMPL_ADD,(uint16_t)TEMPL_DEFAULT);
		EE_WriteVariable(HUMH_ADD,(uint16_t)HUMH_DEFAULT);
		EE_WriteVariable(HUML_ADD,(uint16_t)HUML_DEFAULT);
		EE_WriteVariable(SENSORTYPE_ADD,(uint16_t)SENSORTYPE_DEFAULT);
	struct tm tmp;
		tmp.tm_hour=0;
		tmp.tm_min=0;
		tmp.tm_sec=0;
		tmp.tm_year=0;
		tmp.tm_mon=0;
		tmp.tm_mday=0;
		eeprom_write_structtm(RENT_TIMESTRUCT_BASE_ADD,tmp,0,0);
	
	
}

