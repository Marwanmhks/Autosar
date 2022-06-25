/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#ifndef CAN_H
#define CAN_H

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
#define CAN0RXID                0x1001
#define RXOBJECT                1

#define NODE2TXID               0x2001
#define NODE2TXOBJECT           2
#define NODE3TXID								0x1001
#define NODE3TXOBJECT						1


void CANIntHandler(void);
void CAN_Init(void);
void CAN_Send_2(unsigned char word[]);
void CAN_Send_3(unsigned char word[]);
void CAN_recieve(void);
void Error_Handling (void);

#endif
