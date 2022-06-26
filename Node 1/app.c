/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "App.h"


void Init(void){
		Init_SW();
		CAN_Init();
		Systick_Init(ECU_period);
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

