#include "dio_cfg.h"

<<<<<<< Updated upstream
Port_ConfigType Dio_Config;

void Init_SW(void) {
	Dio_Config.PinMode = Port_PinMode_DIO;
	Dio_Config.PinDirection = PORT_PIN_IN;
	Dio_Config.Pin = SW1;
	Dio_Init(&Dio_Config);
	Dio_Config.Pin = SW2;
	Dio_Init(&Dio_Config);

}
=======
Port_ConfigType Dio_Init;
>>>>>>> Stashed changes
