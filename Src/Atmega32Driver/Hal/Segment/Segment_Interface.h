#ifndef _HAL_SEGMENT_SEGMENT_INTERFACE_H
#define _HAL_SEGMENT_SEGMENT_INTERFACE_H

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"

#include "Segment_Private.h"
#include "Segment_Config.h"

void SSD_Init(uint8_t SSDGroup);

void SSD_DisplayNumber(uint8_t SSDGroup, uint8_t SSDType, uint8_t Number);
void SSD_Off(uint8_t SSDGroup, uint8_t SSDType);

#endif
