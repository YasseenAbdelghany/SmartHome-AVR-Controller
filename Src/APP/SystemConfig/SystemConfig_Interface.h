#ifndef _SYSTEMCONFIG_INTERFACE_H
#define _SYSTEMCONFIG_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>
#include "SystemConfig_Private.h"
#include "SystemConfig_Config.h"

typedef enum
{
    CFG_OK,
    CFG_INVALID_VALUE,
    CFG_WRITE_FAIL
} CFG_Status_t;

/*API's*/
void             CFG_Init(void);
CFG_Status_t     CFG_SetTempThreshold(uint8_t Value);
CFG_Status_t     CFG_SetLightThreshold(uint8_t Value);
CFG_Status_t     CFG_SetAlarmEnable(CFG_AlarmState_t State);
CFG_Status_t     CFG_SetSystemMode(CFG_SystemMode_t Mode);

/* These 4 getters are the public contract other teammates integrate against */
uint8_t          CFG_GetTempThreshold(void);
uint8_t          CFG_GetLightThreshold(void);
CFG_AlarmState_t CFG_GetAlarmEnable(void);
CFG_SystemMode_t CFG_GetSystemMode(void);

#endif /*_SYSTEMCONFIG_INTERFACE_H*/
