/**
 * @file StateMachine_Interface.h
 * @author Team1 -- Smart Home Controller
 * @brief Main Application State Machine -- Login -> Main Menu -> Manual
 *        Control, driven by Keypad input, displayed on the LCD. This is
 *        the piece that ties every other module (Auth, Config, Operating
 *        Modes, Alarm, Event Logging, Real-Time Monitor) into one
 *        running system.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef STATEMACHINE_INTERFACE
#define STATEMACHINE_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Hal/KeyPad/KeyPad_Interface.h"
#include "../../Hal/LCD/LCD_Interface.h"
#include "../SystemMap.h"
#include "../Authentication/Authentication_Interface.h"
#include "../SystemConfig/SystemConfig_Interface.h"
#include "../OperatingModes/OperatingModes_Interface.h"
#include "../AlarmSystem/AlarmSystem_Interface.h"
#include "../EventLogging/EventLogging_Interface.h"
#include "StateMachine_Private.h"
#include "StateMachine_Config.h"

/** @brief Show the initial Login prompt on the LCD. */
void SM_Init(void);

/**
 * @brief Scan the keypad once and advance the state machine if a new key
 *        press is detected (edge-detected internally -- holding a key
 *        down does not repeat the action). Non-blocking. Register with
 *        the Scheduler (e.g. every 50ms).
 */
void SM_MainFunction(void);

#endif /* STATEMACHINE_INTERFACE */
