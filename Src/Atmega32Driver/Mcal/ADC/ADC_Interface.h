#ifndef ADC_INTERFACE
#define ADC_INTERFACE
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"

#include <stdint.h>
#include "ADC_Private.h"
#include "ADC_Config.h"

void ADC_Init(const ADC_Config_t * Config);

uint16_t ADC_ReadChannelPolling(uint8_t ADC_Channel);

void ADC_StartConversionInterrupt(uint8_t ADC_Channel);

/**/
void ADC_SetCallBack(void(*PF)(uint16_t ADCResult));

void __vector_16()  __attribute__((signal));
#endif /* ADC_INTERFACE */
