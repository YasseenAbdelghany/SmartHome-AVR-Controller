/**
 * @file RTM_Interface.h
 * @author Team6 (Khaled)
 * @brief Real-Time Response & Status Monitoring -- continuous (but
 *        change-only, non-blocking) LCD status refresh, and UART debug
 *        logging of sensor readings.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef RTM_INTERFACE
#define RTM_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Hal/LCD/LCD_Interface.h"
#include "../../Hal/LM35/LM35_Interface.h"
#include "../../Hal/LDR/LDR_Interface.h"
#include "../../Mcal/UART/UART_Interface.h"
#include "../SystemMap.h"
#include "../SystemConfig/SystemConfig_Interface.h"
#include "../OperatingModes/OperatingModes_Interface.h"
#include "../AlarmSystem/AlarmSystem_Interface.h"
#include "RTM_Private.h"
#include "RTM_Config.h"

/** @brief Initialize UART for debug logging and reset the LCD "last displayed" cache. */
void RTM_Init(void);

/**
 * @brief Refresh both LCD lines only where the content actually changed
 *        since the last call (compares against a cached copy -- avoids a
 *        full redraw, which is slow, every call). Register with the
 *        Scheduler at ~300ms; do not call from the 1ms tick directly.
 */
void RTM_LCDStatusUpdate(void);

/**
 * @brief Send one line of sensor/mode/alarm status to the PC terminal
 *        over UART. Register with the Scheduler at ~1000ms.
 */
void RTM_LogSensorReadings(void);

/**
 * @brief Send an error/event line over UART immediately (not scheduled --
 *        call this directly from wherever the error occurs).
 */
void RTM_LogError(uint8_t ErrorCode);

#endif /* RTM_INTERFACE */
