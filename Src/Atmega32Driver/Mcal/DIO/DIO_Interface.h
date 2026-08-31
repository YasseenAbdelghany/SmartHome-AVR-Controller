#ifndef _DIO_INTERFACE_H
#define _DIO_INTERFACE_H
#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"
#include "DIO_Private.h"
#include "DIO_Config.h"


/*API's*/
// Direction (input / output )
void DIO_DirectionSelectforPin(const uint8_t GroupName , const uint8_t PinNo,const uint8_t DirectionState);
void DIO_DirectionSelectforGroup(const uint8_t GroupName,  const uint8_t DirectionState);

// Output Value (low / High )
void DIO_WritePin(const uint8_t GroupName , const uint8_t PinNo,const uint8_t OutputValue);
void DIO_WriteGroup(const uint8_t GroupName,  const uint8_t OutputValue);

// InputState 
void DIO_ReadPin(const uint8_t GroupName , const uint8_t PinNo, uint8_t *InputState);
// uint8_t DIO_ReadPin(const uint8_t GroupName , const uint8_t PinNo);
void DIO_ReadGroup(const uint8_t GroupName , uint8_t *InputState);
// uint8_t DIO_ReadGroup(const uint8_t GroupName );


// Toggle 
void DIO_TogglePin(const uint8_t GroupName , const uint8_t PinNo);
void DIO_ToggleGroup(const uint8_t GroupName );
#endif /*_DIO_INTERFACE_H*/