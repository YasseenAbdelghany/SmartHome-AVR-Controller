/**
 * @file LM35_Program.c
 * @author Team1 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "LM35_Interface.h"

uint8_t LM35_GetTemperature(uint8_t ADC_Channel)
{
    uint16_t Local_u16DigitalReading;
    uint32_t Local_u32MilliVolts;
    uint32_t Local_u32TemperatureC;
    uint8_t  Local_u8Result;

    Local_u16DigitalReading = ADC_ReadChannelPolling(ADC_Channel);

    /* mV = reading * (Vref_mV / FullScaleSteps) */
    Local_u32MilliVolts = ((uint32_t)Local_u16DigitalReading * LM35_ReferenceMilliVolts)
                           / LM35_ADCStepsFullScale;

    /* LM35: 10mV per degree C, so degrees = mV / 10 */
    Local_u32TemperatureC = Local_u32MilliVolts / 10UL;

    if(Local_u32TemperatureC>255UL)
    {
        Local_u8Result = 255U; /* clamp -- should not realistically happen */
    }
    else
    {
        Local_u8Result = (uint8_t)Local_u32TemperatureC;
    }

    return Local_u8Result;
}
