/**
 * @file T0_Private.h
 * @brief Timer/Counter0 private bit positions and register masks.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note All bit positions verified against the ATmega32(L) datasheet,
 *       TCCR0 = FOC0(7) WGM00(6) COM01(5) COM00(4) WGM01(3) CS02(2) CS01(1) CS00(0)
 *       TIMSK (Timer0 bits) = OCIE0(1) TOIE0(0)
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef T0_PRIVATE
#define T0_PRIVATE

#include <stdint.h>

typedef enum
{
    Bit_T0_CS00,
    Bit_T0_CS01,
    Bit_T0_CS02,
    Bit_T0_WGM01,
    Bit_T0_COM00,
    Bit_T0_COM01,
    Bit_T0_WGM00,
    Bit_T0_FOC0,
}T0_TCCR0Bit_t;

typedef enum
{
    Bit_T0_TOIE0,
    Bit_T0_OCIE0,
}T0_TIMSKBit_t;

/* Clock Select (CS02:CS00) -- written directly to TCCR0 bits 2:0 */
typedef enum
{
    T0_NoClock       = 0x00,
    T0_Prescaler1    = 0x01,
    T0_Prescaler8    = 0x02,
    T0_Prescaler64   = 0x03,
    T0_Prescaler256  = 0x04,
    T0_Prescaler1024 = 0x05,
    T0_ExtClkFalling = 0x06,
    T0_ExtClkRising  = 0x07,
}T0_ClockSelect_t;

/* Waveform Generation Mode. WGM01 (bit3) and WGM00 (bit6) are NOT
 * contiguous in TCCR0, so these values are pre-combined and split back
 * out onto the correct bits inside T0_Init() -- do not OR these directly
 * onto TCCR0 without masking first.
 */
typedef enum
{
    T0_Normal          = 0x00, /* WGM01=0 WGM00=0 */
    T0_PhaseCorrectPWM = 0x40, /* WGM01=0 WGM00=1 */
    T0_CTC             = 0x08, /* WGM01=1 WGM00=0 */
    T0_FastPWM         = 0x48, /* WGM01=1 WGM00=1 */
}T0_Mode_t;

/* Compare Output Mode for OC0 (COM01:COM00), bits 5:4 -- only meaningful
 * in one of the PWM modes above.
 */
typedef enum
{
    T0_OC0_Disconnected = 0x00,
    T0_OC0_Toggle       = 0x10,
    T0_OC0_NonInverting = 0x20,
    T0_OC0_Inverting    = 0x30,
}T0_OutputCompareMode_t;

typedef enum
{
    T0_InterruptDisable,
    T0_InterruptEnable,
}T0_InterruptState_t;

typedef struct
{
    T0_ClockSelect_t       Prescaler;
    T0_Mode_t               Mode;
    T0_OutputCompareMode_t OC0Mode;
    T0_InterruptState_t     OVFInterrupt;
    T0_InterruptState_t     CompInterrupt;
    uint8_t                  CompareValue; /* preloaded into OCR0 */
}T0_Config_t;

#define TCCR0_ClockMask 0x07U
#define TCCR0_ModeMask  0x48U /* bits 6 and 3 (WGM00, WGM01) -- non-contiguous, mask still valid */
#define TCCR0_ComMask   0x30U

#endif /* T0_PRIVATE */
