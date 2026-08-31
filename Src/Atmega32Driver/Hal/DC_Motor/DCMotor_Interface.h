/**
 * @file DCMotor_Interface.h
 * @author Team1 (Khaled)
 * @brief 2-pin H-bridge DC Motor driver (direction control only -- pair
 *        with Timer1 PWM on the H-bridge's enable pin for speed control).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef DC_MOTOR_INTERFACE
#define DC_MOTOR_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"
#include "DCMotor_Private.h"
#include "DCMotor_Config.h"

/**
 * @brief Configure both H-bridge input pins as outputs and stop the motor.
 */
void DCMotor_Init(uint8_t MotorGroup, uint8_t In1Pin, uint8_t In2Pin);

/**
 * @brief Drive the motor into the given state (Stop, ClockWise,
 *        AntiClockWise or Brake).
 */
void DCMotor_SetState(uint8_t MotorGroup, uint8_t In1Pin, uint8_t In2Pin, uint8_t State);

#endif /* DC_MOTOR_INTERFACE */
