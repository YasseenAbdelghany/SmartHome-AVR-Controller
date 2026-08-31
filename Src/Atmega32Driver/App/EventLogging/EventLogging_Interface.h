/**
 * @file EventLogging_Interface.h
 * @author Team5 (Maryam)
 * @brief Event Logging -- records critical system events into the
 *        EEPROM log region (0x50-0x8F) as a circular buffer, and
 *        supports dumping the log over UART for review/debug.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef EVENTLOGGING_INTERFACE
#define EVENTLOGGING_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/EEPROM/EEPROM_Interface.h"
#include "../../Mcal/UART/UART_Interface.h"
#include "../SystemMap.h"
#include "EventLogging_Private.h"
#include "EventLogging_Config.h"

typedef enum
{
    EVENT_SYSTEM_BOOT,
    EVENT_LOGIN_SUCCESS,
    EVENT_LOGIN_FAIL,
    EVENT_LOCKOUT,
    EVENT_CONFIG_CHANGED,
    EVENT_ALARM_FIRE,
    EVENT_ALARM_EMERGENCY_BUTTON,
    EVENT_ALARM_FAILED_LOGIN,
    EVENT_ALARM_CLEARED,
    EVENT_MODE_CHANGED,
}EventLogging_EventType_t;

/**
 * @brief Initialize the logging module's write-index from EEPROM (or
 *        start a fresh log if this is the first boot).
 */
void LOG_Init(void);

/**
 * @brief Record an event. Writes a 2-byte record [EventType][SeqNo] into
 *        the next circular-buffer slot in the EEPROM log region, wrapping
 *        back to the start once full (oldest entries get overwritten).
 * @param EventType One of the EventLogging_EventType_t values.
 */
void LOG_Event(EventLogging_EventType_t EventType);

/**
 * @brief Dump every record currently in the log region over UART, one
 *        line per record, for debug/audit review on a PC terminal.
 */
void LOG_DumpToUART(void);

#endif /* EVENTLOGGING_INTERFACE */
