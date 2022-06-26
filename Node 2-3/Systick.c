#include "Systick.h"



volatile uint32_t tickPer10ms = 0;
volatile FlagType systickFlag = 0;
volatile FlagType oneSecondFlag = 0;

/******************************************************************************/
/* Inputs: None        												  */
/* Outputs: sets the flags for the tasks of the application        												  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :									*/
/* Description: ISR for the systick timer with period 10ms													  */
/******************************************************************************/
void SysTickIntHandler(void){
	systickFlag = 1;
	tickPer10ms++;
	if(tickPer10ms == 100){
		oneSecondFlag = 1;
		tickPer10ms = 0;
	}
}
/******************************************************************************/
/* Inputs: None        												  */
/* Outputs: flag of the systick timer       												  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :									*/
/* Description: checks the flag of the systick timer 10 ms periodicity											  */
/******************************************************************************/
FlagType systick_elapsed(void){
	return systickFlag;
}
/******************************************************************************/
/* Inputs: None        												  */
/* Outputs: flag of the systick timer       												  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :									*/
/* Description: checks the flag of the systick timer 1 s periodicity											  */
/******************************************************************************/
FlagType oneSec_elapsed(){
	return oneSecondFlag;
}
void oneSec_reset(){
	oneSecondFlag = 0;
}
void systick_reset(){
	systickFlag = 0;
}

void Systick_Init(TimeType ECU_period){
	IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()*ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}
