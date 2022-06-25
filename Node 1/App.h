/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#ifndef APP_H
#define APP_H

#include "Dio.h"
#include "Port.h"
#include "Can.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

#define ECU_period 0.5 //periodicity in s

void SysTickIntHandler(void);
void Systick_Init(void);
void GPIO_Init(void);
uint32_t Read_SW(void);
void State_Machine(void);
bool systick_elapsed(void);
void systick_reset(void);

#endif
