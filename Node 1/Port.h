#include "Port_cfg.h"
#include "types.h"

#include "tm4c123gh6pm.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#define NumOfPins	8
const Dio_PortType Ports[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};
const Port_PinType Pins[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
const Port_PinModeType Modes[] = {'D','C'};
const unsigned int clocks [] = {SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOF};

void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
//void Port_RefreshPortDirection(void);