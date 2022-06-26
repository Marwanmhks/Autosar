/******************************************************************************/
/* Module Name: Hal       												  */
/* Author: Youssef Ragaa              */
/* Purpose: mediate between the Application functions and the hardware specific functions													  */
/******************************************************************************/
#ifndef HAL_H
#define HAL_H

#include "Dio.h"
#include "Port.h"
#include "Can.h"
#include "Systick.h"

void Init_LEDs(void);
uint8_t Read_State(void);
void State_Change(uint8_t State);

#endif
