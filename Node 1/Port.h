/******************************************************************************/
/* Module Name: PORT       												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */

/******************************************************************************/

#ifndef PORT_H
#define PORT_H
#include "Port_cfg.h"

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
//void Port_RefreshPortDirection(void);

#endif
