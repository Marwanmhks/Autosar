#include "Port_cfg.h"
#include "types.h"

#include "tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/can.h"
#include "inc/hw_can.h"
#define NumOfPins	8


void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
//void Port_RefreshPortDirection(void);