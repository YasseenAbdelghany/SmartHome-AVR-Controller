#ifndef _EEPROM_PRIVATE_H
#define _EEPROM_PRIVATE_H

/* EECR Register bit positions (ATmega32 datasheet) */
#define EEPROM_EERE_BIT   0u
#define EEPROM_EEWE_BIT   1u
#define EEPROM_EEMWE_BIT  2u
#define EEPROM_EERIE_BIT  3u

/* ATmega32 internal EEPROM = 1024 bytes (0x000 - 0x3FF) */
#define EEPROM_MAX_ADDRESS 1023u

#endif /*_EEPROM_PRIVATE_H*/
