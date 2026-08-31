/**
 * @file RTM_Program.c
 * @author Team6 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "RTM_Interface.h"

static uint8_t RTM_au8LastLine0[RTM_LCD_COLS+1U];
static uint8_t RTM_au8LastLine1[RTM_LCD_COLS+1U];

static void RTM_vidU8ToString(uint8_t Value, uint8_t *Out)
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

static uint8_t RTM_u8StringsEqual(const uint8_t *A, const uint8_t *B)
{
    uint8_t Local_u8Result = 1U;
    uint8_t Local_u8Index  = 0U;

    while((Local_u8Result==1U) && (Local_u8Index<RTM_LCD_COLS))
    {
        if(A[Local_u8Index]!=B[Local_u8Index])
        {
            Local_u8Result = 0U;
        }
        else
        {
            // still matching, keep going
        }
        Local_u8Index++;
    }

    return Local_u8Result;
}

void RTM_Init(void)
{
    UART_Config_t Local_UARTConfig;
    uint8_t Local_u8Index;

    Local_UARTConfig.BaudRate = RTM_UARTBaudRate;
    Local_UARTConfig.DataBits = UART_8Bit;
    Local_UARTConfig.StopBits = UART_1StopBit;
    Local_UARTConfig.Parity   = UART_ParityDisabled;
    UART_Init(&Local_UARTConfig);

    for(Local_u8Index=0U; Local_u8Index<RTM_LCD_COLS; Local_u8Index++)
    {
        /* A byte the real status text will never produce, so the first
         * call to RTM_LCDStatusUpdate() always writes both lines in full.
         */
        RTM_au8LastLine0[Local_u8Index] = 0xFFU;
        RTM_au8LastLine1[Local_u8Index] = 0xFFU;
    }
    RTM_au8LastLine0[RTM_LCD_COLS] = 0U;
    RTM_au8LastLine1[RTM_LCD_COLS] = 0U;
}

void RTM_LCDStatusUpdate(void)
{
    uint8_t Local_au8NewLine0[RTM_LCD_COLS+1U];
    uint8_t Local_au8NewLine1[RTM_LCD_COLS+1U];
    uint8_t Local_au8Num[4];
    uint8_t Local_u8Idx;
    uint8_t Local_u8Src;

    /* Line 0: "T:xxC     M:A/M" */
    for(Local_u8Idx=0U; Local_u8Idx<RTM_LCD_COLS; Local_u8Idx++)
    {
        Local_au8NewLine0[Local_u8Idx] = (uint8_t)' ';
    }
    Local_au8NewLine0[0U] = (uint8_t)'T';
    Local_au8NewLine0[1U] = (uint8_t)':';
    RTM_vidU8ToString(LM35_GetTemperature(SystemMap_LM35_ADCChannel),Local_au8Num);
    for(Local_u8Src=0U; (Local_au8Num[Local_u8Src]!=0U) && ((2U+Local_u8Src)<14U); Local_u8Src++)
    {
        Local_au8NewLine0[2U+Local_u8Src] = Local_au8Num[Local_u8Src];
    }
    Local_au8NewLine0[2U+Local_u8Src] = (uint8_t)'C';
    Local_au8NewLine0[14U] = (uint8_t)'M';
    Local_au8NewLine0[15U] = (CFG_GetSystemMode()==CFG_ModeAuto) ? (uint8_t)'A' : (uint8_t)'M';
    Local_au8NewLine0[RTM_LCD_COLS] = 0U;

    /* Line 1: "L:xxx%  ALM:ON/-" */
    for(Local_u8Idx=0U; Local_u8Idx<RTM_LCD_COLS; Local_u8Idx++)
    {
        Local_au8NewLine1[Local_u8Idx] = (uint8_t)' ';
    }
    Local_au8NewLine1[0U] = (uint8_t)'L';
    Local_au8NewLine1[1U] = (uint8_t)':';
    RTM_vidU8ToString(LDR_GetLightPercentage(SystemMap_LDR_ADCChannel),Local_au8Num);
    for(Local_u8Src=0U; (Local_au8Num[Local_u8Src]!=0U) && ((2U+Local_u8Src)<8U); Local_u8Src++)
    {
        Local_au8NewLine1[2U+Local_u8Src] = Local_au8Num[Local_u8Src];
    }
    Local_au8NewLine1[2U+Local_u8Src] = (uint8_t)'%';
    Local_au8NewLine1[9U]  = (uint8_t)'A';
    Local_au8NewLine1[10U] = (uint8_t)'L';
    Local_au8NewLine1[11U] = (uint8_t)':';
    Local_au8NewLine1[12U] = (ALARM_IsActive()==1U) ? (uint8_t)'O' : (uint8_t)'-';
    Local_au8NewLine1[13U] = (ALARM_IsActive()==1U) ? (uint8_t)'N' : (uint8_t)' ';
    Local_au8NewLine1[RTM_LCD_COLS] = 0U;

    if(RTM_u8StringsEqual(Local_au8NewLine0,RTM_au8LastLine0)==0U)
    {
        LCD_MoveTo(0U,0U);
        LCD_WriteString(Local_au8NewLine0);
        for(Local_u8Idx=0U; Local_u8Idx<=RTM_LCD_COLS; Local_u8Idx++)
        {
            RTM_au8LastLine0[Local_u8Idx] = Local_au8NewLine0[Local_u8Idx];
        }
    }
    else
    {
        // unchanged, skip the LCD write
    }

    if(RTM_u8StringsEqual(Local_au8NewLine1,RTM_au8LastLine1)==0U)
    {
        LCD_MoveTo(1U,0U);
        LCD_WriteString(Local_au8NewLine1);
        for(Local_u8Idx=0U; Local_u8Idx<=RTM_LCD_COLS; Local_u8Idx++)
        {
            RTM_au8LastLine1[Local_u8Idx] = Local_au8NewLine1[Local_u8Idx];
        }
    }
    else
    {
        // unchanged, skip the LCD write
    }
}

void RTM_LogSensorReadings(void)
{
    uint8_t Local_au8Num[4];

    UART_SendString((const uint8_t*)"T:");
    RTM_vidU8ToString(LM35_GetTemperature(SystemMap_LM35_ADCChannel),Local_au8Num);
    UART_SendString(Local_au8Num);

    UART_SendString((const uint8_t*)" L:");
    RTM_vidU8ToString(LDR_GetLightPercentage(SystemMap_LDR_ADCChannel),Local_au8Num);
    UART_SendString(Local_au8Num);

    UART_SendString((const uint8_t*)" M:");
    RTM_vidU8ToString((uint8_t)CFG_GetSystemMode(),Local_au8Num);
    UART_SendString(Local_au8Num);

    UART_SendString((const uint8_t*)" ALM:");
    RTM_vidU8ToString(ALARM_IsActive(),Local_au8Num);
    UART_SendString(Local_au8Num);

    UART_SendString((const uint8_t*)"\r\n");
}

void RTM_LogError(uint8_t ErrorCode)
{
    uint8_t Local_au8Num[4];

    UART_SendString((const uint8_t*)"ERR:");
    RTM_vidU8ToString(ErrorCode,Local_au8Num);
    UART_SendString(Local_au8Num);
    UART_SendString((const uint8_t*)"\r\n");
}
