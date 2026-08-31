/**
 * @file SystemConfig_Interface.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief System Configuration -- caches all user-tunable settings in RAM
 *        at boot, writes through to EEPROM on every change so settings
 *        survive a power cycle.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SYSTEMCONFIG_INTERFACE
#define SYSTEMCONFIG_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/EEPROM/EEPROM_Interface.h"
#include "../SystemMap.h"
#include "SystemConfig_Private.h"
#include "SystemConfig_Config.h"

/**
 * @brief Load all 4 settings from EEPROM into the RAM cache. If EEPROM is
 *        blank (freshly programmed chip, reads 0xFF), seeds the defaults
 *        from SystemConfig_Config.h and writes them through.
 */
void CFG_Init(void);

/** @brief Range-validated (0-100); rejected values leave the cache/EEPROM unchanged. */
void CFG_SetTempThreshold(uint8_t Value);
uint8_t CFG_GetTempThreshold(void);

/** @brief Range-validated (0-100); rejected values leave the cache/EEPROM unchanged. */
void CFG_SetLightThreshold(uint16_t Value);
uint16_t CFG_GetLightThreshold(void);

void CFG_SetAlarmEnable(CFG_AlarmState_t Value);
CFG_AlarmState_t CFG_GetAlarmEnable(void);

void CFG_SetSystemMode(CFG_SystemMode_t Value);
CFG_SystemMode_t CFG_GetSystemMode(void);

#endif /* SYSTEMCONFIG_INTERFACE */
