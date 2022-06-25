/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "Dio.h"

const Dio_PortType Dio_Ports[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};
const Port_PinType Dio_Pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId){
	Dio_LevelType Level;
	Dio_PortType PortId;
	uint8_t PortNum;
	PortNum = ChannelId/NumOfPins;
	PortId = Dio_Ports[PortNum];
	uint8_t Pin_num = ChannelId % NumOfPins ;
	Dio_ChannelType PinId = Dio_Pins[Pin_num];
	Dio_ChannelType test = GPIOPinRead(PortId ,PinId);
	if(GPIOPinRead(PortId ,PinId) == STD_LOW ){
			Level = STD_LOW;
		}
		else{
			Level = STD_HIGH;
		}
	return Level;
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level){
	Dio_PortType PortId;
	Dio_ChannelType PinId;
	uint8_t PortNum;
	PortNum = ChannelId/NumOfPins;
	uint8_t Pin_num = ChannelId % NumOfPins ;
	PortId = Dio_Ports[PortNum];
	PinId = Dio_Pins[Pin_num];
	
	if(Level == STD_HIGH){
		GPIOPinWrite(PortId, PinId, PinId);
	}
	else if(Level == STD_LOW){
		GPIOPinWrite(PortId, PinId, ~PinId);
	}
}
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId){
	Dio_LevelType PinLevel;
	Dio_PortLevelType PortLevel;
	
	Dio_ChannelType ChannelId, CheckId = PortId * NumOfPins;
	for(ChannelId = PortId * NumOfPins; ChannelId<(CheckId+8); ChannelId++){
			PinLevel = Dio_ReadChannel(ChannelId);		
			if(PinLevel == STD_HIGH){
				PortLevel |= ChannelId;
			}
	}
	return PortLevel;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level){
	Dio_ChannelType ChannelId, CheckId = PortId * NumOfPins;
	
	for(ChannelId = PortId * NumOfPins; ChannelId<(CheckId+8); ChannelId++){
		Dio_WriteChannel(ChannelId, Level);
	}
}
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr){
	Dio_PortLevelType Level;

  Level = (Dio_ReadChannel(ChannelGroupIdPtr->port)& (ChannelGroupIdPtr->mask))>>(ChannelGroupIdPtr->offset);

	return Level;
}		
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level){
	Dio_WriteChannel(((ChannelGroupIdPtr->port) &(ChannelGroupIdPtr->mask))>>ChannelGroupIdPtr->offset,Level);
}

