/**
 * @file AlarmSystem_Program.c
 * @author Team4 (Roaya)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "AlarmSystem_Interface.h"

static ALARM_State_t ALARM_CurrentState = ALARM_Idle;

/**
 * @brief EXTI0 ISR callback -- the emergency button pulls PD2 Low when
 *        pressed (EXTI_Falling). Kept short, as any ISR body should be:
 *        it just raises the trigger, no buzzer/EEPROM work happens here
 *        directly inside interrupt context beyond what ALARM_Trigger()
 *        itself already does (DIO write + EEPROM write, both quick).
 */
static void ALARM_vidEmergencyButtonISR(void)
{
    ALARM_Trigger(ALARM_SourceEmergencyButton);
}

void ALARM_Init(void)
{
    Buzzer_Init(SystemMap_Buzzer_Group,SystemMap_Buzzer_Pin);

    EXTI_Init(EXTI0,EXTI_Falling);
    EXTI_SetCallBack(EXTI0,ALARM_vidEmergencyButtonISR);
    /* GIE_Enable() is called once, centrally, from main() after every
     * module's Init() has run -- not here.
     */
}

void ALARM_Trigger(ALARM_Source_t Source)
{
    if(CFG_GetAlarmEnable()==CFG_AlarmEnabled)
    {
        ALARM_CurrentState = ALARM_Active;
        Buzzer_On(SystemMap_Buzzer_Group,SystemMap_Buzzer_Pin);
    }
    else
    {
        // Alarm system disabled in System Configuration: log only, stay silent
    }

    if(Source==ALARM_SourceFire)
    {
        LOG_Event(EVENT_ALARM_FIRE);
    }
    else if(Source==ALARM_SourceEmergencyButton)
    {
        LOG_Event(EVENT_ALARM_EMERGENCY_BUTTON);
    }
    else if(Source==ALARM_SourceFailedLogin)
    {
        LOG_Event(EVENT_ALARM_FAILED_LOGIN);
    }
    else
    {
        // Invalid Source: no event logged
    }
}

void ALARM_Clear(void)
{
    ALARM_CurrentState = ALARM_Idle;
    Buzzer_Off(SystemMap_Buzzer_Group,SystemMap_Buzzer_Pin);
    LOG_Event(EVENT_ALARM_CLEARED);
}

uint8_t ALARM_IsActive(void)
{
    uint8_t Local_u8Result;

    if(ALARM_CurrentState==ALARM_Active)
    {
        Local_u8Result = 1U;
    }
    else
    {
        Local_u8Result = 0U;
    }

    return Local_u8Result;
}

void ALARM_CheckFireCondition(void)
{
    uint8_t Local_u8TemperatureC = LM35_GetTemperature(SystemMap_LM35_ADCChannel);

    if(Local_u8TemperatureC>=SystemMap_FireTempThresholdC)
    {
        if(ALARM_CurrentState!=ALARM_Active)
        {
            ALARM_Trigger(ALARM_SourceFire);
        }
        else
        {
            // Already active, avoid re-triggering (and re-logging) every tick
        }
    }
    else
    {
        // Below threshold: nothing to do here (ALARM_Clear is a
        // deliberate user/APP action, not automatic on temperature drop)
    }
}
