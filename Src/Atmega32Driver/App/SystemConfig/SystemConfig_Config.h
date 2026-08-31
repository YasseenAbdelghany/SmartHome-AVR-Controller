/**
 * @file SystemConfig_Config.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SYSTEMCONFIG_CONFIG
#define SYSTEMCONFIG_CONFIG

/* Defaults used only the very first time the system boots (EEPROM blank). */
#define SystemConfig_DefaultTempThreshold  30U
#define SystemConfig_DefaultLightThreshold 40U
#define SystemConfig_DefaultAlarmEnable    CFG_AlarmEnabled
#define SystemConfig_DefaultSystemMode     CFG_ModeManual

#endif /* SYSTEMCONFIG_CONFIG */
