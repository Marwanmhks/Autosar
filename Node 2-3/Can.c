/******************************************************************************/
/* Module Name: CAN       												  */
/* Author: Mahmoud Emad              */
/* Purpose: CAN interface functions for reading and writing messsages 													  */

/******************************************************************************/
#include "Can.h"

volatile uint32_t error_type = 0;
volatile FlagType errFlag=0; //error flag for any errors in the CAN bus
tCANMsgObject TXmsg; //message object for the sent message
tCANMsgObject RXmsg; //message object for the recieved message
//message data of maximum size 8 bytes (64 bits) as per CAn protocol
CanMsgType TXmsg_Data[8]; //character array for stroing the message to be set to the can bus
CanMsgType RXmsg_Data[8]; //character array to store the message read from the CAN bus
volatile FlagType rxFlag=0;

/******************************************************************************/
/* function name: CANIntHandler     												  */
/* Inputs: void       												  */
/* Outputs: set the flags for recieved messages							  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: check the status of the can message and determine if it's a valid message then raise
								or if it's an error then raise and error flag and get error typr*/
/******************************************************************************/
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
	else if(status == RXOBJECT) { 
		// clear interrupt
		CANIntClear(CAN0_BASE, RXOBJECT);
		// set rx flag
		rxFlag = 1; 
		// clear any error flags	
		errFlag = 0; 
	}
}

/******************************************************************************/
/* function name: Init_CAN0     												  */
/* Inputs: void       												  */
/* Outputs: void						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: initialize the CAN0 module pins using the port driver APIs */
/******************************************************************************/
void Init_CAN0(void) {
	CAN;
	Port_ConfigType CAN_config;
	CAN_config.PinMode = Port_PinMode_CAN;
	uint32_t len = (sizeof(CanChannelConfigData)/sizeof(Port_PinType));
	for(int i=0; i< len; i++){
		CAN_config.Pin = CanChannelConfigData[i];
		Port_Init(&CAN_config);
	}
}

/******************************************************************************/
/* function name: CAN_Init     												  */
/* Inputs: void       												  */
/* Outputs: void						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: initialize the CAN0 module pins using the port driver APIs and enable interrupts.
								furthermore, set up the message object with the appropriate configuration*/
/******************************************************************************/
void CAN_Init(void){
	// Set up CAN0
	Init_CAN0();
	CANIntRegister(CAN0_BASE, CANIntHandler);
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
	//setup message object 
	RXmsg.ui32MsgID = CAN0RXID;
	RXmsg.ui32MsgIDMask = 0xfffff;
	RXmsg.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	RXmsg.ui32MsgLen = 8; // allow up to 8 bytes
	// Load msg into CAN peripheral message object 1 
	//so it can trigger interrupts on any matched rx messages
	CANMessageSet(CAN0_BASE, RXOBJECT, &RXmsg, MSG_OBJ_TYPE_RX);

}

void CAN_Send(char word[],uint8_t Id){
	
	// Set up msg object
	TXmsg.pui8MsgData = (uint8_t*)&word;

	// send as msg object 1
	//CANMessageSet(CAN0_BASE, TXOBJECT, &TXmsg, MSG_OBJ_TYPE_TX); 
}

/******************************************************************************/
/* function name: CAN_recieve     												  */
/* Inputs: void       												  */
/* Outputs: state of the 						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: if a can message was recieved clear the flag and read the message
								return an identifier indicating the state */
/******************************************************************************/
uint8_t CAN_recieve(void){
			if(rxFlag && !errFlag){ 			
				 // set pointer to rx buffer
				RXmsg.pui8MsgData = RXmsg_Data ; 
				// read CAN message object 1 from CAN peripheral
				CANMessageGet(CAN0_BASE, RXOBJECT, &RXmsg, 0); 
				// clear rx flag
				Error_Handling();	
				rxFlag = 0; 
				
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
		return 0;
}

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
