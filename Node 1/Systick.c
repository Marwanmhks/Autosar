#include "Systick.h"

volatile bool systickFlag = 0;

void SysTickIntHandler(void){
	systickFlag=1;
}
FlagType systick_elapsed(void)
{
	return systickFlag;
}
void systick_reset(void)
{
	systickFlag = 0;
}
void Systick_Init(TimeType ECU_period){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()* ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}
