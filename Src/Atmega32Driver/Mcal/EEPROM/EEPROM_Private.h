/**
 * @file EEPROM_Private.h
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief Internal EEPROM private definitions.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note EECR bit positions verified against the ATmega32(L) datasheet:
 *       EECR = -(7) -(6) -(5) -(4) EERIE(3) EEMWE(2) EEWE(1) EERE(0)
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef EEPROM_PRIVATE
#define EEPROM_PRIVATE

#define Bit_EERE  0
#define Bit_EEWE  1
#define Bit_EEMWE 2
#define Bit_EERIE 3
#define EEPROM_ErasedValue 0xFFU
/* ATmega32 has 1KB of internal EEPROM: valid addresses are 0x000-0x3FF. */
#define EEPROM_MinAddress 0x000U
#define EEPROM_MaxAddress 0x3FFU

#endif /* EEPROM_PRIVATE */
