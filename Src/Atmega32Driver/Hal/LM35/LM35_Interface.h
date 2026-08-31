/**
 * @file LM35_Interface.h
 * @author Team1 (Khaled)
 * @brief LM35 analog temperature sensor driver, built on the MCAL ADC
 *        driver (polling read).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef LM35_INTERFACE
#define LM35_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/ADC/ADC_Interface.h"
#include "LM35_Private.h"
#include "LM35_Config.h"

/**
 * @brief Read the LM35 on the given ADC channel and convert it to degrees
 *        Celsius. Assumes ADC_Init() has already been called with a 5V
 *        (AVCC) reference and right-adjusted result -- LM35's usable
 *        range (0-100C+) fits well within that.
 * @param ADC_Channel ADC channel the LM35's output pin is wired to
 *                     (e.g. ADC_SingleCh0).
 * @return uint8_t Temperature in whole degrees Celsius (0-255 range,
 *                 which comfortably covers LM35's -55C to +150C spec
 *                 for any realistic room-temperature use case; negative
 *                 temperatures are clamped to 0).
 */
uint8_t LM35_GetTemperature(uint8_t ADC_Channel);

#endif /* LM35_INTERFACE */
