#include "Hal.h"

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

void Send_Command(uint8_t Button){
	if(Button == SW1){
			CAN_Send_3((unsigned char *)"NO");
			CAN_Send_2((unsigned char *)"YES");
	}
	else if(Button == SW2){
			CAN_Send_2((unsigned char *)"NO");
			CAN_Send_3((unsigned char *)"YES");
	}
	else if(Button == (SW1+SW2)){
			CAN_Send_3((unsigned char *)"RESET");
			CAN_Send_2((unsigned char *)"RESET");
	}
	else if((SW2-SW1)){
			CAN_Send_2((unsigned char *)"NO");
			CAN_Send_3((unsigned char *)"NO");
	}
}
