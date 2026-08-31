/**
 * @file T1_Private.h
 * @author Team6
 * @brief Timer/Counter1 (16-bit) private bit positions and register masks.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note Bit positions verified against the ATmega32(L) datasheet:
 *       TCCR1A = COM1A1(7) COM1A0(6) COM1B1(5) COM1B0(4) FOC1A(3) FOC1B(2) WGM11(1) WGM10(0)
 *       TCCR1B = ICNC1(7) ICES1(6) -(5) WGM13(4) WGM12(3) CS12(2) CS11(1) CS10(0)
 *       TIMSK (Timer1 bits) = TICIE1(6) OCIE1A(4) OCIE1B(3) TOIE1(2)
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T1_PRIVATE
#define T1_PRIVATE

#include <stdint.h>

/* Prescaler (CS12:CS10) -- written directly to TCCR1B bits 2:0 */
typedef enum
{
    T1_NoClock       = 0x00,
    T1_Prescaler1    = 0x01,
    T1_Prescaler8    = 0x02,
    T1_Prescaler64   = 0x03,
    T1_Prescaler256  = 0x04,
    T1_Prescaler1024 = 0x05,
    T1_ExtClkFalling = 0x06,
    T1_ExtClkRising  = 0x07,
}T1_ClockSelect_t;

/* Waveform Generation Mode -- practical subset used by this project
 * (Normal, CTC on OCR1A, and 8/9/10-bit Fast PWM for the fan-speed use
 * case). Stored as the raw 4-bit WGM13:WGM10 code; T1_Init() splits it
 * across TCCR1A bits1:0 and TCCR1B bits4:3, since they are not contiguous.
 */
typedef enum
{
    T1_Normal           = 0x00, /* 0000 */
    T1_PhaseCorrectPWM8 = 0x01, /* 0001 */
    T1_CTC_OCR1A        = 0x04, /* 0100 */
    T1_FastPWM8         = 0x05, /* 0101 */
    T1_FastPWM9         = 0x06, /* 0110 */
    T1_FastPWM10        = 0x07, /* 0111 */
}T1_Mode_t;

/* Compare Output Mode -- same 2-bit encoding used for both OC1A (bits7:6)
 * and OC1B (bits5:4); caller picks which channel(s) are actually wired.
 */
typedef enum
{
    T1_OC_Disconnected = 0x00,
    T1_OC_Toggle       = 0x01,
    T1_OC_NonInverting = 0x02,
    T1_OC_Inverting    = 0x03,
}T1_OutputCompareMode_t;

typedef enum
{
    T1_InterruptDisable,
    T1_InterruptEnable,
}T1_InterruptState_t;

typedef struct
{
    T1_ClockSelect_t       Prescaler;
    T1_Mode_t                Mode;
    T1_OutputCompareMode_t  OC1AMode;   /* T1_OC_Disconnected if OC1A/PD5 is not used */
    T1_OutputCompareMode_t  OC1BMode;   /* T1_OC_Disconnected if OC1B/PD4 is not used */
    T1_InterruptState_t      OVFInterrupt;
    T1_InterruptState_t      CompAInterrupt;
    T1_InterruptState_t      CompBInterrupt;
    uint16_t                  CompareA; /* preloaded into OCR1A */
    uint16_t                  CompareB; /* preloaded into OCR1B */
}T1_Config_t;

#define TCCR1B_ClockMask 0x07U
#define TCCR1A_WGMLowMask  0x03U /* WGM11:WGM10 -> TCCR1A bits1:0 */
#define TCCR1B_WGMHighMask 0x18U /* WGM13:WGM12 -> TCCR1B bits4:3 */
#define TCCR1A_ComAMask    0xC0U
#define TCCR1A_ComBMask    0x30U

/* TIMSK bit positions relevant to Timer1 */
#define Bit_T1_TOIE1  2U
#define Bit_T1_OCIE1B 3U
#define Bit_T1_OCIE1A 4U

#endif /* T1_PRIVATE */
