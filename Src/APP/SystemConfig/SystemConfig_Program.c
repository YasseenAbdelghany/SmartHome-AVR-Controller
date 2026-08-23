#include "SystemConfig_Interface.h"
#include "../../MCAL/EEPROM/EEPROM_Interface.h"

/* TODO (integration): #include "../EventLogging/EventLogging_Interface.h" -> owned by Logging teammate */

/* RAM cache: avoids repeated EEPROM reads (endurance + speed) once loaded at boot */
static uint8_t          CFG_TempThresholdCache;
static uint8_t          CFG_LightThresholdCache;
static CFG_AlarmState_t CFG_AlarmEnableCache;
static CFG_SystemMode_t CFG_SystemModeCache;

/*API's*/
void CFG_Init(void)
{
    uint8_t TempByte = 0u;

    (void)EEPROM_ReadByte(CFG_EEPROM_TEMP_THRESHOLD_ADDR, &TempByte);
    CFG_TempThresholdCache = TempByte;

    (void)EEPROM_ReadByte(CFG_EEPROM_LIGHT_THRESHOLD_ADDR, &TempByte);
    CFG_LightThresholdCache = TempByte;

    (void)EEPROM_ReadByte(CFG_EEPROM_SYSTEM_MODE_ADDR, &TempByte);
    CFG_SystemModeCache = (CFG_SystemMode_t)TempByte;

    (void)EEPROM_ReadByte(CFG_EEPROM_ALARM_ENABLE_ADDR, &TempByte);
    CFG_AlarmEnableCache = (CFG_AlarmState_t)TempByte;
}

CFG_Status_t CFG_SetTempThreshold(const uint8_t Value)
{
    CFG_Status_t LocalStatus = CFG_INVALID_VALUE;

    if ((Value >= CFG_TEMP_THRESHOLD_MIN) && (Value <= CFG_TEMP_THRESHOLD_MAX))
    {
        if (EEPROM_WriteByte(CFG_EEPROM_TEMP_THRESHOLD_ADDR, Value) == EEPROM_OK)
        {
            CFG_TempThresholdCache = Value;
            LocalStatus = CFG_OK;
            /* TODO: LOG_Event(EVENT_CONFIG_CHANGED); */
        }
        else
        {
            LocalStatus = CFG_WRITE_FAIL;
        }
    }

    return LocalStatus;
}

CFG_Status_t CFG_SetLightThreshold(const uint8_t Value)
{
    CFG_Status_t LocalStatus = CFG_INVALID_VALUE;

    if ((Value >= CFG_LIGHT_THRESHOLD_MIN) && (Value <= CFG_LIGHT_THRESHOLD_MAX))
    {
        if (EEPROM_WriteByte(CFG_EEPROM_LIGHT_THRESHOLD_ADDR, Value) == EEPROM_OK)
        {
            CFG_LightThresholdCache = Value;
            LocalStatus = CFG_OK;
            /* TODO: LOG_Event(EVENT_CONFIG_CHANGED); */
        }
        else
        {
            LocalStatus = CFG_WRITE_FAIL;
        }
    }

    return LocalStatus;
}

CFG_Status_t CFG_SetAlarmEnable(const CFG_AlarmState_t State)
{
    CFG_Status_t LocalStatus = CFG_WRITE_FAIL;

    if (EEPROM_WriteByte(CFG_EEPROM_ALARM_ENABLE_ADDR, (uint8_t)State) == EEPROM_OK)
    {
        CFG_AlarmEnableCache = State;
        LocalStatus = CFG_OK;
        /* TODO: LOG_Event(EVENT_CONFIG_CHANGED); */
    }

    return LocalStatus;
}

CFG_Status_t CFG_SetSystemMode(const CFG_SystemMode_t Mode)
{
    CFG_Status_t LocalStatus = CFG_WRITE_FAIL;

    if (EEPROM_WriteByte(CFG_EEPROM_SYSTEM_MODE_ADDR, (uint8_t)Mode) == EEPROM_OK)
    {
        CFG_SystemModeCache = Mode;
        LocalStatus = CFG_OK;
        /* TODO: LOG_Event(EVENT_CONFIG_CHANGED); */
    }

    return LocalStatus;
}

uint8_t CFG_GetTempThreshold(void)
{
    return CFG_TempThresholdCache;
}

uint8_t CFG_GetLightThreshold(void)
{
    return CFG_LightThresholdCache;
}

CFG_AlarmState_t CFG_GetAlarmEnable(void)
{
    return CFG_AlarmEnableCache;
}

CFG_SystemMode_t CFG_GetSystemMode(void)
{
    return CFG_SystemModeCache;
}
