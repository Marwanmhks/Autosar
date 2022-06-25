/******************************************************************************/
/* Module Name: can.c        												  */
/* Author: Osama Elhout and Mohamed Atef              */
/* Purpose: CAN-BUS module													  */
/******************************************************************************/
#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include <stdbool.h>
//DIO types
typedef unsigned int Dio_ChannelType;
typedef unsigned int Dio_PortType;
typedef struct Dio_ChannelGroupType{
	uint32_t mask;
	uint8_t offset;
	Dio_PortType port;
}Dio_ChannelGroupType;
typedef enum {
	STD_LOW,
	STD_HIGH
}Dio_LevelType;
typedef unsigned int Dio_PortLevelType;

//PORT types
typedef uint8_t Port_PinType;
typedef enum{
  PORT_PIN_IN,
  PORT_PIN_OUT
}Port_PinDirectionType;
typedef enum{
	Port_PinMode_CAN,
	Port_PinMode_DIO
}Port_PinModeType;
typedef struct Port_ConfigType{
	Port_PinModeType PinMode;
	Port_PinDirectionType PinDirection;
	uint32_t PinStrength;
	Port_PinType Pin;
	uint32_t PinType;
}Port_ConfigType;

#endif
