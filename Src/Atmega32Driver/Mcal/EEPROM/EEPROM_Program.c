/**
 * @file EEPROM_Program.c
 * @author Yasseen Ahmed EL-Sayed (yasseen.ahmed2005@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "EEPROM_Interface.h"

/* Global Interrupt Enable bit position within SREG. */
#define Bit_SREG_I 7

void EEPROM_WriteByte(uint16_t Address, uint8_t Data)
{
    uint8_t Local_SREGSave;

    if(Address<=EEPROM_MaxAddress)
    {
        /* 1- Wait for any previous write to finish */
        while(ReadBit(EECR_Reg,Bit_EEWE)==1U)
        {
            // waiting
        }
        /* 2- Set up address and data registers */
        EEAR_Reg = Address;
        EEDR_Reg = Data;

        /* 3- EEMWE must be followed by EEWE within 4 clock cycles, or the
         * write is silently cancelled by hardware. Hold off interrupts for
         * this handful of instructions so an ISR can't land in between and
         * blow that 4-cycle budget (this was flagged as an open blocker --
         * fixed here with a save/restore of SREG rather than a blind
         * enable, so this function is safe to call regardless of whatever
         * interrupt state the caller was already in).
         */
        Local_SREGSave = SREG_Reg;
        ClearBit(SREG_Reg,Bit_SREG_I);

        SetBit(EECR_Reg,Bit_EEMWE);
        SetBit(EECR_Reg,Bit_EEWE);

        SREG_Reg = Local_SREGSave;
    }
    else
    {
        // Out-of-range address: no action
    }
}

void EEPROM_ReadByte(uint16_t Address, uint8_t *Data)
{
    if((Data!=NULL) && (Address<=EEPROM_MaxAddress))
    {
        /* Wait for any pending write to finish first -- reading while a
         * write is in progress is not allowed by the hardware.
         */
        while(ReadBit(EECR_Reg,Bit_EEWE)==1U)
        {
            // waiting
        }
        EEAR_Reg = Address;
        SetBit(EECR_Reg,Bit_EERE);
        *Data = EEDR_Reg;
    }
    else
    {
        // NULL pointer or out-of-range address: no action
    }
}

void EEPROM_WriteBlock(uint16_t Address, const uint8_t *DataBlock, uint16_t Length)
{
    uint16_t Index;

    if(DataBlock!=NULL)
    {
        for(Index=0U; Index<Length; Index++)
        {
            EEPROM_WriteByte((uint16_t)(Address+Index), DataBlock[Index]);
        }
    }
    else
    {
        // NULL pointer: no action
    }
}

void EEPROM_ReadBlock(uint16_t Address, uint8_t *DataBlock, uint16_t Length)
{
    uint16_t Index;

    if(DataBlock!=NULL)
    {
        for(Index=0U; Index<Length; Index++)
        {
            EEPROM_ReadByte((uint16_t)(Address+Index), &DataBlock[Index]);
        }
    }
    else
    {
        // NULL pointer: no action
    }
}
