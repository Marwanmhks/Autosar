/******************************************************************************/
/* Module Name: Hal       												  */
/* Author: Youssef Ragaa              */
/* Purpose: mediate between the Application functions and the hardware specific functions													  */
/******************************************************************************/
#include "Hal.h"

/******************************************************************************/
/* function name: Init_LEDs     												  */
/* Inputs: void       												  */
/* Outputs: void						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: initialize the LEDs specified in the array in the DIO configuration 
								according to teh port driver*/
/******************************************************************************/
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

/******************************************************************************/
/* function name: State_Change     												  */
/* Inputs: state variable denoting which LED to light up       												  */
/* Outputs: void						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: write a low to all the LEDs and write a high to the specified LED */
/******************************************************************************/
void State_Change(uint8_t State){
	Dio_ChannelType color_States[] = {RED, BLUE, GREEN};
	Dio_WriteChannel(color_States[0],STD_LOW);
	Dio_WriteChannel(color_States[1],STD_LOW);
	Dio_WriteChannel(color_States[2],STD_LOW);
	Dio_WriteChannel(color_States[State],STD_HIGH);
}

uint8_t Read_State(void){
	return CAN_recieve();
}
