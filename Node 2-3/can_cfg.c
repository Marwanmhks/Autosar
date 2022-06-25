#include "can_cfg.h"

//Needs to be changed to match port config layout (layered arch)

volatile uint32_t error_type = 0;
volatile bool errFlag=0; //error flag for any errors in the CAN bus
tCANMsgObject TXmsg; //message object for the sent message
tCANMsgObject RXmsg; //message object for the recieved message
//message data of maximum size 8 bytes (64 bits) as per CAn protocol
unsigned char TXmsg_Data[8]; 
unsigned char RXmsg_Data[8];
volatile bool rxFlag=0;

// CAN interrupt handler
void CANIntHandler(void) {
	// read interrupt status
	unsigned long status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); 
	// controller status interrupt
	if(status == CAN_INT_INTID_STATUS) { 
		status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
		errFlag = 1;
		error_type |= status ; 
	} 
	// msg object 2
	else if(status == NODE_2) { 
		// clear interrupt
		CANIntClear(CAN0_BASE, NODE_2);
		// set rx flag
		rxFlag = 1; 
		// clear any error flags	
		errFlag = 0; 
	}
}
void Init_CAN0(void) {
	CAN;
	Port_ConfigType CAN_config;
	CAN_config.PinMode = Port_PinMode_CAN;
	int len = (sizeof(CanChannelConfigData)/sizeof(Port_PinType));
	for(int i=0; i< len; i++){
		CAN_config.Pin = CanChannelConfigData[i];
		Port_Init(&CAN_config);
	}
}
void CAN_Init(void){
	// Set up CAN0
	Init_CAN0();
	CANIntRegister(CAN0_BASE, CANIntHandler);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	RXmsg.ui32MsgID = CAN0RXID;
	RXmsg.ui32MsgIDMask = 0;
	RXmsg.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	RXmsg.ui32MsgLen = 8; // allow up to 8 bytes
	// Load msg into CAN peripheral message object 1 
	//so it can trigger interrupts on any matched rx messages
	CANMessageSet(CAN0_BASE, NODE_2, &RXmsg, MSG_OBJ_TYPE_RX);

}

void CAN_Send(char word[],uint8_t Id){
	
	// Set up msg object
	TXmsg.pui8MsgData = (uint8_t*)&word;

	// send as msg object 1
	CANMessageSet(CAN0_BASE, Id, &TXmsg, MSG_OBJ_TYPE_TX); 
}

//if the can flag is raised receive the message
//decrypt the message and display it on pc over uart
uint8_t CAN_recieve(void){
			if(rxFlag && !errFlag){ 			
				 // set pointer to rx buffer
				RXmsg.pui8MsgData = RXmsg_Data ; 
				// read CAN message object 1 from CAN peripheral
				CANMessageGet(CAN0_BASE, NODE_1, &RXmsg, 0); 
				// clear rx flag
				Error_Handling();	
				rxFlag = 0; 
				char test [8];
				for(int i=0; i<8; i++){
				test[i]=RXmsg_Data[i];
				}
				
				if(strcmp((char*)&RXmsg_Data,"YES") == 0){
					return INCREMENT;
				}
				else if(strcmp((char*)&RXmsg_Data,"NO") == 0){
					return NOTHING;
				}
				else if(strcmp((char*)&RXmsg_Data,"RESET") == 0){
					return RESET;
				}
		}
}

// handles the errors than can occur
// outputs a message to the user with the error type
void Error_Handling (void){
		
	if (errFlag){
	  // bus off error occurred.
		if(error_type & CAN_STATUS_BUS_OFF){
		  	error_type &= ~(CAN_STATUS_BUS_OFF);
    }

    // bit stuffing error occurred.
    else if(error_type & CAN_STATUS_LEC_STUFF){
        error_type &= ~(CAN_STATUS_LEC_STUFF);
    }
	 // other error occurred
		else{
				// Error - Check the Cable
		}
	}

}