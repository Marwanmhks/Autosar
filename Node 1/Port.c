/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "Port.h"

const Dio_PortType Port_Ports[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};
const Port_PinType Port_Pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
const Dio_PortType Port_Clocks [] = {SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOE,SYSCTL_PERIPH_GPIOF};

void Port_Init(const Port_ConfigType* ConfigPtr){
	Dio_PortType PortId;
	Port_PinType PinId;
	Dio_PortType ClockId;
	uint8_t PortNum;
	PortNum = ConfigPtr->Pin/NumOfPins;
	uint8_t PinNum = ConfigPtr->Pin % NumOfPins ;
	PortId = Port_Ports[PortNum];
	PinId = Port_Pins[PinNum];
	ClockId = Port_Clocks[PortNum];
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
  SysCtlPeripheralEnable(ClockId);
  while(!SysCtlPeripheralReady(ClockId));
	if(PortId == GPIO_PORTF_BASE){
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
	}
	Port_SetPinMode(ConfigPtr->Pin, ConfigPtr->PinMode);
	if(ConfigPtr->PinMode == Port_PinMode_DIO){
		Port_SetPinDirection(ConfigPtr->Pin,ConfigPtr->PinDirection);
		if(ConfigPtr->PinDirection == PORT_PIN_IN)
		GPIOPadConfigSet(PortId, PinId, ConfigPtr->PinStrength, ConfigPtr->PinType);
	}
}


void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
	Dio_PortType PortId;
	Port_PinType PinId;
	uint8_t PortNum;
	PortNum = Pin/NumOfPins;
	uint8_t PinNum = Pin % NumOfPins ;
	PortId = Port_Ports[PortNum];
	PinId = Port_Pins[PinNum];
	if(Mode ==Port_PinMode_CAN){
		// to be completed for can??
		switch (PortId){	//CAN0
			case GPIO_PORTB_BASE:
				GPIOPinConfigure(GPIO_PB4_CAN0RX);
				GPIOPinConfigure(GPIO_PB5_CAN0TX);
				GPIOPinTypeCAN(PortId, PinId);
				SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
				CANInit(CAN0_BASE);
				CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
				CANEnable(CAN0_BASE);
				break;
			case GPIO_PORTF_BASE:
				GPIOPinConfigure(GPIO_PF0_CAN0RX);
				GPIOPinConfigure(GPIO_PF3_CAN0TX);
				GPIOPinTypeCAN(PortId, PinId);
				SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
				CANInit(CAN0_BASE);
				CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
				CANEnable(CAN0_BASE);
				break;
			case GPIO_PORTE_BASE:
				GPIOPinConfigure(GPIO_PE4_CAN0RX);
				GPIOPinConfigure(GPIO_PE5_CAN0TX);
				GPIOPinTypeCAN(PortId, PinId);
				SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
				CANInit(CAN0_BASE);
				CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
				CANEnable(CAN0_BASE);
				break;

			case GPIO_PORTA_BASE: //CAN1
				GPIOPinConfigure(GPIO_PA0_CAN1RX);
				GPIOPinConfigure(GPIO_PA1_CAN1TX);
				GPIOPinTypeCAN(PortId, PinId);
				SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
				CANInit(CAN1_BASE);
				CANBitRateSet(CAN1_BASE, SysCtlClockGet(), 500000);
				CANEnable(CAN1_BASE);
				break;
			default:
				break;
			// ERROR
		}
	}
	else if (Mode == Port_PinMode_DIO){
		return;
	}
}

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction){
	uint8_t PortNum = Pin/NumOfPins;
	Dio_PortType PortId = Port_Ports[PortNum];
	uint8_t PinNum = Pin % NumOfPins;
	Port_PinType PinId = Port_Pins[PinNum];
	
		if(Direction == PORT_PIN_OUT){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_OUT);
		GPIOPinTypeGPIOOutput(PortId, PinId);
	}
	else if (Direction == PORT_PIN_IN){
		GPIODirModeSet(PortId, PinId, GPIO_DIR_MODE_IN);
		GPIOPinTypeGPIOInput(PortId, PinId);
	}
}
