/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "App.h"

volatile bool systickFlag = 0;

void SysTickIntHandler(void){
	systickFlag=1;
}
bool systick_elapsed(void)
{
	return systickFlag;
}
void systick_reset(void)
{
	systickFlag = 0;
}
void Systick_Init(void){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()*ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void Init_SW(void) {
	Switches;
	Port_ConfigType SW_config;
	SW_config.PinMode = Port_PinMode_DIO;
	SW_config.PinDirection = PORT_PIN_IN;
	SW_config.PinType = GPIO_PIN_TYPE_STD_WPU;
	SW_config.PinStrength = GPIO_STRENGTH_2MA;
	int len = (sizeof(DioChannelConfigData)/sizeof(Dio_ChannelType));
	for(int i=0; i< len; i++){
		SW_config.Pin = DioChannelConfigData[i];
		Port_Init(&SW_config);
	}
}
void GPIO_Init(void){
		Init_SW();
}
uint32_t Read_SW(void){
		if(Dio_ReadChannel(SW1) == STD_LOW){
			if(Dio_ReadChannel(SW2) == STD_LOW){
				return SW1+SW2;
			}
			return SW1;
		}		
		else if(Dio_ReadChannel(SW2) == STD_LOW){
			if(Dio_ReadChannel(SW1) == STD_LOW){
				return (SW1+SW2);
			}
			return SW2;
		}
		return 0;
}
void State_Machine(void){
  switch(Read_SW()){
        case SW2:
					CAN_Send_3((unsigned char *)"NO");
					CAN_Send_2((unsigned char *)"YES");
					while(Read_SW() == SW1){}
					break;    
        case SW1:
					CAN_Send_2((unsigned char *)"NO");
					CAN_Send_3((unsigned char *)"YES");
					while(Read_SW() == SW2){}
					break;
        case (SW1+SW2):
					CAN_Send_2((unsigned char *)"RESET");
					CAN_Send_3((unsigned char *)"RESET");
					while(Read_SW() == (SW1+SW2)){}
					break; 
				default:
					CAN_Send_2((unsigned char *)"NO");
					CAN_Send_3((unsigned char *)"NO");
	}
}

