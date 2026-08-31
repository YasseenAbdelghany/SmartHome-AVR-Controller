/**
 * @file T1_Program.c
 * @author Team6
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "T1_Interface.h"
#include <stddef.h>

static void (*T1_OVFCallBack)(void)  = NULL;
static void (*T1_CompACallBack)(void) = NULL;
static void (*T1_CompBCallBack)(void) = NULL;

void T1_Init(const T1_Config_t *Config)
{
    if(Config!=NULL)
    {
        /* 1- Waveform Generation Mode, split across the two registers */
        TCCR1A_Reg = (uint8_t)((TCCR1A_Reg & (uint8_t)~TCCR1A_WGMLowMask)
                                | (uint8_t)((uint8_t)Config->Mode & TCCR1A_WGMLowMask));
        TCCR1B_Reg = (uint8_t)((TCCR1B_Reg & (uint8_t)~TCCR1B_WGMHighMask)
                                | (uint8_t)(((uint8_t)Config->Mode << 2) & TCCR1B_WGMHighMask));

        /* 2- Compare Output Mode for OC1A / OC1B, and matching pin setup */
        TCCR1A_Reg = (uint8_t)((TCCR1A_Reg & (uint8_t)~TCCR1A_ComAMask)
                                | (uint8_t)((uint8_t)Config->OC1AMode << 6));
        TCCR1A_Reg = (uint8_t)((TCCR1A_Reg & (uint8_t)~TCCR1A_ComBMask)
                                | (uint8_t)((uint8_t)Config->OC1BMode << 4));

        if(Config->OC1AMode!=T1_OC_Disconnected)
        {
            /* OC1A is PD5 */
            DIO_DirectionSelectforPin(DIO_GroupD,DIO_Pin5,DIO_Outputfor1Pin);
        }
        else
        {
            // OC1A not used: leave pin direction to whoever owns it
        }

        if(Config->OC1BMode!=T1_OC_Disconnected)
        {
            /* OC1B is PD4 */
            DIO_DirectionSelectforPin(DIO_GroupD,DIO_Pin4,DIO_Outputfor1Pin);
        }
        else
        {
            // OC1B not used: leave pin direction to whoever owns it
        }

        /* 3- Preload compare values before the clock starts ticking */
        OCR1A_Reg = Config->CompareA;
        OCR1B_Reg = Config->CompareB;

        /* 4- Interrupt enables */
        if(Config->OVFInterrupt==T1_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T1_TOIE1);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T1_TOIE1);
        }

        if(Config->CompAInterrupt==T1_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T1_OCIE1A);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T1_OCIE1A);
        }

        if(Config->CompBInterrupt==T1_InterruptEnable)
        {
            SetBit(TIMSK_Reg,Bit_T1_OCIE1B);
        }
        else
        {
            ClearBit(TIMSK_Reg,Bit_T1_OCIE1B);
        }

        /* 5- Clock Select (also starts the timer running) */
        TCCR1B_Reg = (uint8_t)((TCCR1B_Reg & (uint8_t)~TCCR1B_ClockMask) | (uint8_t)Config->Prescaler);
    }
    else
    {
        // NULL config: nothing to do
    }
}

void T1_SetCompareA(uint16_t Value)
{
    OCR1A_Reg = Value;
}

void T1_SetCompareB(uint16_t Value)
{
    OCR1B_Reg = Value;
}

uint16_t T1_GetCounterValue(void)
{
    return TCNT1_Reg;
}

void T1_SetCounterValue(uint16_t Value)
{
    TCNT1_Reg = Value;
}

void T1_SetOVFCallBack(void (*PF)(void))
{
    T1_OVFCallBack = PF;
}

void T1_SetCompACallBack(void (*PF)(void))
{
    T1_CompACallBack = PF;
}

void T1_SetCompBCallBack(void (*PF)(void))
{
    T1_CompBCallBack = PF;
}

/*ISR*/
void __vector_7() /* Timer1 Compare Match A */
{
    if(T1_CompACallBack!=NULL)
    {
        T1_CompACallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}

void __vector_8() /* Timer1 Compare Match B */
{
    if(T1_CompBCallBack!=NULL)
    {
        T1_CompBCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}

void __vector_9() /* Timer1 Overflow */
{
    if(T1_OVFCallBack!=NULL)
    {
        T1_OVFCallBack();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
