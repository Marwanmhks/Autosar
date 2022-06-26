/******************************************************************************/
/* Module Name: DIO        												  */
/* Author: Marwan Hesham              */
/* Purpose: Define the types needed to abstractt the Tiva hardware pins as well as
						necessary functions to interact with these pins i.e. read and write*/
/******************************************************************************/
#ifndef DIO_H
#define DIO_H

#include "Dio_Cfg.h"

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);



#endif
