#ifndef HAL_H
#define HAL_H

#include "Dio.h"
#include "Port.h"
#include "Can.h"

void Init_SW(void);
uint32_t Read_SW(void);
void Send_Command(uint8_t Button);

#endif