/******************************************************************************/
/* Module Name: App       												  */
/* Author: Youssef Ragaa           */
/* Purpose: the application layer for nodes 2 and 3 													  */

/******************************************************************************/
#ifndef APP_H
#define APP_H

#include "Hal.h"


#define ECU_period 0.01 //periodicity in s


void Init(void);
void State_Machine(void);
void Loop_Func(void);


#endif
