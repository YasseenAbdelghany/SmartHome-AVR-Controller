/**
 * @file OperatingModes_Interface.h
 * @author Team2 (Soha)
 * @brief Manual Mode (direct user control) and Automatic Mode (sensor
 *        threshold-driven) for Room Light, Fan, Door Lock and Alarm
 *        enable/disable toggling.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef OPERATINGMODES_INTERFACE
#define OPERATINGMODES_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Hal/LED/Led_Interface.h"
#include "../../Hal/Relay/Relay_Interface.h"
#include "../../Hal/LM35/LM35_Interface.h"
#include "../../Hal/LDR/LDR_Interface.h"
#include "../SystemMap.h"
#include "../SystemConfig/SystemConfig_Interface.h"
#include "OperatingModes_Private.h"
#include "OperatingModes_Config.h"

/** @brief Configure Room Light, Fan and Door Lock outputs, all initially off. */
void ModeCtrl_Init(void);

/**
 * @brief Directly set a device's state. Silently discarded (no action)
 *        if the system is currently in Auto mode -- this is the gate
 *        that stops UI commands racing with the automatic sensor loop.
 */
void ModeCtrl_ManualSetDevice(ModeCtrl_Device_t Device, ModeCtrl_DeviceState_t State);

/** @brief Flip a device's current state. Same Auto-mode gating as ModeCtrl_ManualSetDevice(). */
void ModeCtrl_ManualToggleDevice(ModeCtrl_Device_t Device);

/**
 * @brief Non-blocking: if the system is in Auto mode, reads LM35/LDR and
 *        drives Fan/Room Light against CFG_GetTempThreshold() /
 *        CFG_GetLightThreshold() with hysteresis. No-op in Manual mode.
 *        Register this with the Scheduler (e.g. every 500-1000ms).
 */
void ModeCtrl_AutoUpdate(void);

/** @brief 1 if the given device is currently on, 0 otherwise (reflects either mode). */
uint8_t ModeCtrl_GetDeviceState(ModeCtrl_Device_t Device);

#endif /* OPERATINGMODES_INTERFACE */
