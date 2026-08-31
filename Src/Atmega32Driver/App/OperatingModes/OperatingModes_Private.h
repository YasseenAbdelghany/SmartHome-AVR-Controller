/**
 * @file OperatingModes_Private.h
 * @author Team2 (Soha)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef OPERATINGMODES_PRIVATE
#define OPERATINGMODES_PRIVATE

#include <stdint.h>

typedef enum
{
    MODE_DeviceRoomLight,
    MODE_DeviceFan,
    MODE_DeviceDoorLock,
    MODE_DeviceAlarmToggle, /* toggles CFG_AlarmEnable, not a physical output */
}ModeCtrl_Device_t;

typedef enum
{
    MODE_DeviceOff,
    MODE_DeviceOn,
}ModeCtrl_DeviceState_t;

/* Bit positions within the 1-byte device status bitmask */
#define MODE_Bit_RoomLight 0
#define MODE_Bit_Fan       1
#define MODE_Bit_DoorLock  2

/* Hysteresis margin (degrees C / light %) to stop the fan/light relay
 * chattering on/off when the reading sits right at the threshold.
 */
#define MODE_TempHysteresis   1U
#define MODE_LightHysteresis  2U

#endif /* OPERATINGMODES_PRIVATE */
