/**
 * @file SystemConfig_Private.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SYSTEMCONFIG_PRIVATE
#define SYSTEMCONFIG_PRIVATE

#include <stdint.h>

typedef enum
{
    CFG_ModeManual,
    CFG_ModeAuto,
}CFG_SystemMode_t;

typedef enum
{
    CFG_AlarmDisabled,
    CFG_AlarmEnabled,
}CFG_AlarmState_t;

/* Reasonable sanity-check bounds -- reject Set calls with values that
 * clearly indicate a garbage/uninitialised argument rather than a real
 * user-entered threshold.
 */
#define CFG_MinTempThreshold  0U
#define CFG_MaxTempThreshold  100U
#define CFG_MinLightThreshold 0U
#define CFG_MaxLightThreshold 100U

typedef struct
{
    uint8_t          TempThreshold;
    uint16_t         LightThreshold;
    CFG_AlarmState_t AlarmEnable;
    CFG_SystemMode_t SystemMode;
}CFG_Cache_t;

#endif /* SYSTEMCONFIG_PRIVATE */
