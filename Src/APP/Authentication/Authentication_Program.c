#include "Authentication_Interface.h"
#include "../../MCAL/EEPROM/EEPROM_Interface.h"

/* TODO (integration): #include "../AlarmHandler/AlarmHandler_Interface.h"   -> owned by Alarm teammate */
/* TODO (integration): #include "../EventLogging/EventLogging_Interface.h"  -> owned by Logging teammate */

static uint8_t AUTH_FailedAttempts = 0u;
static bool    AUTH_LockedOutFlag  = false;

/*API's*/
void AUTH_Init(void)
{
    AUTH_FailedAttempts = 0u;
    AUTH_LockedOutFlag  = false;
}

AUTH_Result_t AUTH_VerifyPassword(const uint8_t *EnteredPassword)
{
    AUTH_Result_t LocalResult = AUTH_FAIL;
    uint8_t StoredPassword[AUTH_PASSWORD_LENGTH];
    uint8_t Index;
    bool    Match = true;

    if (AUTH_LockedOutFlag == true)
    {
        LocalResult = AUTH_LOCKED;
    }
    else if (EnteredPassword != NULL)
    {
        (void)EEPROM_ReadBlock(AUTH_EEPROM_PASSWORD_ADDR, StoredPassword, AUTH_PASSWORD_LENGTH);

        for (Index = 0u; Index < AUTH_PASSWORD_LENGTH; Index++)
        {
            if (StoredPassword[Index] != EnteredPassword[Index])
            {
                Match = false;
            }
        }

        if (Match == true)
        {
            LocalResult = AUTH_OK;
            AUTH_FailedAttempts = 0u;
            /* TODO: LOG_Event(EVENT_LOGIN_SUCCESS); */
        }
        else
        {
            AUTH_FailedAttempts++;
            /* TODO: LOG_Event(EVENT_LOGIN_FAIL); */

            if (AUTH_FailedAttempts >= AUTH_MAX_FAILED_ATTEMPTS)
            {
                AUTH_LockedOutFlag = true;
                LocalResult = AUTH_LOCKED;
                /* TODO: ALARM_Trigger(ALARM_MAX_ATTEMPTS); */
            }
            else
            {
                LocalResult = AUTH_FAIL;
            }
        }
    }
    else
    {
        LocalResult = AUTH_FAIL;
    }

    return LocalResult;
}

AUTH_Result_t AUTH_ChangePassword(const uint8_t *NewPassword)
{
    AUTH_Result_t LocalResult = AUTH_FAIL;

    if (NewPassword != NULL)
    {
        if (EEPROM_WriteBlock(AUTH_EEPROM_PASSWORD_ADDR, NewPassword, AUTH_PASSWORD_LENGTH) == EEPROM_OK)
        {
            LocalResult = AUTH_OK;
            /* TODO: LOG_Event(EVENT_CONFIG_CHANGED); */
        }
    }

    return LocalResult;
}

uint8_t AUTH_GetFailedAttempts(void)
{
    return AUTH_FailedAttempts;
}

void AUTH_ResetAttempts(void)
{
    AUTH_FailedAttempts = 0u;
    AUTH_LockedOutFlag  = false;
}

bool AUTH_IsLockedOut(void)
{
    return AUTH_LockedOutFlag;
}
