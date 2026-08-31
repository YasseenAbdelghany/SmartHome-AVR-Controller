/**
 * @file LCD_Interface.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * @note This Driver Support control on 1 LCD 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef LCD_Interface
#define LCD_Interface

#include <stdint.h>

/* Delay macro implementation 
 * Try to use avr-libc if available, otherwise use fallback implementation
 * This allows compilation even without full AVR-libc setup
 */
#ifndef _delay_ms
    /* Fallback delay implementation for non-AVR compilers or missing avr-libc */
    #define _delay_ms(ms) { \
        volatile uint32_t delay_count = (uint32_t)(ms) * 2000; \
        while(delay_count--); \
    }
#else
    /* avr-libc is available, _delay_ms is already defined */
#endif

#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"

#include "LCD_Private.h"
#include "LCD_Config.h"

/* Error Status Typedef */
typedef enum {
    LCD_ERROR_NONE = 0,
    LCD_ERROR_INVALID_LINE = 1,
    LCD_ERROR_INVALID_DIGIT = 2,
    LCD_ERROR_NULL_POINTER = 3,
    LCD_ERROR_INIT_FAILED = 4,
    LCD_ERROR_INVALID_LOCATION = 5
} LCD_ErrorStatus_t;

/* Function Declarations */
uint8_t LCD_Init();
void LCD_SendCommand(uint8_t Command);
void LCD_WriteCharacter(uint8_t Character);

uint8_t LCD_WriteString(uint8_t *String);
uint8_t LCD_MoveTo(uint8_t LineNo,uint8_t DigitNo);

void LCD_WriteNumber(int32_t Number);
uint8_t LCD_StoreSpecialCharacter(uint8_t *SpecialCharacter,uint8_t Location);

/* Error Detection Functions */
LCD_ErrorStatus_t LCD_GetLastError(void);
void LCD_ClearError(void);

#endif /* LCD_Interface */
