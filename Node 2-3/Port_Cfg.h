#include "types.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/can.h"
#include "inc/hw_can.h"


#define NumOfPins	8 //Number of pins per port in the MCU


#define CanConf_CanChannel_TX0 13	//Port B5
#define Can_TX0 CanConf_CanChannel_TX0
#define CanConf_CanChannel_RX0 12	//Port B4
#define Can_RX0 CanConf_CanChannel_RX0

#define CAN const Port_PinType CanChannelConfigData[] = {Can_RX0, Can_TX0} //array for the CAN pins to be initialized later
