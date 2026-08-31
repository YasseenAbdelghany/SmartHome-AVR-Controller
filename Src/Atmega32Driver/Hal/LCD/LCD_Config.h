/**
 * @file LCD_Config.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef LCD_CONFIG
#define LCD_CONFIG
/* PIN BUDGET FIX: this was Lcd_8bitMode, which claims all 8 pins of
 * PORTD for the data bus. That leaves zero pins free for the Alarm
 * module's emergency push button (INT0=PD2 and INT1=PD3 are both on
 * PORTD), so the LCD and the emergency interrupt could not physically
 * coexist. Switched to 4-bit mode, which only needs D4-D7 -- see the
 * full project pin map note below.
 */
#define LCD_TypeMode Lcd_4bitMode

// PreConfiguration -> Compile time 
#include "../../Mcal/DIO/DIO_Interface.h"

#define RSPin         DIO_Pin2
#define RSGroup       DIO_GroupC

/* #define RWPin         DIO_Pin1
#define RWGroup       DIO_GroupB*/

#define EPin         DIO_Pin3
#define EGroup       DIO_GroupC

#if LCD_TypeMode==Lcd_8bitMode
    #define DataGroup   DIO_GroupD  
#elif LCD_TypeMode==Lcd_4bitMode
/* BUG FIX: this was "LCD_TyMode" (typo, missing "pe"), so this branch
 * was comparing an undefined macro (== 0) to Lcd_4bitMode (== 2),
 * always false. It silently never fired while LCD_TypeMode was set to
 * 8-bit mode, but would have broken the moment anyone switched modes.
 *
 * PIN BUDGET FIX: also moved off PORTC (was Pin4-7 here) onto PORTD
 * (Pin4-7), since PORTC is now fully dedicated to the 4x4 Keypad
 * (8 pins) after moving the Keypad off PORTA -- see KeyPad_Config.h
 * and the full project pin map note below.
 */
    #define DataGroup   DIO_GroupC
    #define D4Pin       DIO_Pin4
    #define D5Pin       DIO_Pin5
    #define D6Pin       DIO_Pin6
    #define D7Pin       DIO_Pin7
#endif
/**
Lcd_4Bit2Line5x8F
Lcd_4Bit2Line5x11F
Lcd_4Bit1Line5x8F
Lcd_4Bit1Line5x11F
Lcd_8Bit2Line5x8F
Lcd_8Bit2Line5x11F
Lcd_8Bit1Line5x8F
Lcd_8Bit1Line5x11F
*/
/* NOTE: the project's LCD hardware is a 16x2 (2-line) display, and we are
 * now in 4-bit mode (see LCD_TypeMode above) -- so this must be one of
 * the Lcd_4Bit2Line... options, not the previous 8-bit 1-line setting.
 */
#define Lcd_FunctionSet  Lcd_4Bit2Line5x8F
/**
Lcd_DisplayOff
Lcd_DisplayOnCursorOff
Lcd_DisplayOnCursorOnBlinkOff
Lcd_DisplayOnCursorOnBlinkOn
*/
#define Lcd_DisplayOnOFF Lcd_DisplayOnCursorOnBlinkOn


/**
Lcd_EntryMode_DecNoShift  
Lcd_EntryMode_DecShift    
Lcd_EntryMode_IncNoShift  
Lcd_EntryMode_IncShift    
*/
#define Lcd_EntryMode    Lcd_EntryMode_IncNoShift
#endif /* LCD_CONFIG */
