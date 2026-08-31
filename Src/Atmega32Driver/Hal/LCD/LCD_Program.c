/**
 * @file LCD_Program.c
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief LCD Driver with error detection and handling
 * @version 0.3
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "LCD_Interface.h"
#include <stddef.h>

/* Error state tracking - enum defined in LCD_Interface.h */
static LCD_ErrorStatus_t LCD_LastError = LCD_ERROR_NONE;

/**
 * @brief Pulse the Enable pin so the LCD latches whatever is currently on
 *        RS/RW/Data. Every command/character write in both 8-bit and
 *        4-bit mode needs this.
 * @note  BUG FIX: the previous version set E High, then immediately set E
 *        Low with no delay in between (just a "// wait 1msec" comment,
 *        no actual delay call). The HD44780 requires the Enable pulse to
 *        be held for a minimum width to latch the data -- without this
 *        delay, commands/characters were not reliably written. This is
 *        the root cause noted in the old "@bug the Line not Work" comment
 *        on LCD_MoveTo(): Line 2's SetDDRAM command right after a prior
 *        command was especially likely to get missed.
 */
static void LCD_vidPulseEnable(void)
{
    DIO_WritePin(EGroup, EPin, DIO_Highfor1Pin);
    _delay_ms(1);
    DIO_WritePin(EGroup, EPin, DIO_Lowfor1Pin);
    _delay_ms(1);
}

#if LCD_TypeMode==Lcd_4bitMode
/**
 * @brief Send a single 4-bit nibble on D4-D7 and pulse Enable.
 * @param Nibble The 4 bits to send, right-aligned (bits 3:0 of this byte).
 */
static void LCD_vidSendNibble(uint8_t Nibble)
{
    DIO_WritePin(DataGroup, D4Pin, (uint8_t)((Nibble >> 0) & 0x01U));
    DIO_WritePin(DataGroup, D5Pin, (uint8_t)((Nibble >> 1) & 0x01U));
    DIO_WritePin(DataGroup, D6Pin, (uint8_t)((Nibble >> 2) & 0x01U));
    DIO_WritePin(DataGroup, D7Pin, (uint8_t)((Nibble >> 3) & 0x01U));
    LCD_vidPulseEnable();
}
#endif /* LCD_TypeMode==Lcd_4bitMode */

uint8_t LCD_Init()
{
    LCD_LastError = LCD_ERROR_NONE;

    /*Direction*/
    // RS -> Output
    DIO_DirectionSelectforPin(RSGroup,RSPin,DIO_Outputfor1Pin);
    // RW -> Output (RW pin not used in current config - hardwired to write mode)
    // DIO_DirectionSelectforPin(RWGroup,RWPin,DIO_Outputfor1Pin);
    // E  -> Output
    DIO_DirectionSelectforPin(EGroup,EPin,DIO_Outputfor1Pin);
    #if LCD_TypeMode==Lcd_8bitMode
        // DataPin -> All Output 
        DIO_DirectionSelectforGroup(DataGroup,DIO_Outputfor1Group);

        /*8bit Init*/
        // wait for 35msec 
        _delay_ms(35);
        // Function Set 
        // 0 0 1 DL N F x x
        // 0 0 1 1
        LCD_SendCommand(Lcd_FunctionSet);
        // wait 1msec
        _delay_ms(1);
        // DisplayOnOFF
        LCD_SendCommand(Lcd_DisplayOnOFF);
        // wait 1msec
        _delay_ms(1);
        // Clear
        LCD_SendCommand(Lcd_ClearScreen);
        // wait 2msec
        _delay_ms(2);
        //EntryMode
        LCD_SendCommand(Lcd_EntryMode);
        // wait 1msec
        _delay_ms(1);
    #elif LCD_TypeMode==Lcd_4bitMode
        // D4-D7 -> All Output, RS/RW/E already set above
        DIO_DirectionSelectforPin(DataGroup,D4Pin,DIO_Outputfor1Pin);
        DIO_DirectionSelectforPin(DataGroup,D5Pin,DIO_Outputfor1Pin);
        DIO_DirectionSelectforPin(DataGroup,D6Pin,DIO_Outputfor1Pin);
        DIO_DirectionSelectforPin(DataGroup,D7Pin,DIO_Outputfor1Pin);

        DIO_WritePin(RSGroup,RSPin,DIO_Lowfor1Pin);
        // RW pin not used in current config
        // DIO_WritePin(RWGroup,RWPin,DIO_Lowfor1Pin);

        // wait for 35msec (power-up settling)
        _delay_ms(35);
        // HD44780 4-bit init handshake: the display starts up in 8-bit
        // mode internally, so it must be sent 0x3 three times (as high
        // nibbles only) before it will accept 4-bit commands, then 0x2
        // to actually switch it into 4-bit mode.
        LCD_vidSendNibble(0x03U);
        _delay_ms(5);
        LCD_vidSendNibble(0x03U);
        _delay_ms(1);
        LCD_vidSendNibble(0x03U);
        _delay_ms(1);
        LCD_vidSendNibble(0x02U);
        _delay_ms(1);

        // From here on the display is in 4-bit mode: every command/
        // character is two nibbles (high then low), so LCD_SendCommand()
        // and LCD_WriteCharacter() below can be used normally.
        LCD_SendCommand(Lcd_FunctionSet);
        _delay_ms(1);
        LCD_SendCommand(Lcd_DisplayOnOFF);
        _delay_ms(1);
        LCD_SendCommand(Lcd_ClearScreen);
        _delay_ms(2);
        LCD_SendCommand(Lcd_EntryMode);
        _delay_ms(1);
    #endif /* LCD_TypeMode*/
    
    return (uint8_t)LCD_LastError;
}
void LCD_SendCommand(uint8_t Command)
{
    #if LCD_TypeMode==Lcd_8bitMode
        // RS -> Low
        DIO_WritePin(RSGroup,RSPin,DIO_Lowfor1Pin);
        // RW -> Low (RW pin not used in current config - hardwired to write mode)
        // DIO_WritePin(RWGroup,RWPin,DIO_Lowfor1Pin);
        // DataPin=Command 
        DIO_WriteGroup(DataGroup,Command);
        // Pulse Enable so the LCD latches the command (see LCD_vidPulseEnable note)
        LCD_vidPulseEnable();
    #elif LCD_TypeMode==Lcd_4bitMode
        DIO_WritePin(RSGroup,RSPin,DIO_Lowfor1Pin);
        // RW pin not used in current config
        // DIO_WritePin(RWGroup,RWPin,DIO_Lowfor1Pin);
        // High nibble first, then low nibble
        LCD_vidSendNibble((uint8_t)(Command >> 4));
        LCD_vidSendNibble((uint8_t)(Command & 0x0FU));
    #endif /* LCD_TypeMode*/
}

void LCD_WriteCharacter(uint8_t Character)
{
    #if LCD_TypeMode==Lcd_8bitMode
        // RS -> High
        DIO_WritePin(RSGroup,RSPin,DIO_Highfor1Pin);
        // RW -> Low (RW pin not used in current config - hardwired to write mode)
        // DIO_WritePin(RWGroup,RWPin,DIO_Lowfor1Pin);
        // DataPin=Character 
        DIO_WriteGroup(DataGroup,Character);
        // Pulse Enable so the LCD latches the character (see LCD_vidPulseEnable note)
        LCD_vidPulseEnable();
    #elif LCD_TypeMode==Lcd_4bitMode
        DIO_WritePin(RSGroup,RSPin,DIO_Highfor1Pin);
        // RW pin not used in current config
        // DIO_WritePin(RWGroup,RWPin,DIO_Lowfor1Pin);
        LCD_vidSendNibble((uint8_t)(Character >> 4));
        LCD_vidSendNibble((uint8_t)(Character & 0x0FU));
    #endif /* LCD_TypeMode*/
}

uint8_t LCD_WriteString(uint8_t *String)
{
    if(String == NULL)
    {
        LCD_LastError = LCD_ERROR_NULL_POINTER;
        return (uint8_t)LCD_ERROR_NULL_POINTER;
    }
    
    LCD_LastError = LCD_ERROR_NONE;
    uint8_t Index = 0;
    while(String[Index] != NULLChar)
    {
        LCD_WriteCharacter(String[Index]);
        Index++; 
    }
    return (uint8_t)LCD_ERROR_NONE;
}

uint8_t LCD_MoveTo(uint8_t LineNo,uint8_t DigitNo)
{
    //Select the Location Will be Displayed on Data Display RAM
    uint8_t DDRAM_Address = 0;
    
    /* Validate input parameters */
    if(DigitNo > 15U)
    {
        LCD_LastError = LCD_ERROR_INVALID_DIGIT;
        return (uint8_t)LCD_ERROR_INVALID_DIGIT;
    }
    
    switch(LineNo)
    {
        case Lcd_Line1: 
            DDRAM_Address = Lcd_Lin1Address + DigitNo;
            break;
        /* The "Line 2 not working" bug reported here was the missing
         * Enable-pulse delay fixed above in LCD_vidPulseEnable() -- the
         * address math on this line was already correct.
         */
        case Lcd_Line2: 
            DDRAM_Address = Lcd_Lin2Address + DigitNo;
            break;
        default:
            LCD_LastError = LCD_ERROR_INVALID_LINE;
            return (uint8_t)LCD_ERROR_INVALID_LINE;
    }
    
    LCD_LastError = LCD_ERROR_NONE;
    LCD_SendCommand(Lcd_SetDDRAMCommand | DDRAM_Address);
    _delay_ms(1);
    return (uint8_t)LCD_ERROR_NONE;
}


void LCD_WriteNumber(int32_t Number)
{
    /* BUG FIX (previous version):
     *   1) The print loop used a uint8_t loop counter compared with
     *      ">= 0". An unsigned value is NEVER negative, so "Counter >= 0"
     *      is always true -- this was an infinite loop.
     *   2) That same loop read NumberDigits[Counter - 1], which underflows
     *      to a huge index the moment Counter reaches 0 (0 - 1 wraps to
     *      255 for a uint8_t) -- an out-of-bounds array read.
     * Rewritten below with a digit count and a loop that counts down to
     * (and stops at) zero correctly.
     */
    uint8_t NumberDigits[10];
    uint8_t DigitCount = 0U;
    uint8_t Index;
    uint32_t LocalNumber;

    if(Number==0)
    {
        LCD_WriteCharacter('0');
    }
    else
    {
        if(Number<0)
        {
            LCD_WriteCharacter('-');
            LocalNumber = (uint32_t)(-Number);
        }
        else
        {
            LocalNumber = (uint32_t)Number;
        }

        while(LocalNumber!=0U)
        {
            // Separated Numbers, least-significant digit first
            NumberDigits[DigitCount] = (uint8_t)((LocalNumber % 10U) + '0');
            LocalNumber = LocalNumber / 10U;
            DigitCount++;
        }

        // Digits were collected least-significant-first; print them
        // back out in the correct (most-significant-first) order.
        for(Index=DigitCount; Index>0U; Index--)
        {
            LCD_WriteCharacter(NumberDigits[Index-1U]);
        }
    }
}

uint8_t LCD_StoreSpecialCharacter(uint8_t *SpecialCharacter,uint8_t Location)
{
    /* BUG FIX: "uint8_t Index" was declared in the middle of the function
     * body (after executable statements had already run). This violates
     * MISRA's "declare all variables at the top of the block" rule and
     * is rejected outright by strict C90 compilation. Moved to the top.
     */
    uint8_t CGRAM_Address;
    uint8_t Index;

    /* Error detection: check for NULL pointer */
    if(SpecialCharacter == NULL)
    {
        LCD_LastError = LCD_ERROR_NULL_POINTER;
        return (uint8_t)LCD_ERROR_NULL_POINTER;
    }
    
    /* Error detection: validate location (only 8 CGRAM locations 0-7 exist) */
    if(Location >= 8U)
    {
        LCD_LastError = LCD_ERROR_INVALID_LOCATION;
        return (uint8_t)LCD_ERROR_INVALID_LOCATION;
    }

    LCD_LastError = LCD_ERROR_NONE;
    CGRAM_Address = (uint8_t)(Location * 8U);
    LCD_SendCommand((uint8_t)(0x40U | CGRAM_Address)); // Go To CGRAM
    for(Index = 0U; Index < 8U; Index++)
    {
        LCD_WriteCharacter(SpecialCharacter[Index]);
    }
    LCD_MoveTo(Lcd_Line1, 0U);  // Back to DDRAM
    return (uint8_t)LCD_ERROR_NONE;
}

/**
 * @brief Get the last error that occurred in the LCD driver.
 * @return LCD_ErrorStatus_t - The error status enumeration value
 * 
 * @details Returns the status of the last LCD operation. Use this function
 *          after calling other LCD functions to check if an error occurred.
 *          Error codes:
 *          - LCD_ERROR_NONE: No error
 *          - LCD_ERROR_INVALID_LINE: Invalid line number in LCD_MoveTo()
 *          - LCD_ERROR_INVALID_DIGIT: Invalid digit position in LCD_MoveTo()
 *          - LCD_ERROR_NULL_POINTER: NULL pointer passed to function
 *          - LCD_ERROR_INIT_FAILED: LCD initialization failed
 *          - LCD_ERROR_INVALID_LOCATION: Invalid CGRAM location in LCD_StoreSpecialCharacter()
 */
LCD_ErrorStatus_t LCD_GetLastError(void)
{
    return LCD_LastError;
}

/**
 * @brief Clear the last error flag in the LCD driver.
 * @return void
 * 
 * @details Resets the error status to LCD_ERROR_NONE. Call this function
 *          after handling an error or before starting a new sequence of
 *          LCD operations.
 */
void LCD_ClearError(void)
{
    LCD_LastError = LCD_ERROR_NONE;
}
