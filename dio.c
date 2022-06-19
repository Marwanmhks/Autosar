#include "dio.h"

const Dio_PortType Ports[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};
const Dio_ChannelType Pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
const Dio_LevelType STD_LOW = 0x00;
const Dio_LevelType STD_HIGH = 0x01;

const Port_PinModeType Modes[] = {'D','C'};

void Port_Init(const Port_ConfigType* ConfigPtr){
	Dio_PortType PortId;
	Dio_ChannelType PinId;
	uint8_t PortNum;
	PortNum = ConfigPtr->Channel/NumOfPins;
	uint8_t Pin_num = ConfigPtr->Channel % NumOfPins ;
	PortId = Ports[PortNum];
	PinId = Pins[Pin_num];
	
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
  SysCtlPeripheralEnable(ConfigPtr->SYSCTL_PERIPH);
  while(!SysCtlPeripheralReady(ConfigPtr->SYSCTL_PERIPH));
	if(PortId == GPIO_PORTF_BASE){
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
	}
	if(ConfigPtr->PinDirection == PORT_PIN_OUT){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_OUT);
		GPIOPinTypeGPIOOutput(PortId, PinId);
		GPIOPadConfigSet(PortId, PinId, ConfigPtr->PinStrength, ConfigPtr->PinType);
	}
	else if (ConfigPtr->PinDirection == PORT_PIN_IN){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_IN);
		GPIOPinTypeGPIOInput(PortId, PinId);
	}
}
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
	Dio_PortType PortId;
	Dio_ChannelType PinId;
	uint8_t PortNum;
	PortNum = Pin/NumOfPins;
	uint8_t Pin_num = Pin % NumOfPins ;
	PortId = Ports[PortNum];
	PinId = Pins[Pin_num];
	if(Mode == 'C'){
		
	}
}
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
	uint8_t PortNum;
	for(uint8_t PortCount=0; PortCount< NumOfPins; PortCount++){
		if(Ports[PortCount] == PortId){
			PortNum = PortCount;
			break;
		}
	}
	Dio_ChannelType ChannelId, CheckId = PortNum * NumOfPins;
	for(ChannelId = PortNum * NumOfPins; ChannelId<(CheckId+8); ChannelId++){
			PinLevel = Dio_ReadChannel(ChannelId);		
			if(PinLevel == STD_HIGH){
				PortLevel |= ChannelId;
			}
	}

	return PortLevel;
}
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level){
	uint8_t PortNum;
	for(uint8_t PortCount=0; PortCount< NumOfPins; PortCount++){
		if(Ports[PortCount] == PortId){
			PortNum = PortCount;
			break;
		}
	}
	Dio_ChannelType ChannelId, CheckId = PortNum * NumOfPins;
	for(ChannelId = PortNum * NumOfPins; ChannelId<(CheckId+8); ChannelId++){
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
	