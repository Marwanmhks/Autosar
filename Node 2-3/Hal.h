#ifndef HAL_H
#define HAL_H

#include "Dio.h"
#include "Port.h"
#include "Can.h"
#include "Systick.h"

void Init_LEDs(void);

void State_Change(uint8_t State);

#endif