/**
 * @file T1_Interface.h
 * @author Team6
 * @brief 16-bit Timer/Counter1 driver -- used for Fan-speed PWM (OC1A/PD5).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T1_INTERFACE
#define T1_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"
#include "../Atmega32Register.h"
#include "T1_Private.h"
#include "T1_Config.h"

/**
 * @brief Configure Timer1 (mode, prescaler, OC1A/OC1B output behaviour,
 *        interrupts, initial OCR1A/OCR1B) and start it. If OC1AMode or
 *        OC1BMode is not T1_OC_Disconnected, the matching pin (PD5 for
 *        OC1A, PD4 for OC1B) is automatically set as a DIO output.
 * @param Config Pointer to a filled T1_Config_t. NULL is ignored.
 */
void T1_Init(const T1_Config_t *Config);

/** @brief Update OCR1A at runtime, e.g. to change fan PWM duty cycle. */
void T1_SetCompareA(uint16_t Value);

/** @brief Update OCR1B at runtime. */
void T1_SetCompareB(uint16_t Value);

/** @brief Read the free-running 16-bit counter value (TCNT1). */
uint16_t T1_GetCounterValue(void);

/** @brief Force the counter value (TCNT1). */
void T1_SetCounterValue(uint16_t Value);

/** @brief Register a function called from the Overflow ISR (vector 9). NULL to unregister. */
void T1_SetOVFCallBack(void (*PF)(void));

/** @brief Register a function called from the Compare-A ISR (vector 7). NULL to unregister. */
void T1_SetCompACallBack(void (*PF)(void));

/** @brief Register a function called from the Compare-B ISR (vector 8). NULL to unregister. */
void T1_SetCompBCallBack(void (*PF)(void));

/*ISR*/
void __vector_7() __attribute__((signal)); /* Timer1 Compare Match A */
void __vector_8() __attribute__((signal)); /* Timer1 Compare Match B */
void __vector_9() __attribute__((signal)); /* Timer1 Overflow        */

#endif /* T1_INTERFACE */
