/**
 * @file EventLogging_Program.c
 * @author Team5 (Maryam)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "EventLogging_Interface.h"

static uint8_t LOG_u8WriteIndex   = 0U; /* 0 .. EventLogging_MaxRecords-1 */
static uint8_t LOG_u8SequenceCtr  = 0U; /* RAM-only, resets each boot -- no RTC available to timestamp with */

/**
 * @brief Convert a uint8_t to a decimal ASCII string, no sprintf (keeps
 *        flash/RAM footprint small, matches the rest of the project).
 */
static void LOG_vidU8ToString(uint8_t Value, uint8_t *Out)
{
    uint8_t Digits[3];
    uint8_t Count = 0U;
    uint8_t Index;

    if(Value==0U)
    {
        Digits[Count]=0U;
        Count++;
    }
    else
    {
        while(Value>0U)
        {
            Digits[Count] = (uint8_t)(Value%10U);
            Value = (uint8_t)(Value/10U);
            Count++;
        }
    }

    for(Index=0U; Index<Count; Index++)
    {
        Out[Index] = (uint8_t)('0'+Digits[Count-1U-Index]);
    }
    Out[Count] = (uint8_t)0U;
}

void LOG_Init(void)
{
    uint8_t Local_u8Index;

    EEPROM_ReadByte(EventLogging_EE_IndexAddr,&Local_u8Index);

    if((Local_u8Index==0xFFU) || (Local_u8Index>=EventLogging_MaxRecords))
    {
        LOG_u8WriteIndex = 0U;
        EEPROM_WriteByte(EventLogging_EE_IndexAddr,LOG_u8WriteIndex);
    }
    else
    {
        LOG_u8WriteIndex = Local_u8Index;
    }
}

void LOG_Event(EventLogging_EventType_t EventType)
{
    uint16_t Local_u16Addr = (uint16_t)(SystemMap_EE_LogRegionStart
                                         + (uint16_t)(LOG_u8WriteIndex*EventLogging_RecordSize));

    EEPROM_WriteByte(Local_u16Addr,(uint8_t)EventType);
    EEPROM_WriteByte((uint16_t)(Local_u16Addr+1U),LOG_u8SequenceCtr);
    LOG_u8SequenceCtr++;

    LOG_u8WriteIndex = (uint8_t)((LOG_u8WriteIndex+1U)%EventLogging_MaxRecords);
    EEPROM_WriteByte(EventLogging_EE_IndexAddr,LOG_u8WriteIndex);
}

void LOG_DumpToUART(void)
{
    uint8_t  Local_u8Index;
    uint8_t  Local_u8EventType;
    uint8_t  Local_u8Seq;
    uint16_t Local_u16Addr;
    uint8_t  Local_au8Num[4];

    for(Local_u8Index=0U; Local_u8Index<EventLogging_MaxRecords; Local_u8Index++)
    {
        Local_u16Addr = (uint16_t)(SystemMap_EE_LogRegionStart
                                    + (uint16_t)(Local_u8Index*EventLogging_RecordSize));

        EEPROM_ReadByte(Local_u16Addr,&Local_u8EventType);

        if(Local_u8EventType!=0xFFU) /* 0xFF = never written -- skip */
        {
            EEPROM_ReadByte((uint16_t)(Local_u16Addr+1U),&Local_u8Seq);

            UART_SendString((const uint8_t*)"EVT:");
            LOG_vidU8ToString(Local_u8EventType,Local_au8Num);
            UART_SendString(Local_au8Num);

            UART_SendString((const uint8_t*)" SEQ:");
            LOG_vidU8ToString(Local_u8Seq,Local_au8Num);
            UART_SendString(Local_au8Num);

            UART_SendString((const uint8_t*)"\r\n");
        }
        else
        {
            // empty slot, skip
        }
    }
}
