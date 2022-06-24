#ifndef ECU_1_H
#define ECU_1_H

#include "dio.h"
#include "Port.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#define SW1 40
#define SW2 44

void SysTickIntHandler(void);
void Systick_Init(void);
void GPIO_Init(void);
uint32_t SW_Input(void);
void State_machine(void);
void vSwitchTask(void);

#endif