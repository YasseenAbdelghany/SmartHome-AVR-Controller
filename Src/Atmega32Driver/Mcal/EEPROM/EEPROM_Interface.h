/**
 * @file EEPROM_Interface.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief Internal EEPROM driver -- polling read/write, single-byte and
 *        multi-byte block helpers. Shared foundation used by Authentication
 *        (password storage), System Configuration (settings persistence)
 *        and Event Logging (0x50-0x90 log region).
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef EEPROM_INTERFACE
#define EEPROM_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../Atmega32Register.h"
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"

/**
 * @brief Write a single byte to internal EEPROM (polling -- blocks until
 *        any previous write finishes, then blocks until this write's
 *        write-cycle actually starts).
 * @note  The EEMWE->EEWE write sequence is wrapped with the timer/interrupt
 *        guard rule from the datasheet (EEMWE must be followed by EEWE
 *        within 4 clock cycles) -- global interrupts are held off for
 *        that handful of instructions so an ISR firing in between can't
 *        push the sequence past the 4-cycle window and silently drop the
 *        write.
 * @param Address EEPROM address, 0x000-0x3FF. Out-of-range addresses are
 *                ignored (no action).
 * @param Data    Byte to write.
 */
void EEPROM_WriteByte(uint16_t Address, uint8_t Data);

/**
 * @brief Read a single byte from internal EEPROM (polling).
 * @param Address EEPROM address, 0x000-0x3FF.
 * @param Data    Out-parameter, receives the read byte. NULL is ignored.
 */
void EEPROM_ReadByte(uint16_t Address, uint8_t *Data);

/**
 * @brief Write consecutive bytes starting at Address (e.g. a 4-digit
 *        password). Internally calls EEPROM_WriteByte() once per byte.
 * @param Address  First EEPROM address to write.
 * @param DataBlock Source buffer.
 * @param Length    Number of bytes to write.
 */
void EEPROM_WriteBlock(uint16_t Address, const uint8_t *DataBlock, uint16_t Length);

/**
 * @brief Read consecutive bytes starting at Address.
 * @param Address  First EEPROM address to read.
 * @param DataBlock Destination buffer, must hold at least Length bytes.
 * @param Length    Number of bytes to read.
 */
void EEPROM_ReadBlock(uint16_t Address, uint8_t *DataBlock, uint16_t Length);

#endif /* EEPROM_INTERFACE */
