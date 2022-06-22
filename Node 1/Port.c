#include "Port.h"


void Port_Init(const Port_ConfigType* ConfigPtr){
	Dio_PortType PortId;
	Dio_ChannelType PinId;
	uint8_t PortNum;
	PortNum = ConfigPtr->Channel/NumOfPins;
	uint8_t PinNum = ConfigPtr->Channel % NumOfPins ;
	PortId = Ports[PortNum];
	PinId = Pins[PinNum];
	
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
  SysCtlPeripheralEnable(clocks[PortNum]);
  while(!SysCtlPeripheralReady(clocks[PortNum]));
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
	Port_PinType PinId;
	PortId = Ports[Pin/NumOfPins];
	PinId = Pins[Pin%NumOfPins];
	if(Mode == 'C'){
		// to be completed for can??
	}
	else if (Mode == 'D')
	{
		
	}
}

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
	uint8_t PortNum = Pin/NumOfPins;
	uint8_t PortId = Ports[PortNum];
	uint8_t PinNum = Pin % NumOfPins;
	uint8_t PinId = Pins[PinNum];
		if(Direction == PORT_PIN_OUT){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_OUT);
		GPIOPinTypeGPIOOutput(PortId, PinId);
	}
	else if (Direction == PORT_PIN_IN){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_IN);
		GPIOPinTypeGPIOInput(PortId, PinId);
	}
}