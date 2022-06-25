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
#define DioConf_DioChannel_F3 44
#define Dio_F3 DioConf_DioChannel_F3
#define SW1  Dio_F0//pin id correspoding to port f pin 0
#define SW2 Dio_F3 //pin id correspoding to port f pin 3

#define Switches const Dio_ChannelType DioChannelConfigData[] = {SW1, SW2}
#endif
