/**
 * @file LM35_Private.h
 * @author Team1 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef LM35_PRIVATE
#define LM35_PRIVATE

/* LM35 outputs 10mV per degree Celsius. With a 5V ADC reference and
 * 10-bit resolution (1024 steps), each ADC step represents:
 *     5000mV / 1024 steps = 4.8828... mV/step
 * Dividing that by 10mV per degree C gives degrees-per-step. To stay in
 * math (no float on this MCU), the conversion below scales by 10x first
 * (giving deci-Celsius) then divides back down, which keeps the rounding
 * error small without needing floating point.
 */
#define LM35_ADCStepsFullScale 1024UL
#define LM35_ReferenceMilliVolts 5000UL

#endif /* LM35_PRIVATE */
