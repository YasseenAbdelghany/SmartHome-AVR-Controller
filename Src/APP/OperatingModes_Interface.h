/**
 * @file OperatingModes_Interface.h
 * @author Soha Hossam
 * @brief Public API of the Operating Modes (Manual/Auto) APP module.
 *        Implements FR-2 of the README: manual device control and
 *        sensor-driven automatic control of the Fan and Room Lights.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _OPERATINGMODES_INTERFACE_H
#define _OPERATINGMODES_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>
#include "OperatingModes_Private.h"
#include "OperatingModes_Config.h"

typedef enum
{
    MODE_OK,               /* Action applied */
    MODE_WRONG_SYSTEM_MODE /* Rejected: CFG_GetSystemMode() was not the mode this call needs */
} MODE_Status_t;

/*API's*/

/**
 * @brief Initializes the actuator drivers (LED + RELAY) this module owns and
 *        clears the cached device states. Call once at system start-up,
 *        after CFG_Init().
 * @return void
 */
void MODE_Init(void);

/**
 * @brief Manually drives the Room Light. Only takes effect while the system
 *        is in CFG_MODE_MANUAL (see SystemConfig).
 * @param State true = ON, false = OFF.
 * @return MODE_Status_t MODE_OK if applied, MODE_WRONG_SYSTEM_MODE if the
 *         system is currently in Automatic mode.
 */
MODE_Status_t MODE_ManualSetRoomLight(const bool State);

/**
 * @brief Manually drives the Fan/AC relay. Only takes effect while the
 *        system is in CFG_MODE_MANUAL.
 * @param State true = ON, false = OFF.
 * @return MODE_Status_t MODE_OK if applied, MODE_WRONG_SYSTEM_MODE if the
 *         system is currently in Automatic mode.
 */
MODE_Status_t MODE_ManualSetFan(const bool State);

/**
 * @brief Manually drives the Door Lock relay. Only takes effect while the
 *        system is in CFG_MODE_MANUAL.
 * @param State true = Locked (relay energized), false = Unlocked.
 * @return MODE_Status_t MODE_OK if applied, MODE_WRONG_SYSTEM_MODE if the
 *         system is currently in Automatic mode.
 */
MODE_Status_t MODE_ManualSetDoorLock(const bool State);

/**
 * @brief Flips the system's armed/disarmed alarm flag (delegates storage to
 *        CFG_SetAlarmEnable/CFG_GetAlarmEnable so it stays EEPROM-persisted
 *        and consistent with the Admin System Configuration menu). Only
 *        takes effect while the system is in CFG_MODE_MANUAL.
 * @return MODE_Status_t MODE_OK if applied, MODE_WRONG_SYSTEM_MODE if the
 *         system is currently in Automatic mode.
 */
MODE_Status_t MODE_ManualToggleAlarmArm(void);

/**
 * @brief Automatic-mode control loop. Call once per scheduler tick with the
 *        latest processed sensor readings; it is a safe no-op unless the
 *        system is currently in CFG_MODE_AUTO.
 *        Fan:        CurrentTempC > CFG_GetTempThreshold()   -> ON, else OFF
 *        Room Light: CurrentLightLevel < CFG_GetLightThreshold() -> ON, else OFF
 * @param CurrentTempC      Latest temperature reading in the same unit/range
 *                          as CFG_GetTempThreshold() (0-100, degrees C).
 * @param CurrentLightLevel Latest LDR reading in the same unit/range as
 *                          CFG_GetLightThreshold() (0-255).
 * @return void
 */
void MODE_AutoUpdate(const uint8_t CurrentTempC, const uint8_t CurrentLightLevel);

/**
 * @brief Returns the last-known state of the Room Light, set by either
 *        manual or automatic control. Used by the UI/LCD layer.
 * @return MODE_DeviceState_t
 */
MODE_DeviceState_t MODE_GetRoomLightState(void);

/**
 * @brief Returns the last-known state of the Fan, set by either manual or
 *        automatic control. Used by the UI/LCD layer.
 * @return MODE_DeviceState_t
 */
MODE_DeviceState_t MODE_GetFanState(void);

/**
 * @brief Returns the last-known state of the Door Lock, set by manual
 *        control. Used by the UI/LCD layer.
 * @return MODE_DeviceState_t
 */
MODE_DeviceState_t MODE_GetDoorLockState(void);

#endif /*_OPERATINGMODES_INTERFACE_H*/
