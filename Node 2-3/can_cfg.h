#ifndef CAN_CFG_H
#define CAN_CFG_H

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
#define CAN0RXID                0



#define NODE_1	                1
#define NODE_2               		2
#define NODE_3	                3

#define INCREMENT	                1
#define NOTHING               		2
#define RESET	                		3

void CANIntHandler(void);
void CAN_Init(void);
void CAN_Send(char word[],uint8_t Id);
uint8_t CAN_recieve(void);
void Error_Handling (void);

#endif
