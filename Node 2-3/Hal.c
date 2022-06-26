#include "Hal.h"

void Init_LEDs(void) {
	LEDs;
	Port_ConfigType LED_config;
	LED_config.PinMode = Port_PinMode_DIO;
	LED_config.PinDirection = PORT_PIN_OUT;
	uint32_t len = (sizeof(DioChannelConfigData)/sizeof(Dio_ChannelType));
	for(int i=0; i< len; i++){
		LED_config.Pin = DioChannelConfigData[i];
		Port_Init(&LED_config);
	}
}
void State_Change(uint8_t State){
	Dio_ChannelType color_States[] = {RED, BLUE, GREEN};
	Dio_WriteChannel(color_States[0],STD_LOW);
	Dio_WriteChannel(color_States[1],STD_LOW);
	Dio_WriteChannel(color_States[2],STD_LOW);
	Dio_WriteChannel(color_States[State],STD_HIGH);
}