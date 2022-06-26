#ifndef CAN_H
#define CAN_H

#include "Port.h"
#include <stdint.h>
#include "string.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

//the ids for the sending and receiving message objects
#define CAN0RXID                0x1001	
#define RXOBJECT                1				
#define CAN0TXID                9
#define TXOBJECT                10

#define INCREMENT	                6
#define NOTHING               		8
#define RESET	                		10

void CANIntHandler(void);
void CAN_Init(void);
void CAN_Send(char word[],uint8_t Id);
uint8_t CAN_recieve(void);
void Error_Handling (void);

#endif
