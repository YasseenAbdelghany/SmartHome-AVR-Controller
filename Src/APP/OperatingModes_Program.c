#include "OperatingModes_Interface.h"
#include "../SystemConfig/SystemConfig_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/RELAY/RELAY_Interface.h"

/* TODO (integration): #include "../EventLogging/EventLogging_Interface.h" -> owned by Logging teammate */

/* RAM cache of last-known device states, read cheaply by the UI/LCD layer */
static MODE_DeviceState_t MODE_RoomLightState = MODE_DEVICE_OFF;
static MODE_DeviceState_t MODE_FanState       = MODE_DEVICE_OFF;
static MODE_DeviceState_t MODE_DoorLockState  = MODE_DEVICE_OFF;

/*API's*/
void MODE_Init(void)
{
    LED_Init();
    RELAY_Init();

    MODE_RoomLightState = MODE_DEVICE_OFF;
    MODE_FanState       = MODE_DEVICE_OFF;
    MODE_DoorLockState  = MODE_DEVICE_OFF;
}

MODE_Status_t MODE_ManualSetRoomLight(const bool State)
{
    MODE_Status_t LocalStatus = MODE_WRONG_SYSTEM_MODE;

    if (CFG_GetSystemMode() == CFG_MODE_MANUAL)
    {
        LED_SetState(LED_ROOM_LIGHT, (State == true) ? LED_ON : LED_OFF);
        MODE_RoomLightState = (State == true) ? MODE_DEVICE_ON : MODE_DEVICE_OFF;
        LocalStatus = MODE_OK;
        /* TODO: LOG_Event(EVENT_MANUAL_ROOMLIGHT_CHANGED); */
    }
    else
    {
        /* Rejected: manual control is only allowed in CFG_MODE_MANUAL */
    }

    return LocalStatus;
}

MODE_Status_t MODE_ManualSetFan(const bool State)
{
    MODE_Status_t LocalStatus = MODE_WRONG_SYSTEM_MODE;

    if (CFG_GetSystemMode() == CFG_MODE_MANUAL)
    {
        RELAY_SetState(RELAY_FAN, (State == true) ? RELAY_ON : RELAY_OFF);
        MODE_FanState = (State == true) ? MODE_DEVICE_ON : MODE_DEVICE_OFF;
        LocalStatus = MODE_OK;
        /* TODO: LOG_Event(EVENT_MANUAL_FAN_CHANGED); */
    }
    else
    {
        /* Rejected: manual control is only allowed in CFG_MODE_MANUAL */
    }

    return LocalStatus;
}

MODE_Status_t MODE_ManualSetDoorLock(const bool State)
{
    MODE_Status_t LocalStatus = MODE_WRONG_SYSTEM_MODE;

    if (CFG_GetSystemMode() == CFG_MODE_MANUAL)
    {
        RELAY_SetState(RELAY_DOOR_LOCK, (State == true) ? RELAY_ON : RELAY_OFF);
        MODE_DoorLockState = (State == true) ? MODE_DEVICE_ON : MODE_DEVICE_OFF;
        LocalStatus = MODE_OK;
        /* TODO: LOG_Event(EVENT_MANUAL_DOORLOCK_CHANGED); */
    }
    else
    {
        /* Rejected: manual control is only allowed in CFG_MODE_MANUAL */
    }

    return LocalStatus;
}

MODE_Status_t MODE_ManualToggleAlarmArm(void)
{
    MODE_Status_t LocalStatus = MODE_WRONG_SYSTEM_MODE;

    if (CFG_GetSystemMode() == CFG_MODE_MANUAL)
    {
        if (CFG_GetAlarmEnable() == CFG_ALARM_ENABLED)
        {
            (void)CFG_SetAlarmEnable(CFG_ALARM_DISABLED);
        }
        else
        {
            (void)CFG_SetAlarmEnable(CFG_ALARM_ENABLED);
        }

        LocalStatus = MODE_OK;
        /* TODO: LOG_Event(EVENT_MANUAL_ALARM_TOGGLED); */
    }
    else
    {
        /* Rejected: manual control is only allowed in CFG_MODE_MANUAL */
    }

    return LocalStatus;
}

void MODE_AutoUpdate(const uint8_t CurrentTempC, const uint8_t CurrentLightLevel)
{
    if (CFG_GetSystemMode() == CFG_MODE_AUTO)
    {
        uint16_t      TempUpperBound;
        uint16_t      TempLowerBound;
        uint16_t      LightUpperBound;
        uint16_t      LightLowerBound;
        const uint8_t TempThreshold  = CFG_GetTempThreshold();
        const uint8_t LightThreshold = CFG_GetLightThreshold();

        /* --- Fan: Temperature > Threshold -> ON --- */
        TempUpperBound = (uint16_t)TempThreshold + (uint16_t)MODE_TEMP_HYSTERESIS;
        TempLowerBound = ((uint16_t)TempThreshold > (uint16_t)MODE_TEMP_HYSTERESIS) ?
                          ((uint16_t)TempThreshold - (uint16_t)MODE_TEMP_HYSTERESIS) : 0u;

        if ((uint16_t)CurrentTempC > TempUpperBound)
        {
            RELAY_SetState(RELAY_FAN, RELAY_ON);
            MODE_FanState = MODE_DEVICE_ON;
        }
        else if ((uint16_t)CurrentTempC <= TempLowerBound)
        {
            RELAY_SetState(RELAY_FAN, RELAY_OFF);
            MODE_FanState = MODE_DEVICE_OFF;
        }
        else
        {
            /* Inside the hysteresis dead-band: hold the last Fan state */
        }

        /* --- Room Light: LDR Level < Threshold -> ON --- */
        LightUpperBound = (uint16_t)LightThreshold + (uint16_t)MODE_LIGHT_HYSTERESIS;
        LightLowerBound = ((uint16_t)LightThreshold > (uint16_t)MODE_LIGHT_HYSTERESIS) ?
                           ((uint16_t)LightThreshold - (uint16_t)MODE_LIGHT_HYSTERESIS) : 0u;

        if ((uint16_t)CurrentLightLevel < LightLowerBound)
        {
            LED_SetState(LED_ROOM_LIGHT, LED_ON);
            MODE_RoomLightState = MODE_DEVICE_ON;
        }
        else if ((uint16_t)CurrentLightLevel >= LightUpperBound)
        {
            LED_SetState(LED_ROOM_LIGHT, LED_OFF);
            MODE_RoomLightState = MODE_DEVICE_OFF;
        }
        else
        {
            /* Inside the hysteresis dead-band: hold the last Room Light state */
        }
    }
    else
    {
        /* Automatic control only runs while SystemConfig mode == CFG_MODE_AUTO */
    }
}

MODE_DeviceState_t MODE_GetRoomLightState(void)
{
    return MODE_RoomLightState;
}

MODE_DeviceState_t MODE_GetFanState(void)
{
    return MODE_FanState;
}

MODE_DeviceState_t MODE_GetDoorLockState(void)
{
    return MODE_DoorLockState;
}
