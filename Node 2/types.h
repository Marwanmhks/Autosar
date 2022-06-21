#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include <stdbool.h>

typedef unsigned int Dio_ChannelType;
typedef unsigned int Dio_PortType;
typedef struct Dio_ChannelGroupType{
	uint32_t mask;
	uint8_t offset;
	Dio_PortType port;
}Dio_ChannelGroupType;
typedef uint8_t Dio_LevelType;
typedef unsigned int Dio_PortLevelType;

typedef uint8_t Port_PinType;

typedef enum{
  PORT_PIN_IN,
  PORT_PIN_OUT
}Port_PinDirectionType;
typedef unsigned int Port_PinModeType;


typedef struct Port_ConfigType{
	Port_PinModeType PinMode;
	Dio_PortType SYSCTL_PERIPH; //SYSCTL_PERIPH_GPIOF example
	Dio_ChannelType Channel;
	Port_PinDirectionType PinDirection;
	uint32_t PinStrength;
	Port_PinType PinType;

}Port_ConfigType;

#endif
