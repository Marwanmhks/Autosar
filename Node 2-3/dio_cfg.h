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

#define DioConf_DioChannel_F1 41
#define Dio_F1 DioConf_DioChannel_F1
#define DioConf_DioChannel_F2 42
#define Dio_F2 DioConf_DioChannel_F2
#define DioConf_DioChannel_F3 43
#define Dio_F3 DioConf_DioChannel_F3
#define RED  Dio_F1//pin id correspoding to port f pin 0
#define BLUE Dio_F2 //pin id correspoding to port f pin 3
#define GREEN Dio_F3 //pin id correspoding to port f pin 0

#define LEDs const Dio_ChannelType DioChannelConfigData[] = {RED, BLUE, GREEN}

#endif
