/**
 * @file SystemConfig_Program.c
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "SystemConfig_Interface.h"

static CFG_Cache_t CFG_Cache;

void CFG_Init(void)
{
    uint8_t Local_u8TempProbe;

    /* Detect first boot / blank EEPROM: an unprogrammed AVR EEPROM cell
     * reads back as 0xFF. If the Temp Threshold byte is 0xFF, assume
     * nothing has ever been written and seed the defaults.
     */
    EEPROM_ReadByte(SystemMap_EE_TempThresholdAddr,&Local_u8TempProbe);

    if(Local_u8TempProbe==0xFFU)
    {
        CFG_Cache.TempThreshold  = SystemConfig_DefaultTempThreshold;
        CFG_Cache.LightThreshold = SystemConfig_DefaultLightThreshold;
        CFG_Cache.AlarmEnable    = SystemConfig_DefaultAlarmEnable;
        CFG_Cache.SystemMode     = SystemConfig_DefaultSystemMode;

        EEPROM_WriteByte(SystemMap_EE_TempThresholdAddr,CFG_Cache.TempThreshold);
        EEPROM_WriteBlock(SystemMap_EE_LightThresholdAddr,(const uint8_t*)&CFG_Cache.LightThreshold,2U);
        EEPROM_WriteByte(SystemMap_EE_AlarmEnableAddr,(uint8_t)CFG_Cache.AlarmEnable);
        EEPROM_WriteByte(SystemMap_EE_SystemModeAddr,(uint8_t)CFG_Cache.SystemMode);
    }
    else
    {
        uint8_t Local_u8Raw;

        EEPROM_ReadByte(SystemMap_EE_TempThresholdAddr,&CFG_Cache.TempThreshold);
        EEPROM_ReadBlock(SystemMap_EE_LightThresholdAddr,(uint8_t*)&CFG_Cache.LightThreshold,2U);

        EEPROM_ReadByte(SystemMap_EE_AlarmEnableAddr,&Local_u8Raw);
        CFG_Cache.AlarmEnable = (CFG_AlarmState_t)Local_u8Raw;

        EEPROM_ReadByte(SystemMap_EE_SystemModeAddr,&Local_u8Raw);
        CFG_Cache.SystemMode = (CFG_SystemMode_t)Local_u8Raw;
    }
}

void CFG_SetTempThreshold(uint8_t Value)
{
    /* Value is uint8_t so >=0 is implicit; only the upper bound needs checking. */
    if(Value<=CFG_MaxTempThreshold)
    {
        CFG_Cache.TempThreshold = Value;
        EEPROM_WriteByte(SystemMap_EE_TempThresholdAddr,Value);
    }
    else
    {
        // Out of range: reject, cache/EEPROM unchanged
    }
}

uint8_t CFG_GetTempThreshold(void)
{
    return CFG_Cache.TempThreshold;
}

void CFG_SetLightThreshold(uint16_t Value)
{
    /* Value is uint16_t so >=0 is implicit; only the upper bound needs checking. */
    if(Value<=CFG_MaxLightThreshold)
    {
        CFG_Cache.LightThreshold = Value;
        EEPROM_WriteBlock(SystemMap_EE_LightThresholdAddr,(const uint8_t*)&Value,2U);
    }
    else
    {
        // Out of range: reject, cache/EEPROM unchanged
    }
}

uint16_t CFG_GetLightThreshold(void)
{
    return CFG_Cache.LightThreshold;
}

void CFG_SetAlarmEnable(CFG_AlarmState_t Value)
{
    CFG_Cache.AlarmEnable = Value;
    EEPROM_WriteByte(SystemMap_EE_AlarmEnableAddr,(uint8_t)Value);
}

CFG_AlarmState_t CFG_GetAlarmEnable(void)
{
    return CFG_Cache.AlarmEnable;
}

void CFG_SetSystemMode(CFG_SystemMode_t Value)
{
    CFG_Cache.SystemMode = Value;
    EEPROM_WriteByte(SystemMap_EE_SystemModeAddr,(uint8_t)Value);
}

CFG_SystemMode_t CFG_GetSystemMode(void)
{
    return CFG_Cache.SystemMode;
}
