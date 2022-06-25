#include "ECU_1.h"

int main(){
	CAN_Init();
	GPIO_Init();
	Systick_Init();
	while(1)
	{
		/*
		can messages: pressed, reset, not pressed
		read switch
		if sw1flag: sw1task
		if sw2flag sw2task
		if sw1andsw2 bothtask
		if systickflag (500 ms): can_send
		*/
			if(systick_elapsed()){
				State_Machine();
				systick_reset(); 
     }
			if (oneSec_elapsed()){
				State_Change();
				oneSec_reset();
			}
		/*node2
		systick (10ms) : state_machine()
		{ 
		read_can() set task
		case sw_pressed : increment led status
		case_sw_not pressed: no change
		case both pressed: reset led status
		}
		if 1 second elapsed() :change color(led status)
		*/
	}
	return 0;
}