/**
 * @file T0_Program.c
 * @author Team1
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "T0_Interface.h"
#include <stddef.h>

static void (*T0_OVFCallBack)(void)  = NULL;
static void (*T0_CompCallBack)(void) = NULL;

void T0_Init(const T0_Config_t *Config)
{
    if(Config!=NULL)
    {
        /* 1- Waveform Generation Mode (non-contiguous WGM00/WGM01 bits) */
        TCCR0_Reg = (uint8_t)((TCCR0_Reg & (uint8_t)~TCCR0_ModeMask) | (uint8_t)Config->Mode);
        /* 2- Compare Output Mode for OC0 */
        TCCR0_Reg = (uint8_t)((TCCR0_Reg & (uint8_t)~TCCR0_ComMask) | (uint8_t)Config->OC0Mode);
        /* 3- Preload the compare value before the clock starts ticking */
        OCR0_Reg = Config->CompareValue;
        /* 4- Overflow interrupt enable */
        if(Config->OVFInterrupt==T0_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T0_TOIE0);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T0_TOIE0);
        }
        /* 5- Compare Match interrupt enable */
        if(Config->CompInterrupt==T0_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T0_OCIE0);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T0_OCIE0);
        }
        /* 6- Clock Select (also starts the timer running) */
        TCCR0_Reg = (uint8_t)((TCCR0_Reg & (uint8_t)~TCCR0_ClockMask) | (uint8_t)Config->Prescaler);
    }
    else
    {
        // NULL config: nothing to do
    }
}

void T0_SetCompareValue(uint8_t Value)
{
    OCR0_Reg = Value;
}

uint8_t T0_GetCounterValue(void)
{
    return TCNT0_Reg;
}

void T0_SetCounterValue(uint8_t Value)
{
    TCNT0_Reg = Value;
}

void T0_SetOVFCallBack(void (*PF)(void))
{
    T0_OVFCallBack = PF;
}

void T0_SetCompareCallBack(void (*PF)(void))
{
    T0_CompCallBack = PF;
}

/*ISR*/
void __vector_10() /* Timer0 Compare Match */
{
    if(T0_CompCallBack!=NULL)
    {
        T0_CompCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}

void __vector_11() /* Timer0 Overflow */
{
    if(T0_OVFCallBack!=NULL)
    {
        T0_OVFCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
