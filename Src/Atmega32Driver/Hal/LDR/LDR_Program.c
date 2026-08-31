/**
 * @file LDR_Program.c
 * @author Team6 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "LDR_Interface.h"

uint8_t LDR_GetLightPercentage(uint8_t ADC_Channel)
{
    uint16_t Local_u16DigitalReading;
    uint32_t Local_u32Percentage;

    Local_u16DigitalReading = ADC_ReadChannelPolling(ADC_Channel);

    Local_u32Percentage = ((uint32_t)Local_u16DigitalReading * 100UL) / LDR_ADCStepsFullScale;

    return (uint8_t)Local_u32Percentage;
}
