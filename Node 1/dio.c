#include "dio.h"

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId){
	Dio_LevelType Level;
	Dio_PortType PortId;
	uint8_t PortNum;
	PortNum = ChannelId/NumOfPins;
	PortId = Ports[PortNum];
	uint8_t Pin_num = ChannelId % NumOfPins ;
	Dio_ChannelType PinId = Pins[Pin_num];

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
	PortId = Ports[PortNum];
	PinId = Pins[Pin_num];
	
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
	