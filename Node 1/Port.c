#include "Port.h"

void Port_Init(const Port_ConfigType* ConfigPtr){
	Dio_PortType PortId;
	Dio_ChannelType PinId;
	uint8_t PortNum;
	PortNum = ConfigPtr->Pin/NumOfPins;
	uint8_t PinNum = ConfigPtr->Pin % NumOfPins ;
	PortId = Ports[PortNum];
	PinId = Pins[PinNum];
	
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
  SysCtlPeripheralEnable(clocks[PortNum]);
  while(!SysCtlPeripheralReady(clocks[PortNum]));
	if(PortId == GPIO_PORTF_BASE){
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
	}
	Port_SetPinMode(ConfigPtr->Pin, ConfigPtr->PinMode);
	Port_SetPinDirection(ConfigPtr->Pin,ConfigPtr->PinDirection);
	if(ConfigPtr->PinDirection == PORT_PIN_OUT)
		GPIOPadConfigSet(PortId, PinId, ConfigPtr->PinStrength, ConfigPtr->Pin);
}

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
	Dio_PortType PortId;
	Port_PinType PinId;
	PortId = Ports[Pin/NumOfPins];
	PinId = Pins[Pin%NumOfPins];
	if(Mode ==Port_PinMode_CAN){
		// to be completed for can??
		if (PortId == (GPIO_PORTF_BASE | GPIO_PORTB_BASE | GPIO_PORTE_BASE)) {//CAN0
			if(PortId == GPIO_PORTB_BASE){
				GPIOPinConfigure(GPIO_PB4_CAN0RX);
				GPIOPinConfigure(GPIO_PB5_CAN0TX);
				GPIOPinTypeCAN(PortId, GPIO_PIN_4 | GPIO_PIN_5);
			}
			if(PortId == GPIO_PORTF_BASE){
				GPIOPinConfigure(GPIO_PF0_CAN0RX);
				GPIOPinConfigure(GPIO_PF3_CAN0TX);
				GPIOPinTypeCAN(PortId, GPIO_PIN_0 | GPIO_PIN_3);
			}
			if(PortId == GPIO_PORTE_BASE){
				GPIOPinConfigure(GPIO_PE4_CAN0RX);
				GPIOPinConfigure(GPIO_PE5_CAN0TX);
				GPIOPinTypeCAN(PortId, GPIO_PIN_4 | GPIO_PIN_5);
			}
			SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
			CANInit(CAN0_BASE);
			CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
			CANEnable(CAN0_BASE);
		}
		else if (PortId == GPIO_PORTA_BASE){ //CAN1
			GPIOPinConfigure(GPIO_PA0_CAN1RX);
			GPIOPinConfigure(GPIO_PA1_CAN1TX);
			GPIOPinTypeCAN(PortId, GPIO_PIN_0 | GPIO_PIN_1);
			SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
			CANInit(CAN1_BASE);
			CANBitRateSet(CAN1_BASE, SysCtlClockGet(), 500000);
			CANEnable(CAN1_BASE);
		}
		else {
			// ERROR
		}
	}
	else if (Mode == Port_PinMode_DIO){
		return;
	}
}

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction){
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