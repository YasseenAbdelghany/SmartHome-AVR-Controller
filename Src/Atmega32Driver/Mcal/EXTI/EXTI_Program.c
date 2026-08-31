#include "EXTI_Interface.h"
#include <stddef.h>

/* One callback slot per external interrupt line. NULL = nothing registered. */
static void (*EXTI_CallBack0)(void) = NULL;
static void (*EXTI_CallBack1)(void) = NULL;
static void (*EXTI_CallBack2)(void) = NULL;

/*API's*/
void EXTI_Init(uint8_t InterruptNumber,uint8_t SensControl)
{
    if(InterruptNumber==EXTI0) //MCUCR    ISC00 ISC01
    {
        if(SensControl== EXTI_LowLevel)
        {
            ClearBit(MCUCR_Reg,Bit_ISC00);
            ClearBit(MCUCR_Reg,Bit_ISC01);
        }
        else if (SensControl==EXTI_AnyLogic)
        {
            SetBit  (MCUCR_Reg,Bit_ISC00);
            ClearBit(MCUCR_Reg,Bit_ISC01);
        }
        else if (SensControl==EXTI_Falling)
        {
            ClearBit(MCUCR_Reg,Bit_ISC00);
            SetBit(MCUCR_Reg,Bit_ISC01);
        }
        else if (SensControl==EXTI_Rising)
        {
            SetBit(MCUCR_Reg,Bit_ISC00);
            SetBit(MCUCR_Reg,Bit_ISC01);
        }
        else
        {
            // Invalid SensControl: no action
        }
        // Enable for INT0 
        // GICR - INT0 -> 1 
        SetBit(GICR_Reg,Bit_INT0);
    }
    else if(InterruptNumber==EXTI1) //MCUCR    ISC10 ISC11 (same scheme as INT0)
    {
        if(SensControl== EXTI_LowLevel)
        {
            ClearBit(MCUCR_Reg,Bit_ISC10);
            ClearBit(MCUCR_Reg,Bit_ISC11);
        }
        else if (SensControl==EXTI_AnyLogic)
        {
            SetBit  (MCUCR_Reg,Bit_ISC10);
            ClearBit(MCUCR_Reg,Bit_ISC11);
        }
        else if (SensControl==EXTI_Falling)
        {
            ClearBit(MCUCR_Reg,Bit_ISC10);
            SetBit(MCUCR_Reg,Bit_ISC11);
        }
        else if (SensControl==EXTI_Rising)
        {
            SetBit(MCUCR_Reg,Bit_ISC10);
            SetBit(MCUCR_Reg,Bit_ISC11);
        }
        else
        {
            // Invalid SensControl: no action
        }
        // Enable for INT1
        // GICR - INT1 -> 1
        SetBit(GICR_Reg,Bit_INT1);
    }
    else if (InterruptNumber==EXTI2)
    {
        /* NOTE: INT2 is hardware-different from INT0/INT1 on the ATmega32
         * -- it only has a single sense-control bit (MCUCSR.ISC2), so it
         * can only be configured for Falling or Rising edge, NOT
         * Low-Level or Any-Logic-Change (the datasheet does not offer
         * those options for INT2). LowLevel/AnyLogic requests are
         * rejected here rather than silently mis-configuring the pin.
         */
        if (SensControl==EXTI_Falling)
        {
            ClearBit(MCUCSR_Reg,Bit_ISC2);
        }
        else if (SensControl==EXTI_Rising)
        {
            SetBit(MCUCSR_Reg,Bit_ISC2);
        }
        else
        {
            // EXTI_LowLevel / EXTI_AnyLogic are not supported by INT2's
            // single-bit sense control -- no action taken.
        }
        // Enable for INT2
        // GICR - INT2 -> 1
        SetBit(GICR_Reg,Bit_INT2);
    }
    else
    {
        // @todo return the Error Code Wrong InterruptNumber 
    }
}
void EXTI_Disable(uint8_t InterruptNumber)
{
    if(InterruptNumber==EXTI0)
    {
        ClearBit(GICR_Reg,Bit_INT0);
    }
    else if(InterruptNumber==EXTI1)
    {
        ClearBit(GICR_Reg,Bit_INT1);
    }
    else if(InterruptNumber==EXTI2)
    {
        ClearBit(GICR_Reg,Bit_INT2);
    }
    else
    {
        // Invalid InterruptNumber: no action
    }
}

/*Call-Back-Function*/
void EXTI_SetCallBack(uint8_t InterruptNumber, void (*Copy_pvCallBack)(void))
{
    if(InterruptNumber==EXTI0)
    {
        EXTI_CallBack0 = Copy_pvCallBack;
    }
    else if(InterruptNumber==EXTI1)
    {
        EXTI_CallBack1 = Copy_pvCallBack;
    }
    else if(InterruptNumber==EXTI2)
    {
        EXTI_CallBack2 = Copy_pvCallBack;
    }
    else
    {
        // Invalid InterruptNumber: no action
    }
}

/*ISR*/

/*EXTI0*/
void __vector_1()
{
    if(EXTI_CallBack0!=NULL)
    {
        EXTI_CallBack0();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
/*EXTI1*/
void __vector_2()
{
    if(EXTI_CallBack1!=NULL)
    {
        EXTI_CallBack1();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
/*EXTI2*/
void __vector_3()
{
    if(EXTI_CallBack2!=NULL)
    {
        EXTI_CallBack2();
    }
    else
    {
        // No callback registered, nothing to do.
    }
}
