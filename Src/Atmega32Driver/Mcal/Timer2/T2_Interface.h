/**
 * @file T2_Interface.h
 * @author Team6
 * @brief 8-bit Timer/Counter2 driver.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T2_INTERFACE
#define T2_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"
#include "T2_Private.h"
#include "T2_Config.h"

/**
 * @brief Configure Timer2 (mode, prescaler, OC2 output behaviour,
 *        interrupts and the initial OCR2 compare value) and start it.
 * @param Config Pointer to a filled T2_Config_t. NULL is ignored.
 */
void T2_Init(const T2_Config_t *Config);

/** @brief Update the Output Compare Register (OCR2) at runtime. */
void T2_SetCompareValue(uint8_t Value);

/** @brief Read the free-running counter value (TCNT2). */
uint8_t T2_GetCounterValue(void);

/** @brief Force the counter value (TCNT2). */
void T2_SetCounterValue(uint8_t Value);

/** @brief Register a function called from the Overflow ISR (vector 5). NULL to unregister. */
void T2_SetOVFCallBack(void (*PF)(void));

/** @brief Register a function called from the Compare Match ISR (vector 4). NULL to unregister. */
void T2_SetCompareCallBack(void (*PF)(void));

/*ISR*/
void __vector_4() __attribute__((signal)); /* Timer2 Compare Match */
void __vector_5() __attribute__((signal)); /* Timer2 Overflow      */

#endif /* T2_INTERFACE */
