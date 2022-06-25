#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Port.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "string.h"

//the ids for the sending and receiving message objects
#define CAN0RXID                2
#define RXOBJECT                1
#define CAN0TXID                0
#define TXOBJECT                2

#define NODE_1	                1
#define NODE_2               		2
#define NODE_3	                3

void CANIntHandler(void);
void CAN_Init(void);
void CAN_Send(unsigned char word[],uint8_t Id);
void CAN_recieve(void);
void Error_Handling (void);

#endif
