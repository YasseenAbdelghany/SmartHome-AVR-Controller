/**
 * @file T2_Program.c
 * @author Team6
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "T2_Interface.h"
#include <stddef.h>

static void (*T2_OVFCallBack)(void)  = NULL;
static void (*T2_CompCallBack)(void) = NULL;

void T2_Init(const T2_Config_t *Config)
{
    if(Config!=NULL)
    {
        TCCR2_Reg = (uint8_t)((TCCR2_Reg & (uint8_t)~TCCR2_ModeMask) | (uint8_t)Config->Mode);
        TCCR2_Reg = (uint8_t)((TCCR2_Reg & (uint8_t)~TCCR2_ComMask) | (uint8_t)Config->OC2Mode);
        OCR2_Reg = Config->CompareValue;

        if(Config->OVFInterrupt==T2_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T2_TOIE2);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T2_TOIE2);
        }

        if(Config->CompInterrupt==T2_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T2_OCIE2);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T2_OCIE2);
        }

        TCCR2_Reg = (uint8_t)((TCCR2_Reg & (uint8_t)~TCCR2_ClockMask) | (uint8_t)Config->Prescaler);
    }
    else
    {
        // NULL config: nothing to do
    }
}

void T2_SetCompareValue(uint8_t Value)
{
    OCR2_Reg = Value;
}

uint8_t T2_GetCounterValue(void)
{
    return TCNT2_Reg;
}

void T2_SetCounterValue(uint8_t Value)
{
    TCNT2_Reg = Value;
}

void T2_SetOVFCallBack(void (*PF)(void))
{
    T2_OVFCallBack = PF;
}

void T2_SetCompareCallBack(void (*PF)(void))
{
    T2_CompCallBack = PF;
}

/*ISR*/
void __vector_4() /* Timer2 Compare Match */
{
    if(T2_CompCallBack!=NULL)
    {
        T2_CompCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}

void __vector_5() /* Timer2 Overflow */
{
    if(T2_OVFCallBack!=NULL)
    {
        T2_OVFCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
