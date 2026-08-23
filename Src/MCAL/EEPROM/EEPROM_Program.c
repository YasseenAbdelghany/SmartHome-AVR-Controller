#include "EEPROM_Interface.h"

/*
 * NOTE: Register names below (EEARL_Reg, EEARH_Reg, EEDR_Reg, EECR_Reg)
 * must exist in Atmega32Register.h using the same naming convention
 * already used for DDRA_Reg / PORTA_Reg / PINA_Reg in the DIO driver.
 * Rename here if your teammates' register header uses different names.
 */

/*API's*/
EEPROM_Status_t EEPROM_WriteByte(const uint16_t Address, const uint8_t Data)
{
    EEPROM_Status_t LocalStatus = EEPROM_OK;

    if (Address <= EEPROM_MAX_ADDRESS)
    {
        /* Wait for any previous write to complete (polling) */
        while (ReadBit(EECR_Reg, EEPROM_EEWE_BIT) == 1u)
        {
            /* Busy wait */
        }

        EEARL_Reg = (uint8_t)(Address & 0xFFu);
        EEARH_Reg = (uint8_t)((Address >> 8u) & 0x03u);
        EEDR_Reg  = Data;

        /* Must set EEMWE then EEWE within 4 clock cycles (datasheet) */
        SetBit(EECR_Reg, EEPROM_EEMWE_BIT);
        SetBit(EECR_Reg, EEPROM_EEWE_BIT);
    }
    else
    {
        LocalStatus = EEPROM_INVALID_ADDRESS;
    }

    return LocalStatus;
}

EEPROM_Status_t EEPROM_ReadByte(const uint16_t Address, uint8_t *Data)
{
    EEPROM_Status_t LocalStatus = EEPROM_OK;

    if ((Address <= EEPROM_MAX_ADDRESS) && (Data != NULL))
    {
        while (ReadBit(EECR_Reg, EEPROM_EEWE_BIT) == 1u)
        {
            /* Busy wait */
        }

        EEARL_Reg = (uint8_t)(Address & 0xFFu);
        EEARH_Reg = (uint8_t)((Address >> 8u) & 0x03u);

        SetBit(EECR_Reg, EEPROM_EERE_BIT);
        *Data = EEDR_Reg;
    }
    else
    {
        LocalStatus = EEPROM_INVALID_ADDRESS;
    }

    return LocalStatus;
}

EEPROM_Status_t EEPROM_WriteBlock(const uint16_t StartAddress, const uint8_t *DataBuffer, const uint8_t Length)
{
    EEPROM_Status_t LocalStatus = EEPROM_OK;
    uint8_t Index;

    if (DataBuffer != NULL)
    {
        for (Index = 0u; Index < Length; Index++)
        {
            LocalStatus = EEPROM_WriteByte((uint16_t)(StartAddress + Index), DataBuffer[Index]);
            if (LocalStatus != EEPROM_OK)
            {
                break;
            }
        }
    }
    else
    {
        LocalStatus = EEPROM_NOK;
    }

    return LocalStatus;
}

EEPROM_Status_t EEPROM_ReadBlock(const uint16_t StartAddress, uint8_t *DataBuffer, const uint8_t Length)
{
    EEPROM_Status_t LocalStatus = EEPROM_OK;
    uint8_t Index;

    if (DataBuffer != NULL)
    {
        for (Index = 0u; Index < Length; Index++)
        {
            LocalStatus = EEPROM_ReadByte((uint16_t)(StartAddress + Index), &DataBuffer[Index]);
            if (LocalStatus != EEPROM_OK)
            {
                break;
            }
        }
    }
    else
    {
        LocalStatus = EEPROM_NOK;
    }

    return LocalStatus;
}
