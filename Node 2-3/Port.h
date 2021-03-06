/******************************************************************************/
/* Module Name: PORT       												  */
/* Author: Omar Atef              */
/* Purpose: Port driver for MCU ports													  */

/******************************************************************************/

#ifndef PORT_H
#define PORT_H
#include "Port_cfg.h"

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif
