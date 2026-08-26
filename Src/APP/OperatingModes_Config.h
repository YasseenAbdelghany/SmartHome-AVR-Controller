/**
 * @file OperatingModes_Config.h
 * @author Soha Hossam
 * @brief Tunable parameters for the Operating Modes (Manual/Auto) module.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _OPERATINGMODES_CONFIG_H
#define _OPERATINGMODES_CONFIG_H

/*
 * Hysteresis margin (same unit as the matching SystemConfig threshold) added
 * around CFG_GetTempThreshold()/CFG_GetLightThreshold() so the Fan relay /
 * Room-Light LED do not chatter when a sensor reading sits right on the
 * threshold line.
 *
 * Keep both at 0u to match the literal spec exactly:
 *   Temperature > Threshold  -> Fan ON,   otherwise OFF
 *   LDR Level   < Threshold  -> Light ON, otherwise OFF
 */
#define MODE_TEMP_HYSTERESIS     0u
#define MODE_LIGHT_HYSTERESIS    0u

#endif /*_OPERATINGMODES_CONFIG_H*/
