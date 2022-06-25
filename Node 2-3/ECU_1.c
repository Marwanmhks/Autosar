#include "ECU_1.h"
volatile uint8_t currentState = 0;
volatile uint32_t tickPer10ms = 0;
volatile bool systickFlag = 0;
volatile bool oneSecondFlag = 0;

void SysTickIntHandler(void){
	systickFlag = 1;
	tickPer10ms++;
	if(tickPer10ms == 100){
		oneSecondFlag = 1;
		tickPer10ms = 0;
	}
}
bool systick_elapsed(){
	return systickFlag;
}
bool oneSec_elapsed(){
	return oneSecondFlag;
}
void oneSec_reset(){
	oneSecondFlag = 0;
}
void systick_reset(){
	systickFlag = 0;
}
void Systick_Init(void){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet()*ECU_period);
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void Init_LEDs(void) {
	LEDs;
	Port_ConfigType LED_config;
	LED_config.PinMode = Port_PinMode_DIO;
	LED_config.PinDirection = PORT_PIN_OUT;
	int len = (sizeof(DioChannelConfigData)/sizeof(Dio_ChannelType));
	for(int i=0; i< len; i++){
		LED_config.Pin = DioChannelConfigData[i];
		Port_Init(&LED_config);
	}
}
void GPIO_Init(void){
		Init_LEDs();
}

void State_Machine(void){
  switch(CAN_recieve()){
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

void State_Change(void){
	Dio_ChannelType color_States[] = {RED, BLUE, GREEN};
	Dio_WriteChannel(color_States[0],STD_LOW);
	Dio_WriteChannel(color_States[1],STD_LOW);
	Dio_WriteChannel(color_States[2],STD_LOW);
	Dio_WriteChannel(color_States[currentState],STD_HIGH);
}


