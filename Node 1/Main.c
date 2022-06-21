#include "init.h"


//Main routine
int main(void) {
	initClock();
	initGPIO();
	CAN_Init();
	for(;;){
		vSwitchTask();
		vLedTask();
	}

}
