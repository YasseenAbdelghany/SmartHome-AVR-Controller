/**
 * @file DCMotor_Private.h
 * @author Team1 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef DC_MOTOR_PRIVATE
#define DC_MOTOR_PRIVATE

/* Standard 2-pin H-bridge control (e.g. L298N/L293D style IN1/IN2). */
typedef enum
{
    DCMotor_Stop,          /* In1=Low,  In2=Low  -- coast, no drive  */
    DCMotor_ClockWise,     /* In1=High, In2=Low                      */
    DCMotor_AntiClockWise, /* In1=Low,  In2=High                     */
    DCMotor_Brake,         /* In1=High, In2=High -- active brake     */
}DCMotor_State_t;

#endif /* DC_MOTOR_PRIVATE */
