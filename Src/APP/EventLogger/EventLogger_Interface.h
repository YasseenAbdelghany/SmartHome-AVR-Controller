#ifndef _EVENTLOGGER_INTERFACE_H
#define _EVENTLOGGER_INTERFACE_H

#include <stdint.h>

typedef enum
{
    EVENT_LOGIN_SUCCESS = 1u,
    EVENT_LOGIN_FAILED,
    EVENT_ALARM_TRIGGERED,
    EVENT_CONFIGURATION_CHANGED
} EventLogger_Event_t;

typedef enum
{
    EVENTLOGGER_OK,
    EVENTLOGGER_NOK
} EventLogger_Status_t;

/*API's*/
EventLogger_Status_t EventLogger_Init(void);
EventLogger_Status_t EventLogger_Log(EventLogger_Event_t Event);

#endif