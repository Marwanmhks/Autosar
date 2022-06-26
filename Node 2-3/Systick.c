/******************************************************************************/
/* Module Name: Systick       												  */
/* Author: Marwan Hesham              */
/* Purpose: define APIs to set the Tiva systick timer 													  */

/******************************************************************************/
#include "Systick.h"

volatile uint32_t tickPer10ms = 0; //variable to indicate if 1 second is reached (100 ticks to reach 1 s)
volatile FlagType systickFlag = 0;
volatile FlagType oneSecondFlag = 0;

/******************************************************************************/
/* function name: SysTickIntHandler     												  */
/* Inputs: void       												  */
/* Outputs: raises systick flag						  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: raise flag for 10ms and increment ticks elapsed or raise flag for 1 second elapsed and reset */
/******************************************************************************/
void SysTickIntHandler(void){
	systickFlag = 1;
	tickPer10ms++;
	if(tickPer10ms == 100){
		oneSecondFlag = 1;
		tickPer10ms = 0;
	}
}
FlagType systick_elapsed(void){
	return systickFlag;
}

FlagType oneSec_elapsed(){
	return oneSecondFlag;
}
void oneSec_reset(){
	oneSecondFlag = 0;
}
void systick_reset(){
	systickFlag = 0;
}

/******************************************************************************/
/* function name: Systick_Init     												  */
/* Inputs: a period in s to set the systick timer to (must be less than 1)       												  */
/* Outputs: starts the systick timer							  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :								*/
/* Description: initialize the systick with the provided period and enable the interrupt*/
/******************************************************************************/
void Systick_Init(TimeType ECU_period){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()*ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}
