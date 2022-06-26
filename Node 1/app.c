/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "App.h"

volatile bool systickFlag = 0;

void SysTickIntHandler(void){
	systickFlag=1;
}
bool systick_elapsed(void)
{
	return systickFlag;
}
void systick_reset(void)
{
	systickFlag = 0;
}
void Systick_Init(void){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()* ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void GPIO_Init(void){
		Init_SW();
}

void State_Machine(void){
  switch(Read_SW()){
        case SW1:
					Send_Command(SW1);
					while(Read_SW() == SW1){}
					break;    
        case SW2:
					Send_Command(SW2);
					while(Read_SW() == SW2){}
					break;
        case (SW1+SW2):	
					while(Read_SW() == (SW1+SW2)){
						Send_Command((SW1+SW2));
					}
					break; 
				default:
					Send_Command((SW2-SW1));
					
	}
}

