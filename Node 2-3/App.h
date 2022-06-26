#ifndef APP_H
#define APP_H

#include "Dio.h"
#include "Port.h"
#include "Can.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

#define ECU_period 0.01 //periodicity in s

void SysTickIntHandler(void);
void Systick_Init(void);
void GPIO_Init(void);
void State_Machine(void);
void State_Change(void);
bool systick_elapsed();
void systick_reset();
bool oneSec_elapsed();
void oneSec_reset();

#endif
