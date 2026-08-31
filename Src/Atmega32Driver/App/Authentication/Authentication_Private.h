/**
 * @file Authentication_Private.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef AUTHENTICATION_PRIVATE
#define AUTHENTICATION_PRIVATE

#include <stdint.h>

typedef enum
{
    AUTH_Success,
    AUTH_WrongPassword,
    AUTH_LockedOut,
}AUTH_Result_t;

#define AUTH_MaxFailedAttempts 3U

#endif /* AUTHENTICATION_PRIVATE */
