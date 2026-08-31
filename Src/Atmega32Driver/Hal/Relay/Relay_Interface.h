/**
 * @file Relay_Interface.h
 * @author Team1 (Soha)
 * @brief Relay driver -- used for Fan/AC and Door Lock (both are
 *        on/off loads per the README, not PWM-speed-controlled).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef RELAY_INTERFACE
#define RELAY_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"
#include "Relay_Private.h"
#include "Relay_Config.h"

void Relay_Init(uint8_t RelayGroup, uint8_t RelayPin);
void Relay_On(uint8_t RelayGroup, uint8_t RelayPin, uint8_t ConnectionType);
void Relay_Off(uint8_t RelayGroup, uint8_t RelayPin, uint8_t ConnectionType);

#endif /* RELAY_INTERFACE */
