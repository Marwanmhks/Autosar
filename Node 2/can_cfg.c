#include "can_cfg.h"

//Needs to be changed to match port config layout (layered arch)

volatile bool errFlag = 0; 
tCANMsgObject msg; 
unsigned int msgData;
unsigned char *msgDataPtr = (unsigned char *)&msgData;

// CAN interrupt handler
void CANIntHandler(void) {
	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); // read interrupt status
	// controller status interrupt
	if(status == CAN_INT_INTID_STATUS) { 
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
		errFlag = 1;
	} else if(status == 1) { // message object 1
		CANIntClear(CAN0_BASE, 1); // clear interrupt
		errFlag = 0; // clear any error flags
	} 
}
void CAN_Init(void){
	// Set up CAN0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // enable CAN0 GPIO peripheral
	GPIOPinConfigure(GPIO_PB4_CAN0RX);
	GPIOPinConfigure(GPIO_PB5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
	CANIntRegister(CAN0_BASE, CANIntHandler);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	CANEnable(CAN0_BASE);
}

void CAN_Send(){
	// Set up msg object
	msgData = 0;
	msg.ui32MsgID = 1;
	msg.ui32MsgIDMask = 0;
	msg.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	msg.ui32MsgLen = sizeof(msgDataPtr);
	msg.pui8MsgData = msgDataPtr;
	// send as msg object 1
	CANMessageSet(CAN0_BASE, 1, &msg, MSG_OBJ_TYPE_TX); 
}

