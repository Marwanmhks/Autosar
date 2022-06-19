#include "dio_cfg.h"

Port_ConfigType Dio_Init;

void Init_SW(void) {
	Dio_Init.SYSCTL_PERIPH = SYSCTL_PERIPH_GPIOF;
	Dio_Init.PinDirection = PORT_PIN_IN;
	Dio_Init.Channel = 40;
	Port_Init(&Dio_Init);
	Dio_Init.Channel = 44;
	Port_Init(&Dio_Init);

}