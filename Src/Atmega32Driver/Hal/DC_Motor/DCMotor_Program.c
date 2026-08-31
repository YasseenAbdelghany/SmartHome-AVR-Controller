/**
 * @file DCMotor_Program.c
 * @author Team1 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "DCMotor_Interface.h"

void DCMotor_Init(uint8_t MotorGroup, uint8_t In1Pin, uint8_t In2Pin)
{
    DIO_DirectionSelectforPin(MotorGroup,In1Pin,DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(MotorGroup,In2Pin,DIO_Outputfor1Pin);
    DCMotor_SetState(MotorGroup,In1Pin,In2Pin,DCMotor_Stop);
}

void DCMotor_SetState(uint8_t MotorGroup, uint8_t In1Pin, uint8_t In2Pin, uint8_t State)
{
    if(State==DCMotor_Stop)
    {
        DIO_WritePin(MotorGroup,In1Pin,DIO_Lowfor1Pin);
        DIO_WritePin(MotorGroup,In2Pin,DIO_Lowfor1Pin);
    }
    else if(State==DCMotor_ClockWise)
    {
        DIO_WritePin(MotorGroup,In1Pin,DIO_Highfor1Pin);
        DIO_WritePin(MotorGroup,In2Pin,DIO_Lowfor1Pin);
    }
    else if(State==DCMotor_AntiClockWise)
    {
        DIO_WritePin(MotorGroup,In1Pin,DIO_Lowfor1Pin);
        DIO_WritePin(MotorGroup,In2Pin,DIO_Highfor1Pin);
    }
    else if(State==DCMotor_Brake)
    {
        DIO_WritePin(MotorGroup,In1Pin,DIO_Highfor1Pin);
        DIO_WritePin(MotorGroup,In2Pin,DIO_Highfor1Pin);
    }
    else
    {
        // Invalid State: no action
    }
}
