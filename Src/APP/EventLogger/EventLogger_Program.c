#include "EventLogger_Interface.h"
#include "EventLogger_Private.h"
#include "../../MCAL/EEPROM/EEPROM_Interface.h"

static uint16_t EventLogger_CurrentAddress = EVENT_LOG_START_ADDRESS;

/**
 * @brief Initialize the Event Logger.
 *
 * @return EventLogger_Status_t
 */
EventLogger_Status_t EventLogger_Init(void)
{
    EventLogger_Status_t LocalStatus = EVENTLOGGER_OK;
    uint8_t LocalData;
    uint16_t LocalAddress;

    for (LocalAddress = EVENT_LOG_START_ADDRESS;
         LocalAddress <= EVENT_LOG_END_ADDRESS;
         LocalAddress++)
    {
        if (EEPROM_ReadByte(LocalAddress, &LocalData) != EEPROM_OK)
        {
            LocalStatus = EVENTLOGGER_NOK;
            break;
        }

        if (LocalData == 0xFFu)
        {
            EventLogger_CurrentAddress = LocalAddress;
            break;
        }
    }

    if (LocalAddress > EVENT_LOG_END_ADDRESS)
    {
        EventLogger_CurrentAddress = EVENT_LOG_START_ADDRESS;
    }

    return LocalStatus;
}

/**
 * @brief Log an event into EEPROM.
 *
 * @param Event Event to be logged.
 * @return EventLogger_Status_t
 */
EventLogger_Status_t EventLogger_Log(EventLogger_Event_t Event)
{
    EventLogger_Status_t LocalStatus = EVENTLOGGER_OK;

    if ((Event >= EVENT_LOGIN_SUCCESS) &&
        (Event <= EVENT_CONFIGURATION_CHANGED))
    {
        if (EEPROM_WriteByte(EventLogger_CurrentAddress,
                             (uint8_t)Event) != EEPROM_OK)
        {
            LocalStatus = EVENTLOGGER_NOK;
        }
        else
        {
            EventLogger_CurrentAddress++;

            if (EventLogger_CurrentAddress > EVENT_LOG_END_ADDRESS)
            {
                EventLogger_CurrentAddress = EVENT_LOG_START_ADDRESS;
            }
        }
    }
    else
    {
        LocalStatus = EVENTLOGGER_NOK;
    }

    return LocalStatus;
}