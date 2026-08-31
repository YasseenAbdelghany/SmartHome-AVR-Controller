/**
 * @file AlarmSystem_Private.h
 * @author Team4 (Roaya)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef ALARMSYSTEM_PRIVATE
#define ALARMSYSTEM_PRIVATE

typedef enum
{
    ALARM_SourceFire,
    ALARM_SourceEmergencyButton,
    ALARM_SourceFailedLogin,
}ALARM_Source_t;

typedef enum
{
    ALARM_Idle,
    ALARM_Active,
}ALARM_State_t;

#endif /* ALARMSYSTEM_PRIVATE */
