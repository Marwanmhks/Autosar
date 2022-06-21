#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "dio.h"

#define RED 41
#define BLUE 42
#define GREEN 43

void Init_LEDs(void);
Port_ConfigType Dio_Init;

void Init_LEDs(void) {
	Dio_Init.SYSCTL_PERIPH = SYSCTL_PERIPH_GPIOF;
	Dio_Init.PinDirection = PORT_PIN_OUT;
	Dio_Init.Channel = RED;
	Port_Init(&Dio_Init);
	Dio_Init.Channel = BLUE;
	Port_Init(&Dio_Init);
	Dio_Init.Channel = GREEN;
	Port_Init(&Dio_Init);

}
#endif
