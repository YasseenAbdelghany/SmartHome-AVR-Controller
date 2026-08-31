/**
 * @file Button_Interface.h
 * @author Team1
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _HAL_BUTTON_BUTTON_INTERFACE_H
#define _HAL_BUTTON_BUTTON_INTERFACE_H

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"
#include "Button_Private.h"

void Btn_Init(uint8_t ButtonGroup,uint8_t ButtonPin,uint8_t Connection);

uint8_t Btn_ReadState(uint8_t ButtonGroup,uint8_t ButtonPin,uint8_t Connection);

#endif /*_HAL_BUTTON_BUTTON_INTERFACE_H*/