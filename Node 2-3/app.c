#include "App.h"

volatile uint8_t currentState = 0;


void Init(void){
		Init_LEDs();
		CAN_Init();
		Systick_Init(ECU_period);
}
void Loop_Func(void){
			if(systick_elapsed()){
				State_Machine();
				systick_reset(); 
     }
			if (oneSec_elapsed()){
				State_Change(currentState);
				oneSec_reset();
			}
}
void State_Machine(void){
  switch(Read_State()){
        case INCREMENT:
					currentState++;
					if(currentState == 3)
						currentState = 0;
					break;    
        case NOTHING:
					// Nothing, what did you expect
					break;
        case RESET:
					currentState = 0;
					break; 
	}
}
