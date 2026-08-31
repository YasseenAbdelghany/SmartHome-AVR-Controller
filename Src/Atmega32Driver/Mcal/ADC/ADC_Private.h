#ifndef ADC_PRIVATE
#define ADC_PRIVATE

typedef enum
{
    Bit_Mux0,
    Bit_Mux1,
    Bit_Mux2,
    Bit_Mux3,
    Bit_Mux4,
    Bit_ADLAR,
    Bit_REFS0,
    Bit_REFS1,
}ADC_ADMUXBit_t;

// 76543210
// 01000000
// 11000000
typedef enum
{
    ADC_Aref =0x00,
    ADC_Avcc =0x40,
    ADC_InternalVcc=0xC0,
}ADC_Vref_t;
// 76543210
// 00000000
// 00100000
typedef enum
{
    ADC_RightAdjust =0x00,
    ADC_LeftAdjust = 0x20,
}ADC_AdjustResult_t;
// 76543210
// 00000000
// 00000001
// 00000002
typedef enum
{
    /*SingleEnded*/
    ADC_SingleCh0,
    ADC_SingleCh1,
    ADC_SingleCh2,
    ADC_SingleCh3,
    ADC_SingleCh4,
    ADC_SingleCh5,
    ADC_SingleCh6,
    ADC_SingleCh7,
    /*DifferentialWithgain*/

    /*Differentialwithoutgain*/
    
}ADC_ChannelSelection_t;


typedef enum 
{
    Bit_ADPS0,
    Bit_ADPS1,
    Bit_ADPS2,
    Bit_ADIE,
    Bit_ADIF,
    Bit_ADATE,
    Bit_ADSC,
    Bit_ADEN,    
}ADC_ADCSRA_t;
// 76543210
// 10000000
typedef enum 
{
    ADC_Disable,
    ADC_Enable=0x80,

}ADC_Control_t;
// 76543210
// 00100000
typedef enum 
{
    ADC_SingleConversionMode,
    ADC_AutoConversionMode=0x20,
}ADC_ModeSelection_t;
// 76543210
// 00001000
typedef enum 
{
    ADC_InterruptDisable,
    ADC_InterruptEnable=0x08,
}ADC_InterruptState_t;
// 76543210
// 00000001
// 00000010

typedef enum 
{
    ADC_Prescaler2=1,    
    ADC_Prescaler4,
    ADC_Prescaler8,
    ADC_Prescaler16,
    ADC_Prescaler32,
    ADC_Prescaler64,
    ADC_Prescaler128,    
}ADC_ClockSelect_t;
// 76543210
// 00100000
// 01000000
typedef enum 
{
    ADC_FreeRunning =0x00,
    ADC_AnalogComp=0x20,
    ADC_EXTI0=0x40,
    ADC_T0CTC=0x60,
    ADC_T0OVF=0x80,
    ADC_T1CTCB=0xA0,
    ADC_T1OVF=0xC0,
    ADC_T1ICU=0xE0,
}ADC_TriggerSource_t;


typedef struct
{
    ADC_Vref_t Vref;
    ADC_AdjustResult_t Adjust;
    ADC_ClockSelect_t  Prescaler;
    ADC_ModeSelection_t Mode;
    ADC_TriggerSource_t TriggerSource;
    ADC_InterruptState_t  Interrupt;
    ADC_Control_t         State;
}ADC_Config_t;



#define ADMUX_VrefMask   0xC0
#define ADMUX_AdjustMask 0x20
#define ADCSRA_PrescallerMask 0x07
#define ADCSRA_InterruptMask 0x08
#define SFIOR_TriggerSourceMask 0xE0
#define ADCSRA_StateMask 0x80 



#endif /* ADC_PRIVATE */
