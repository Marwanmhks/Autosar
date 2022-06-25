#include "ECU_2.h"

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