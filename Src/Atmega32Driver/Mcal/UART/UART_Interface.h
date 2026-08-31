/**
 * @file UART_Interface.h
 * @author Team6 (Khaled)
 * @brief USART driver -- interrupt-driven TX and RX ring buffers, so
 *        sending/receiving debug data never blocks the real-time loop.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef UART_INTERFACE
#define UART_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"
#include "UART_Private.h"
#include "UART_Config.h"

/**
 * @brief Configure the USART (baud rate, frame format) and enable TX, RX
 *        and the RX-Complete interrupt. TX is only interrupt-enabled once
 *        there is actually something queued (see UART_SendByte).
 * @param Config Pointer to a filled UART_Config_t. NULL is ignored.
 */
void UART_Init(const UART_Config_t *Config);

/**
 * @brief Queue a single byte for transmission. Non-blocking: pushes into
 *        the TX ring buffer and returns immediately -- the UDRE interrupt
 *        drains it in the background. If the buffer is full, the byte is
 *        dropped rather than blocking the caller.
 */
void UART_SendByte(uint8_t Data);

/** @brief Queue a null-terminated string for transmission (byte by byte). */
void UART_SendString(const uint8_t *String);

/**
 * @brief Check whether at least one received byte is waiting.
 * @return 1 if data is available, 0 otherwise.
 */
uint8_t UART_IsDataAvailable(void);

/**
 * @brief Pop the oldest received byte. Does not block -- call
 *        UART_IsDataAvailable() first. Returns 0 if nothing is available.
 */
uint8_t UART_ReceiveByte(void);

/*ISR*/
void __vector_13() __attribute__((signal)); /* USART RX Complete       */
void __vector_14() __attribute__((signal)); /* USART Data Reg. Empty   */

#endif /* UART_INTERFACE */
