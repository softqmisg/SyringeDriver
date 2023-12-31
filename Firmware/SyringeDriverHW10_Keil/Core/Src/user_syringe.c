#include "user_syringe.h"

uint16_t syringeTimes[]={6,8,10,12,14,16,18,20,22,24};
uint16_t syringeTypes[]={10,20};

//syringWakeups[Times][Type(10/20)]
//uint8_t syringWakeups[][2]={{49,42},
//														{66,56},
//														{82,70},
//														{100,84},
//														{118,98},
//														{136,112},
//														{154,126},
//														{169,140},
//														{186,154},
//														{208,168},
//														};
//uint8_t syringWakeups[][2]={{42,36},
//														{56,48},
//														{70,60},
//														{84,72},
//														{98,84},
//														{112,96},
//														{126,108},
//														{140,120},
//														{154,132},
//														{168,144},
//														};
//uint8_t syringWakeups[][2]={{49,42},
//														{63,54},
//														{77,66},
//														{91,78},
//														{105,90},
//														{119,102},
//														{133,114},
//														{147,126},
//														{161,138},
//														{175,150},
//														};
uint16_t syringWakeups[][2]={{45,45}, 	//6
														{60,60}, 	//8
														{75,75}, 	//10
														{90,90}, 	//12
														{108,108},//14
														{123,123},//16
														{138,138},//18
														{153,153},//20
														{168,168},//22
														{183,183},//24
														};
uint8_t delayAlarwakups[]={3,3};
char *systemErrorMsg[]={"  ","NE","E5","dU"};
uint8_t systemError=0;
