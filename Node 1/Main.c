/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#include "App.h"

int main(){
	CAN_Init();
	GPIO_Init();
	Systick_Init();
	while(1)
	{
			if(systick_elapsed()){
				State_Machine();
				systick_reset(); 
     }
	}
	return 0;
}
