/**
 * @file Authentication_Interface.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief User Authentication -- EEPROM-persisted 4-digit password with
 *        lockout protection after repeated failures.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef AUTHENTICATION_INTERFACE
#define AUTHENTICATION_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/EEPROM/EEPROM_Interface.h"
#include "../SystemMap.h"
#include "../EventLogging/EventLogging_Interface.h"
#include "../AlarmSystem/AlarmSystem_Interface.h"
#include "Authentication_Private.h"
#include "Authentication_Config.h"

/**
 * @brief Load the password from EEPROM. If EEPROM is blank (first boot),
 *        seeds SystemMap_DefaultPassword and writes it through -- guarded
 *        so this only ever happens once, not on every boot.
 */
void AUTH_Init(void);

/**
 * @brief Check a 4-digit entry against the stored password.
 * @note  If already locked out, returns AUTH_LockedOut immediately
 *        without touching the failed-attempt counter again.
 *        On success: resets the failed-attempt counter and logs
 *        EVENT_LOGIN_SUCCESS.
 *        On failure: increments the RAM failed-attempt counter and logs
 *        EVENT_LOGIN_FAIL; on the 3rd consecutive failure, additionally
 *        calls ALARM_Trigger(ALARM_SourceFailedLogin) and returns
 *        AUTH_LockedOut instead of AUTH_WrongPassword.
 * @param EnteredPassword Pointer to a 4-byte buffer of entered digits.
 */
AUTH_Result_t AUTH_VerifyPassword(const uint8_t *EnteredPassword);

/**
 * @brief Overwrite the stored password. Rejected (no action) while
 *        locked out.
 * @param NewPassword Pointer to a 4-byte buffer of new digits.
 */
void AUTH_ChangePassword(const uint8_t *NewPassword);

uint8_t AUTH_GetFailedAttempts(void);
void AUTH_ResetAttempts(void);
uint8_t AUTH_IsLockedOut(void);

#endif /* AUTHENTICATION_INTERFACE */
