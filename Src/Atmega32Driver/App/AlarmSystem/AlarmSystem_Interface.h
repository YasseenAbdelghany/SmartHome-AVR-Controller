/**
 * @file AlarmSystem_Interface.h
 * @author Team4 (Roaya)
 * @brief Alarm System -- fires the buzzer on fire (LM35 threshold, no
 *        discrete flame sensor in the hardware table -- see SystemMap.h),
 *        the emergency push button (EXTI0, interrupt-driven), or 3
 *        consecutive failed logins (Authentication calls ALARM_Trigger
 *        directly).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef ALARMSYSTEM_INTERFACE
#define ALARMSYSTEM_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/EXTI/EXTI_Interface.h"
#include "../../Mcal/GIE/GIE_Interface.h"
#include "../../Hal/Buzzer/Buzzer_Interface.h"
#include "../../Hal/LM35/LM35_Interface.h"
#include "../SystemMap.h"
#include "../SystemConfig/SystemConfig_Interface.h"
#include "../EventLogging/EventLogging_Interface.h"
#include "AlarmSystem_Private.h"
#include "AlarmSystem_Config.h"

/**
 * @brief Configure the buzzer output and the emergency button's external
 *        interrupt (EXTI0, falling edge -- button pulls the pin Low when
 *        pressed).
 * @note  Does not call GIE_Enable() itself -- that is done once, centrally,
 *        from main() after every module's Init() has run.
 */
void ALARM_Init(void);

/**
 * @brief Trigger the alarm from the given source. Respects
 *        CFG_GetAlarmEnable() -- if the alarm system is disabled in
 *        System Configuration, this logs the event but does not sound
 *        the buzzer. Always logs via LOG_Event().
 * @param Source Which condition triggered the alarm.
 */
void ALARM_Trigger(ALARM_Source_t Source);

/** @brief Silence the buzzer and return the alarm to idle (e.g. after a valid login/reset). */
void ALARM_Clear(void);

/** @brief 1 if the alarm is currently sounding, 0 otherwise. */
uint8_t ALARM_IsActive(void);

/**
 * @brief Non-blocking periodic check: reads the LM35 and triggers a fire
 *        alarm if it crosses SystemMap_FireTempThreshold. Register this
 *        with the Scheduler (e.g. every 1000ms) -- do not call it every
 *        1ms tick, an ADC read every millisecond is unnecessary and wastes
 *        cycles the real-time loop could use elsewhere.
 */
void ALARM_CheckFireCondition(void);

#endif /* ALARMSYSTEM_INTERFACE */
