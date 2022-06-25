/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "types.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"


#define NumOfPins					8

#define DioConf_DioChannel_F0 40
#define Dio_F0 DioConf_DioChannel_F0
#define DioConf_DioChannel_F4 44
#define Dio_F4 DioConf_DioChannel_F4
#define SW1  Dio_F0//pin id correspoding to port f pin 0
#define SW2 Dio_F4 //pin id correspoding to port f pin 4

#define Switches const Dio_ChannelType DioChannelConfigData[] = {SW1, SW2}
#endif
