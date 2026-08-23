#ifndef _AUTHENTICATION_INTERFACE_H
#define _AUTHENTICATION_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>
#include "Authentication_Private.h"
#include "Authentication_Config.h"

typedef enum
{
    AUTH_OK,
    AUTH_FAIL,
    AUTH_LOCKED
} AUTH_Result_t;

/*API's*/
void            AUTH_Init(void);
AUTH_Result_t   AUTH_VerifyPassword(const uint8_t *EnteredPassword);
AUTH_Result_t   AUTH_ChangePassword(const uint8_t *NewPassword);
uint8_t         AUTH_GetFailedAttempts(void);
void            AUTH_ResetAttempts(void);
bool            AUTH_IsLockedOut(void);

#endif /*_AUTHENTICATION_INTERFACE_H*/
