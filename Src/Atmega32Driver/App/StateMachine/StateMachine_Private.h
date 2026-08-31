/**
 * @file StateMachine_Private.h
 * @author Team1 -- Smart Home Controller
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef STATEMACHINE_PRIVATE
#define STATEMACHINE_PRIVATE

#include <stdint.h>

typedef enum
{
    SM_StateLogin,
    SM_StateMainMenu,
    SM_StateManualControl,
}SM_State_t;

/* Keypad button map (see KeyPad_Config.h KPD_ButtonValue):
 *   Login screen : digits 0-9 enter password, 'C' clears the entry buffer
 *   Main Menu    : '*' toggles System Mode (Manual<->Auto)
 *                  '/' enters Manual Control (only meaningful in Manual mode)
 *                  'C' logs out back to the Login screen
 *   Manual Ctrl  : '1' toggles Room Light   '2' toggles Fan
 *                  '3' toggles Door Lock    '4' toggles Alarm Enable
 *                  'C' returns to Main Menu
 */

#endif /* STATEMACHINE_PRIVATE */
