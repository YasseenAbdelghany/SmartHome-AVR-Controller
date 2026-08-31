#ifndef LED_INTERFACE
#define LED_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"

#include "Led_Private.h"
#include "Led_Config.h"

#define LED_SINK_CONNECTION      (0U)
#define LED_SOURCE_CONNECTION    (1U)

void Led_Init(uint8_t LedGroup, uint8_t LedPin);
void Led_On(uint8_t LedGroup, uint8_t LedPin, uint8_t ConnectionType);
void Led_Off(uint8_t LedGroup, uint8_t LedPin, uint8_t ConnectionType);
void Led_Toggle(uint8_t LedGroup, uint8_t LedPin);

#endif /* LED_INTERFACE */
