#ifndef _EEPROM_INTERFACE_H
#define _EEPROM_INTERFACE_H
#include <stdint.h>
#include "../BitMath.h"
#include "../Atmega32Register.h"
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"

typedef enum
{
    EEPROM_OK,
    EEPROM_NOK,
    EEPROM_INVALID_ADDRESS
} EEPROM_Status_t;

/*API's*/
EEPROM_Status_t EEPROM_WriteByte(uint16_t Address, uint8_t Data);
EEPROM_Status_t EEPROM_ReadByte(uint16_t Address, uint8_t *Data);
EEPROM_Status_t EEPROM_WriteBlock(uint16_t StartAddress, const uint8_t *DataBuffer, uint8_t Length);
EEPROM_Status_t EEPROM_ReadBlock(uint16_t StartAddress, uint8_t *DataBuffer, uint8_t Length);

#endif /*_EEPROM_INTERFACE_H*/
