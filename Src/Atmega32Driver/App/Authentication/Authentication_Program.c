/**
 * @file Authentication_Program.c
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief Authentication module implementation.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Authentication_Interface.h"
static uint8_t AUTH_u8FailedAttempts = 0U;

/**
 * @brief Initializes the Authentication module.
 *
 *        Checks whether the EEPROM password area is blank.
 *        If the EEPROM is blank, the default password is stored.
 *        Otherwise, the existing password remains unchanged.
 *
 * @param None.
 *
 * @return None.
 */
void AUTH_Init(void)
{
    uint8_t Local_u8EEPROMFirstByte = 0U;
    static const uint8_t Local_au8DefaultPassword[SystemMap_EE_PasswordLength] = SystemMap_DefaultPassword;

    /*
     * Check the first byte of the stored password.
     * The EEPROM erased state is used to detect first boot.
     *
     * The default password must not be written on every reset,
     * otherwise an existing user password would be overwritten.
     */
    EEPROM_ReadByte(
        SystemMap_EE_PasswordAddr,
        &Local_u8EEPROMFirstByte);

    if (Local_u8EEPROMFirstByte == EEPROM_ErasedValue)
    {
        EEPROM_WriteBlock(
            SystemMap_EE_PasswordAddr,
            Local_au8DefaultPassword,
            SystemMap_EE_PasswordLength);
    }
    else
    {
        /*
         * EEPROM already contains a configured password.
         * Keep the stored password unchanged.
         */
    }

    AUTH_u8FailedAttempts = 0U;
}

/**
 * @brief Verifies the entered password against the stored password.
 *
 * @param EnteredPassword Pointer to the password entered by the user.
 *
 * @return Authentication result.
 */
AUTH_Result_t AUTH_VerifyPassword(
    const uint8_t *EnteredPassword)
{
    AUTH_Result_t Local_Result = AUTH_WrongPassword;
    uint8_t Local_au8StoredPassword[SystemMap_EE_PasswordLength] = {0U};
    uint8_t Local_u8PasswordIndex = 0U;
    uint8_t Local_u8PasswordMatch = 1U;

    if (EnteredPassword == NULL)
    {
        Local_Result = AUTH_WrongPassword;
    }
    else if (AUTH_IsLockedOut() == 1U)
    {
        Local_Result = AUTH_LockedOut;
    }
    else
    {
        EEPROM_ReadBlock(
            SystemMap_EE_PasswordAddr,
            Local_au8StoredPassword,
            SystemMap_EE_PasswordLength);

        for (Local_u8PasswordIndex = 0U;
             Local_u8PasswordIndex < SystemMap_EE_PasswordLength;
             Local_u8PasswordIndex++)
        {
            if (Local_au8StoredPassword[Local_u8PasswordIndex] !=
                EnteredPassword[Local_u8PasswordIndex])
            {
                Local_u8PasswordMatch = 0U;
            }
            else
            {
                /*
                 * Current password digit matches.
                 * Continue checking the remaining digits.
                 */
            }
        }

        if (Local_u8PasswordMatch == 1U)
        {
            AUTH_u8FailedAttempts = 0U;

            LOG_Event(EVENT_LOGIN_SUCCESS);

            Local_Result = AUTH_Success;
        }
        else
        {
            AUTH_u8FailedAttempts++;

            LOG_Event(EVENT_LOGIN_FAIL);

            if (AUTH_u8FailedAttempts >= AUTH_MaxFailedAttempts)
            {
                ALARM_Trigger(ALARM_SourceFailedLogin);

                LOG_Event(EVENT_LOCKOUT);

                Local_Result = AUTH_LockedOut;
            }
            else
            {
                Local_Result = AUTH_WrongPassword;
            }
        }
    }

    return Local_Result;
}

/**
 * @brief Changes the current system password.
 *
 * @param NewPassword Pointer to the new password.
 *
 * @return None.
 */
void AUTH_ChangePassword(
    const uint8_t *NewPassword)
{
    if (NewPassword == NULL)
    {
        /*
         * Invalid password pointer.
         * Do not access EEPROM.
         */
    }
    else if (AUTH_IsLockedOut() == 0U)
    {
        EEPROM_WriteBlock(
            SystemMap_EE_PasswordAddr,
            NewPassword,
            SystemMap_EE_PasswordLength);

        LOG_Event(EVENT_CONFIG_CHANGED);
    }
    else
    {
        /*
         * System is locked out.
         * Password change is rejected.
         */
    }
}

/**
 * @brief Gets the number of consecutive failed authentication attempts.
 *
 * @param None.
 *
 * @return Number of failed authentication attempts.
 */
uint8_t AUTH_GetFailedAttempts(void)
{
    return AUTH_u8FailedAttempts;
}

/**
 * @brief Resets the failed authentication attempt counter.
 *
 * @param None.
 *
 * @return None.
 */
void AUTH_ResetAttempts(void)
{
    AUTH_u8FailedAttempts = 0U;
}

/**
 * @brief Checks whether the authentication system is locked out.
 *
 * @param None.
 *
 * @return 1U if the system is locked out, otherwise 0U.
 */
uint8_t AUTH_IsLockedOut(void)
{
    uint8_t Local_u8LockoutStatus = 0U;

    if (AUTH_u8FailedAttempts >= AUTH_MaxFailedAttempts)
    {
        Local_u8LockoutStatus = 1U;
    }
    else
    {
        Local_u8LockoutStatus = 0U;
    }

    return Local_u8LockoutStatus;
}