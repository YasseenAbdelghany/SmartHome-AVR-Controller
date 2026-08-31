/**
 * @file T2_Private.h
 * @author Team6
 * @brief Timer/Counter2 private bit positions and register masks.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note Bit positions verified against the ATmega32(L) datasheet:
 *       TCCR2 = FOC2(7) WGM20(6) COM21(5) COM20(4) WGM21(3) CS22(2) CS21(1) CS20(0)
 *       TIMSK (Timer2 bits) = OCIE2(7) TOIE2(6)
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T2_PRIVATE
#define T2_PRIVATE

#include <stdint.h>

typedef enum
{
    Bit_T2_TOIE2 = 6,
    Bit_T2_OCIE2 = 7,
}T2_TIMSKBit_t;

/* Clock Select (CS22:CS20) -- written directly to TCCR2 bits 2:0.
 * Timer2 has different prescaler taps than Timer0/1 (adds /32 and /128,
 * no external clock input) since it can run from the async oscillator.
 */
typedef enum
{
    T2_NoClock       = 0x00,
    T2_Prescaler1    = 0x01,
    T2_Prescaler8    = 0x02,
    T2_Prescaler32   = 0x03,
    T2_Prescaler64   = 0x04,
    T2_Prescaler128  = 0x05,
    T2_Prescaler256  = 0x06,
    T2_Prescaler1024 = 0x07,
}T2_ClockSelect_t;

/* Waveform Generation Mode. WGM21 (bit3) and WGM20 (bit6) are NOT
 * contiguous in TCCR2, matching Timer0's layout exactly.
 */
typedef enum
{
    T2_Normal          = 0x00, /* WGM21=0 WGM20=0 */
    T2_PhaseCorrectPWM = 0x40, /* WGM21=0 WGM20=1 */
    T2_CTC             = 0x08, /* WGM21=1 WGM20=0 */
    T2_FastPWM         = 0x48, /* WGM21=1 WGM20=1 */
}T2_Mode_t;

/* Compare Output Mode for OC2 (COM21:COM20), bits 5:4 */
typedef enum
{
    T2_OC2_Disconnected = 0x00,
    T2_OC2_Toggle       = 0x10,
    T2_OC2_NonInverting = 0x20,
    T2_OC2_Inverting    = 0x30,
}T2_OutputCompareMode_t;

typedef enum
{
    T2_InterruptDisable,
    T2_InterruptEnable,
}T2_InterruptState_t;

typedef struct
{
    T2_ClockSelect_t       Prescaler;
    T2_Mode_t                Mode;
    T2_OutputCompareMode_t  OC2Mode;
    T2_InterruptState_t      OVFInterrupt;
    T2_InterruptState_t      CompInterrupt;
    uint8_t                   CompareValue; /* preloaded into OCR2 */
}T2_Config_t;

#define TCCR2_ClockMask 0x07U
#define TCCR2_ModeMask  0x48U /* bits 6 and 3 (WGM20, WGM21) */
#define TCCR2_ComMask   0x30U

#endif /* T2_PRIVATE */
