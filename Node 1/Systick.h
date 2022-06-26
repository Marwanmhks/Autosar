/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#ifndef SYSTICK_H
#define SYSTICK_H

#include "types.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

void SysTickIntHandler(void);
void Systick_Init(TimeType ECU_period);
FlagType systick_elapsed(void);
void systick_reset(void);

#endif
