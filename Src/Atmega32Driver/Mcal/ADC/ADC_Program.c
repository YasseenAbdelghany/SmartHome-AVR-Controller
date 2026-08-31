#include "ADC_Interface.h"


// Reg =(Reg &~Mask)|Value
// 76543210
// 00001000
void ADC_Init(const ADC_Config_t * Config)
{
    if(Config!=NULL)
    {
        // 1- Confiure Voltage reference 6 ,7 
        ADMUX_Reg = (ADMUX_Reg&~ADMUX_VrefMask)|(Config->Vref);
        // 2- Configure Adjust
        ADMUX_Reg = (ADMUX_Reg&~ADMUX_AdjustMask)|(Config->Adjust);
        // 3- Configure Clock Select 
        ADCSRA_Reg = (ADCSRA_Reg&~ADCSRA_PrescallerMask)|(Config->Prescaler);
        // 4- Configure AutoMode 
        if(Config->Mode==ADC_AutoConversionMode)
        {
            SetBit(ADCSRA_Reg,Bit_ADATE);
            // 4.1 - Configure Trigger Source 
            SFIOR_Reg = (SFIOR_Reg&~SFIOR_TriggerSourceMask)|(Config->TriggerSource);
        }
        else 
        {
            ClearBit(ADCSRA_Reg,Bit_ADATE);
        }
        // 6- Interrupt State 
        ADCSRA_Reg = (ADCSRA_Reg&~ADCSRA_InterruptMask)|(Config->Interrupt);
        // 7- Enable 
        ADCSRA_Reg = (ADCSRA_Reg&~ADCSRA_StateMask)|(Config->State);
    }
}
#define ADMUX_ChannelMask  0x1F
uint16_t ADC_ReadChannelPolling(uint8_t ADC_Channel)
{
    // 76543210
    // 00011111
    uint16_t DigitalVolt = 0 ;
    // 1- Update Channel 
    ADMUX_Reg = (ADMUX_Reg&~ADMUX_ChannelMask)|(ADC_Channel&~0b11100000);
    // 2- Start Conversion -> 
    SetBit(ADCSRA_Reg,Bit_ADSC);
    // 3- wait for the Conversion to complete (Pollingon Flag on )
    while(ReadBit(ADCSRA_Reg,Bit_ADIF)== 0)
    {
        // waiting 
    }
    // 4- Clear Manual for Flag 
    SetBit(ADCSRA_Reg,Bit_ADIF);
    // 5- Read Result Check Adjust
    // BUG FIX: ReadBit() returns a plain 0/1 value, never the raw byte
    // mask ADC_LeftAdjust (0x20). Comparing against 0x20 was always
    // false, so this branch was silently dead code and Left-Adjust mode
    // never worked. Compare against 1 (or just use it as a boolean) instead.
    if(ReadBit(ADMUX_Reg,Bit_ADLAR)==1U)
    {
        // Left-Adjust: 10-bit result sits in ADCH[7:0]=bits9:2, ADCL[7:6]=bits1:0
        DigitalVolt = (uint16_t)((ADCL_Reg>>6)|(ADCH_Reg<<2));
    }
    else 
    {
        DigitalVolt = ADCData_Reg;
    }
        return DigitalVolt;
}

void ADC_StartConversionInterrupt(uint8_t ADC_Channel)
{
    ADMUX_Reg = (ADMUX_Reg&~ADMUX_ChannelMask)|(ADC_Channel&~0b11100000);
    SetBit(ADCSRA_Reg,Bit_ADSC);
}

/* Holds the function registered via ADC_SetCallBack(), called from the
 * ADC Conversion Complete ISR once a result is ready. NULL = no callback.
 */
static void (*ADC_CallBackPtr)(uint16_t ADCResult) = NULL;

void ADC_SetCallBack(void(*PF)(uint16_t ADCResult))
{
    ADC_CallBackPtr = PF;
}

void __vector_16()
{
    uint16_t Digitalvolt=0;
    // Same fix as ADC_ReadChannelPolling(): compare against 1, not 0x20.
    if(ReadBit(ADMUX_Reg,Bit_ADLAR)==1U)
    {
        Digitalvolt = (uint16_t)((ADCL_Reg>>6)|(ADCH_Reg<<2));
    }
    else 
    {
        Digitalvolt= ADCData_Reg;
    }
    /* Notify whoever registered a callback that a result is ready. */
    if(ADC_CallBackPtr!=NULL)
    {
        ADC_CallBackPtr(Digitalvolt);
    }
    else
    {
        // No callback registered, nothing to do.
    }
}