/******************************************************************************/
/* Module Name: App       												  */
/* Author: Youssef Ragaa           */
/* Purpose: the application layer for nodes 2 and 3 													  */

/******************************************************************************/

#include "App.h"

volatile uint8_t currentState = 0; //the current state of the node from the 3 possible states RGB

/******************************************************************************/
/* function name: Init     												  */
/* Inputs: void       												  */
/* Outputs: void							  */
/* Re-entrancy: Re-entrant        												  */
/* Synchronous :									*/
/* Description: initialize the peripherals needed for the application. Namely, the LED pins, the CAN bus and the systick timer 									  */
/******************************************************************************/
void Init(void){
		Init_LEDs();
		CAN_Init();
		Systick_Init(ECU_period);
}

/******************************************************************************/
/* function name: Loop_Func     												  */
/* Inputs: void       												  */
/* Outputs: void							  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: the main loop function which checks the systick timer to either
								check the state machine at 10 ms intervals or change the states
								at 1 s intervals 									  */
/******************************************************************************/
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

/******************************************************************************/
/* function name: State_Machine     												  */
/* Inputs: void       												  */
/* Outputs: void							  */
/* Re-entrancy: non Re-entrant        												  */
/* Synchronous :									*/
/* Description: the state machine for the application checking the sent CAN messages every 10 ms
								and setting the State variable accordingly*/
/******************************************************************************/
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
