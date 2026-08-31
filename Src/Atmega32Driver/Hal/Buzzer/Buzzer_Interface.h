/**
 * @file Buzzer_Interface.h
 * @author Team1
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _BUZZER_INTERFACE_
#define _BUZZER_INTERFACE_

#include <stdint.h>
#include "../../Common/Definition.h"
#include "../../Common/BitMath.h"
#include "../../Mcal/DIO/DIO_Interface.h"

#include "Buzzer_Private.h"
#include "Buzzer_Config.h"

void Buzzer_Init(uint8_t BuzzerGroup, uint8_t BuzzerPin);
void Buzzer_On(uint8_t BuzzerGroup, uint8_t BuzzerPin);
void Buzzer_Off(uint8_t BuzzerGroup, uint8_t BuzzerPin);

#endif /* BUZZER_INTERFACE */
