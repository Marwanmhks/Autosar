#ifndef ECU_1_H
#define ECU_1_H

#include "dio.h"
#include "Port.h"
#include "can_cfg.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

#define ECU_period 0.5 //periodicity in s

void SysTickIntHandler(void);
void Systick_Init(void);
void GPIO_Init(void);
uint32_t Read_SW(void);
void State_Machine(void);
bool systick_elapsed();
void systick_reset();

#endif
