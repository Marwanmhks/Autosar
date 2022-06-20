#ifndef ECU_1_H
#define ECU_1_H

#include "dio_cfg.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#define STD_LOW 0x00

void SysTickIntHandler(void);
void Systick_Init(void);
void GPIO_Init(void);
uint32_t SW_Input(void);
void State_Switch(void);
void vSwitchTask(void);
	
#endif