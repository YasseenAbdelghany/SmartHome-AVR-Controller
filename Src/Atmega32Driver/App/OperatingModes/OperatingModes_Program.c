/**
 * @file OperatingModes_Program.c
 * @author Team2 (Soha)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "OperatingModes_Interface.h"

static uint8_t ModeCtrl_u8DeviceStatus = 0U; /* bitmask, see MODE_Bit_* */

static void ModeCtrl_vidApplyRoomLight(ModeCtrl_DeviceState_t State)
{
    if(State==MODE_DeviceOn)
    {
        Led_On(SystemMap_RoomLight_Group,SystemMap_RoomLight_Pin,SystemMap_RoomLight_ConnectionType);
        SetBit(ModeCtrl_u8DeviceStatus,MODE_Bit_RoomLight);
    }
    else
    {
        Led_Off(SystemMap_RoomLight_Group,SystemMap_RoomLight_Pin,SystemMap_RoomLight_ConnectionType);
        ClearBit(ModeCtrl_u8DeviceStatus,MODE_Bit_RoomLight);
    }
}

static void ModeCtrl_vidApplyFan(ModeCtrl_DeviceState_t State)
{
    if(State==MODE_DeviceOn)
    {
        Relay_On(SystemMap_FanRelay_Group,SystemMap_FanRelay_Pin,SystemMap_FanRelay_ConnectionType);
        SetBit(ModeCtrl_u8DeviceStatus,MODE_Bit_Fan);
    }
    else
    {
        Relay_Off(SystemMap_FanRelay_Group,SystemMap_FanRelay_Pin,SystemMap_FanRelay_ConnectionType);
        ClearBit(ModeCtrl_u8DeviceStatus,MODE_Bit_Fan);
    }
}

static void ModeCtrl_vidApplyDoorLock(ModeCtrl_DeviceState_t State)
{
    if(State==MODE_DeviceOn)
    {
        Relay_On(SystemMap_DoorRelay_Group,SystemMap_DoorRelay_Pin,SystemMap_DoorRelay_ConnectionType);
        SetBit(ModeCtrl_u8DeviceStatus,MODE_Bit_DoorLock);
    }
    else
    {
        Relay_Off(SystemMap_DoorRelay_Group,SystemMap_DoorRelay_Pin,SystemMap_DoorRelay_ConnectionType);
        ClearBit(ModeCtrl_u8DeviceStatus,MODE_Bit_DoorLock);
    }
}

void ModeCtrl_Init(void)
{
    Led_Init(SystemMap_RoomLight_Group,SystemMap_RoomLight_Pin);
    Relay_Init(SystemMap_FanRelay_Group,SystemMap_FanRelay_Pin);
    Relay_Init(SystemMap_DoorRelay_Group,SystemMap_DoorRelay_Pin);

    ModeCtrl_vidApplyRoomLight(MODE_DeviceOff);
    ModeCtrl_vidApplyFan(MODE_DeviceOff);
    ModeCtrl_vidApplyDoorLock(MODE_DeviceOff);
}

void ModeCtrl_ManualSetDevice(ModeCtrl_Device_t Device, ModeCtrl_DeviceState_t State)
{
    if(CFG_GetSystemMode()==CFG_ModeManual)
    {
        if(Device==MODE_DeviceRoomLight)
        {
            ModeCtrl_vidApplyRoomLight(State);
        }
        else if(Device==MODE_DeviceFan)
        {
            ModeCtrl_vidApplyFan(State);
        }
        else if(Device==MODE_DeviceDoorLock)
        {
            ModeCtrl_vidApplyDoorLock(State);
        }
        else if(Device==MODE_DeviceAlarmToggle)
        {
            if(State==MODE_DeviceOn)
            {
                CFG_SetAlarmEnable(CFG_AlarmEnabled);
            }
            else
            {
                CFG_SetAlarmEnable(CFG_AlarmDisabled);
            }
        }
        else
        {
            // Invalid Device: no action
        }
    }
    else
    {
        // In Auto mode: silently discard manual UI commands (prevents
        // races with the automatic sensor loop, per design)
    }
}

void ModeCtrl_ManualToggleDevice(ModeCtrl_Device_t Device)
{
    uint8_t Local_u8CurrentState = ModeCtrl_GetDeviceState(Device);

    if(Local_u8CurrentState==1U)
    {
        ModeCtrl_ManualSetDevice(Device,MODE_DeviceOff);
    }
    else
    {
        ModeCtrl_ManualSetDevice(Device,MODE_DeviceOn);
    }
}

void ModeCtrl_AutoUpdate(void)
{
    if(CFG_GetSystemMode()==CFG_ModeAuto)
    {
        uint8_t  Local_u8TempC   = LM35_GetTemperature(SystemMap_LM35_ADCChannel);
        uint8_t  Local_u8Light   = LDR_GetLightPercentage(SystemMap_LDR_ADCChannel);
        uint8_t  Local_u8TempThr = CFG_GetTempThreshold();
        uint16_t Local_u16LightThr = CFG_GetLightThreshold();

        /* Fan: ON above threshold+hysteresis, OFF below threshold-hysteresis */
        if(Local_u8TempC>=(uint8_t)(Local_u8TempThr+MODE_TempHysteresis))
        {
            ModeCtrl_vidApplyFan(MODE_DeviceOn);
        }
        else if(Local_u8TempC<=(uint8_t)(Local_u8TempThr-MODE_TempHysteresis))
        {
            ModeCtrl_vidApplyFan(MODE_DeviceOff);
        }
        else
        {
            // Inside the hysteresis band: leave the fan as it currently is
        }

        /* Room Light: ON when darker than threshold-hysteresis (lower % = darker),
         * OFF when brighter than threshold+hysteresis.
         */
        if((uint16_t)Local_u8Light<=(uint16_t)(Local_u16LightThr-MODE_LightHysteresis))
        {
            ModeCtrl_vidApplyRoomLight(MODE_DeviceOn);
        }
        else if((uint16_t)Local_u8Light>=(uint16_t)(Local_u16LightThr+MODE_LightHysteresis))
        {
            ModeCtrl_vidApplyRoomLight(MODE_DeviceOff);
        }
        else
        {
            // Inside the hysteresis band: leave the light as it currently is
        }
    }
    else
    {
        // Manual mode: automatic control is inactive, nothing to do
    }
}

uint8_t ModeCtrl_GetDeviceState(ModeCtrl_Device_t Device)
{
    uint8_t Local_u8Result = 0U;

    if(Device==MODE_DeviceRoomLight)
    {
        Local_u8Result = ReadBit(ModeCtrl_u8DeviceStatus,MODE_Bit_RoomLight);
    }
    else if(Device==MODE_DeviceFan)
    {
        Local_u8Result = ReadBit(ModeCtrl_u8DeviceStatus,MODE_Bit_Fan);
    }
    else if(Device==MODE_DeviceDoorLock)
    {
        Local_u8Result = ReadBit(ModeCtrl_u8DeviceStatus,MODE_Bit_DoorLock);
    }
    else if(Device==MODE_DeviceAlarmToggle)
    {
        Local_u8Result = (uint8_t)CFG_GetAlarmEnable();
    }
    else
    {
        // Invalid Device: return 0
    }

    return Local_u8Result;
}
