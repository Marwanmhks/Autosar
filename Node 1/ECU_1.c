#include "ECU_1.h"

volatile bool ECU_2_Flag = 0;
volatile bool ECU_3_Flag = 0;
volatile bool Red_Flag = 0;
volatile bool switchFlag = 0;

void SysTickIntHandler(void){

}
void Systick_Init(void){
		IntMasterEnable();
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void Init_SW(void) {
	Port_ConfigType SW_config;
	//SW_config.SYSCTL_PERIPH = SYSCTL_PERIPH_GPIOF;
	SW_config.PinDirection = PORT_PIN_IN;
	SW_config.Pin = SW1;
	SW_config.Pin = SW2;
	Port_Init(&SW_config);
}
void GPIO_Init(void){
		Init_SW();
}
uint32_t Read_SW(void){
		if(Dio_ReadChannel(SW1) == STD_LOW){
			if(Dio_ReadChannel(SW2) == STD_LOW){
				return SW1+SW2;
			}
			return SW1;
		}		
		else if(Dio_ReadChannel(SW2) == STD_LOW){
			if(Dio_ReadChannel(SW1) == STD_LOW){
				return (SW1+SW2);
			}
			return SW2;
		}	
}
void State_machine(void){
  switch(Read_SW()){
        case SW1:
                ECU_2_Flag = 1;
                while(SW_Input() == SW1){}
                break;    
        case SW2:
                ECU_3_Flag = 1;
                while(SW_Input() == SW2){}
                break;
 
        case (SW1+SW2):
                Red_Flag = 1;
                while(SW_Input() == (SW1+SW2)){}
                break;            
	}
}
void vSwitchTask(void){
		if(switchFlag == 1){
			State_Switch();
      switchFlag = 0; 
     }
}
