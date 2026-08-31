/**
 * @file T0_Interface.h
 * @author Team1
 * @brief 8-bit Timer/Counter0 driver.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T0_INTERFACE
#define T0_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"
#include "T0_Private.h"
#include "T0_Config.h"

/**
 * @brief Configure Timer0 (mode, prescaler, OC0 output behaviour,
 *        interrupts and the initial OCR0 compare value) and start it.
 * @param Config Pointer to a filled T0_Config_t. NULL is ignored.
 */
void T0_Init(const T0_Config_t *Config);

/**
 * @brief Update the Output Compare Register (OCR0) at runtime, e.g. to
 *        change a system-tick period or a PWM duty cycle.
 */
void T0_SetCompareValue(uint8_t Value);

/** @brief Read the free-running counter value (TCNT0). */
uint8_t T0_GetCounterValue(void);

/** @brief Force the counter value (TCNT0), e.g. to resync a tick. */
void T0_SetCounterValue(uint8_t Value);

/** @brief Register a function called from the Overflow ISR (vector 11). NULL to unregister. */
void T0_SetOVFCallBack(void (*PF)(void));

/** @brief Register a function called from the Compare Match ISR (vector 10). NULL to unregister. */
void T0_SetCompareCallBack(void (*PF)(void));

/*ISR*/
void __vector_10() __attribute__((signal)); /* Timer0 Compare Match */
void __vector_11() __attribute__((signal)); /* Timer0 Overflow      */

#endif /* T0_INTERFACE */
