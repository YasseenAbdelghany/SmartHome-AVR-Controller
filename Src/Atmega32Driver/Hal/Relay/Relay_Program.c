/**
 * @file Relay_Program.c
 * @author Team1 (Soha)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "Relay_Interface.h"

void Relay_Init(uint8_t RelayGroup, uint8_t RelayPin)
{
    DIO_DirectionSelectforPin(RelayGroup,RelayPin,DIO_Outputfor1Pin);
    Relay_Off(RelayGroup, RelayPin, Relay_ActiveHigh);
}

void Relay_On(uint8_t RelayGroup, uint8_t RelayPin, uint8_t ConnectionType)
{
    if(ConnectionType==Relay_ActiveHigh)
    {
        DIO_WritePin(RelayGroup,RelayPin,DIO_Highfor1Pin);
    }
    else if(ConnectionType==Relay_ActiveLow)
    {
        DIO_WritePin(RelayGroup,RelayPin,DIO_Lowfor1Pin);
    }
    else
    {
        // Invalid ConnectionType: no action
    }
}

void Relay_Off(uint8_t RelayGroup, uint8_t RelayPin, uint8_t ConnectionType)
{
    if(ConnectionType==Relay_ActiveHigh)
    {
        DIO_WritePin(RelayGroup,RelayPin,DIO_Lowfor1Pin);
    }
    else if(ConnectionType==Relay_ActiveLow)
    {
        DIO_WritePin(RelayGroup,RelayPin,DIO_Highfor1Pin);
    }
    else
    {
        // Invalid ConnectionType: no action
    }
}
