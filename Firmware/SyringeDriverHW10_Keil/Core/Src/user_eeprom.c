#include "user_eeprom.h"
 uint16_t EEValue_PWM;
 uint16_t EEValue_VHALLF;
 uint16_t EEValue_VHALLE;
 uint16_t EEValue_CURMOT;
 uint16_t EEValue_VOLBAT;
 uint16_t EEValue_CURBAT;
/////////////////////////////////////////////////////////////////////
void eeprom_read_values(void)
{
	uint16_t tmp_read;
	EE_ReadVariable(EE_ADD_PWM,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_PWM=tmp_read;	
	
	EE_ReadVariable(EE_ADD_VHALLF,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_VHALLF=tmp_read;	

	EE_ReadVariable(EE_ADD_VHALLE,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_VHALLE=tmp_read;	

	EE_ReadVariable(EE_ADD_CURMOT,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_CURMOT=tmp_read;	

	EE_ReadVariable(EE_ADD_VOLBAT,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_VOLBAT=tmp_read;	

	EE_ReadVariable(EE_ADD_CURBAT,&tmp_read);//(bytes_value[0]|(bytes_value[1]<<8));
	EEValue_CURBAT=tmp_read;		
}
/////////////////////////////////////////////////
void eeprom_write_defaults(void)
{
	EE_WriteVariable(EE_ADD_PWM,(uint16_t)DEFAULT_PWM);HAL_Delay(50);
	EE_WriteVariable(EE_ADD_VHALLF,(uint16_t)DEFAULT_VHALLF);HAL_Delay(50);
	EE_WriteVariable(EE_ADD_VHALLE,(uint16_t)DEFAULT_VHALLE);HAL_Delay(50);
	EE_WriteVariable(EE_ADD_CURMOT,(uint16_t)DEFAULT_CURMOT);HAL_Delay(50);
	EE_WriteVariable(EE_ADD_VOLBAT,(uint16_t)DEFAULT_VOLBAT);HAL_Delay(50);
	EE_WriteVariable(EE_ADD_CURBAT,(uint16_t)DEFAULT_CURBT);HAL_Delay(50);

	
}

