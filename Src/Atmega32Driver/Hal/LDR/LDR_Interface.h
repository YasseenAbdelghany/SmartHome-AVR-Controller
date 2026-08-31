/**
 * @file LDR_Interface.h
 * @author Team6 (Khaled)
 * @brief LDR (light-dependent resistor) driver, built on the MCAL ADC
 *        driver (polling read).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef LDR_INTERFACE
#define LDR_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/ADC/ADC_Interface.h"
#include "LDR_Private.h"
#include "LDR_Config.h"

/**
 * @brief Read the LDR on the given ADC channel and convert it to a
 *        light-level percentage.
 * @note  The LDR is assumed wired as the top half of a voltage divider
 *        (LDR from VCC to the ADC pin, fixed resistor from the ADC pin
 *        to GND), so a HIGHER ADC reading means MORE light (lower LDR
 *        resistance in bright conditions pulls the node closer to VCC).
 *        If your circuit wires the divider the other way round, invert
 *        the result (100 - value) at the call site, or ask before
 *        changing this driver, since it changes the polarity for every
 *        caller (Operating Modes' Auto-mode light threshold included).
 * @param ADC_Channel ADC channel the LDR's divider node is wired to
 *                     (e.g. ADC_SingleCh1).
 * @return uint8_t Light level as a percentage, 0 (dark) to 100 (bright).
 */
uint8_t LDR_GetLightPercentage(uint8_t ADC_Channel);

#endif /* LDR_INTERFACE */
