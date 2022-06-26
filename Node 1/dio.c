/******************************************************************************/
/* Module Name: DIO        												  */
/* Author: Marwan Hesham              */
/* Purpose: Define the types needed to abstractt the Tiva hardware pins as well as
						necessary functions to interact with these pins i.e. read and write*/
/******************************************************************************/
#include "Dio.h"

const Dio_PortType Dio_Ports[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};
const Port_PinType Dio_Pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};


/******************************************************************************/
/* function name: Dio_ReadChannel     												  */
/* Inputs: Channel ID of a digital pin         												  */
/* Outputs: The state of the provided pin							  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: checks the digital state of Pin with the given channel ID whether STD_HIGH or STD_LOW 									  */
/******************************************************************************/
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

/******************************************************************************/
/* function name: Dio_WriteChannel     												  */
/* Inputs: Channel ID of a digital pin and a digital level         												  */
/* Outputs: digital level for given channel ID					  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: writes the provided digital level to the given channel id 									  */
/******************************************************************************/
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

/******************************************************************************/
/* function name: Dio_ReadPort     												  */
/* Inputs: PORT ID of a digital pin         												  */
/* Outputs: The state of the provided port							  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: checks the digital state of PORT with the given ID whether STD_HIGH or STD_LOW 									  */
/******************************************************************************/
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

/******************************************************************************/
/* function name: Dio_WritePort     												  */
/* Inputs: PORT ID of a digital PORT and a digital level         												  */
/* Outputs: digital level for given PORT ID					  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: writes the provided digital level to the given PORT  									  */
/******************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level){
	Dio_ChannelType ChannelId, CheckId = PortId * NumOfPins;
	
	for(ChannelId = PortId * NumOfPins; ChannelId<(CheckId+8); ChannelId++){
		Dio_WriteChannel(ChannelId, Level);
	}
}

/******************************************************************************/
/* function name: Dio_ReadChannelGroup     												  */
/* Inputs: pointer to channel group type          												  */
/* Outputs: The state of the provided channel group							  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: checks the digital state of Channel group whether STD_HIGH or STD_LOW 									  */
/******************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr){
	Dio_PortLevelType Level;

  Level = (Dio_ReadChannel(ChannelGroupIdPtr->port)& (ChannelGroupIdPtr->mask))>>(ChannelGroupIdPtr->offset);

	return Level;
}	

/******************************************************************************/
/* function name: Dio_WriteChannelGroup     												  */
/* Inputs: Channel ID of a digital pin and a digital level         												  */
/* Outputs: digital level for a channel group				  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: writes the provided digital level to the given DIO channel group								  */
/******************************************************************************/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level){
	Dio_WriteChannel(((ChannelGroupIdPtr->port) &(ChannelGroupIdPtr->mask))>>ChannelGroupIdPtr->offset,Level);
}

