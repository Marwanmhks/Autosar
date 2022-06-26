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
			if (oneSec_elapsed()){
				State_Change();
				oneSec_reset();
			}
	}
	return 0;
}