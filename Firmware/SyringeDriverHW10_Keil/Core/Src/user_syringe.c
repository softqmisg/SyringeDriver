#include "user_syringe.h"

uint16_t syringeTimes[]={6,8,10,12,14,16,18,20,22,24};
uint16_t syringeTypes[]={10,20};

//syringWakeups[Times][Type(10/20)]
uint8_t syringWakeups[][2]={{49,42},
														{66,56},
														{82,70},
														{100,84},
														{118,98},
														{136,112},
														{154,126},
														{169,140},
														{186,154},
														{208,168},
														};

char *systemErrorMsg[]={"  ","nE","E5","dU"};
uint8_t systemError=0;
