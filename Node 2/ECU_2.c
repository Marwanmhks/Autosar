#include "ECU_2.h"

volatile bool ECU_2_Flag = 0;
volatile bool ECU_3_Flag = 0;
volatile bool Red_Flag = 0;
volatile bool stateFlag = 0;

void SysTickIntHandler(void){

}
void Systick_Init(void){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}
void GPIO_Init(void){
		Init_LEDs();
}
void Write_LEDs(Dio_ChannelType Color,Dio_LevelType Level){
	Dio_WriteChannel(Color,Level);
}
void State_Change(Dio_ChannelType Color){
	Write_LEDs(RED,STD_LOW);
	Write_LEDs(BLUE,STD_LOW);
	Write_LEDs(GREEN,STD_LOW);
	Write_LEDs(Color,STD_HIGH);
}

void vLedTask(void){
	Dio_ChannelType Color[]={RED,GREEN,BLUE};
	if(stateFlag==1){

            stateFlag = 0;
        }
}
