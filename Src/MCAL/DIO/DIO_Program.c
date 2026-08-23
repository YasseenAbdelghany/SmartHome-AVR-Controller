#include "DIO_Interface.h"

/*API's*/
// Direction (input 0 Clear / output 1 Set  ) DDRA -- Optimized --
void DIO_DirectionSelectforPin(const uint8_t GroupName , const uint8_t PinNo,const uint8_t DirectionState)
{
    if ((GroupName <= DIO_GroupD) &&
        (PinNo <= DIO_Pin7))
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            if (DirectionState == DIO_Outputfor1Pin)
            {
                SetBit(DDRA_Reg, PinNo);
            }
            else if (DirectionState == DIO_Inputfor1Pin)
            {
                ClearBit(DDRA_Reg, PinNo);
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupB:
            if (DirectionState == DIO_Outputfor1Pin)
            {
                SetBit(DDRB_Reg, PinNo);
            }
            else if (DirectionState == DIO_Inputfor1Pin)
            {
                ClearBit(DDRB_Reg, PinNo);
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupC:
            if (DirectionState == DIO_Outputfor1Pin)
            {
                SetBit(DDRC_Reg, PinNo);
            }
            else if (DirectionState == DIO_Inputfor1Pin)
            {
                ClearBit(DDRC_Reg, PinNo);
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupD:
            if (DirectionState == DIO_Outputfor1Pin)
            {
                SetBit(DDRD_Reg, PinNo);
            }
            else if (DirectionState == DIO_Inputfor1Pin)
            {
                ClearBit(DDRD_Reg, PinNo);
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName or PinNo */
    }
}
void DIO_DirectionSelectforGroup(const uint8_t GroupName,  const uint8_t DirectionState)
{
    if (GroupName <= DIO_GroupD)
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            if (DirectionState == DIO_Outputfor1Group)
            {
                DDRA_Reg = 0xFF;
            }
            else if (DirectionState == DIO_Inputfor1Group)
            {
                DDRA_Reg = 0x00;
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupB:
            if (DirectionState == DIO_Outputfor1Group)
            {
                DDRB_Reg = 0xFF;
            }
            else if (DirectionState == DIO_Inputfor1Group)
            {
                DDRB_Reg = 0x00;
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupC:
            if (DirectionState == DIO_Outputfor1Group)
            {
                DDRC_Reg = 0xFF;
            }
            else if (DirectionState == DIO_Inputfor1Group)
            {
                DDRC_Reg = 0x00;
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        case DIO_GroupD:
            if (DirectionState == DIO_Outputfor1Group)
            {
                DDRD_Reg = 0xFF;
            }
            else if (DirectionState == DIO_Inputfor1Group)
            {
                DDRD_Reg = 0x00;
            }
            else
            {
                /* Invalid DirectionState */
            }
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName */
    }
}

// Output Value (low 0  Clear / High 1 Set  ) PORT
void DIO_WritePin(const uint8_t GroupName , const uint8_t PinNo,const uint8_t OutputValue)
{
    if ((GroupName <= DIO_GroupD) &&
        (PinNo <= DIO_Pin7))
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            if (OutputValue == DIO_Highfor1Pin)
            {
                SetBit(PORTA_Reg, PinNo);
            }
            else if (OutputValue == DIO_Lowfor1Pin)
            {
                ClearBit(PORTA_Reg, PinNo);
            }
            else
            {
                /* Invalid OutputValue */
            }
            break;

        case DIO_GroupB:
            if (OutputValue == DIO_Highfor1Pin)
            {
                SetBit(PORTB_Reg, PinNo);
            }
            else if (OutputValue == DIO_Lowfor1Pin)
            {
                ClearBit(PORTB_Reg, PinNo);
            }
            else
            {
                /* Invalid OutputValue */
            }
            break;

        case DIO_GroupC:
            if (OutputValue == DIO_Highfor1Pin)
            {
                SetBit(PORTC_Reg, PinNo);
            }
            else if (OutputValue == DIO_Lowfor1Pin)
            {
                ClearBit(PORTC_Reg, PinNo);
            }
            else
            {
                /* Invalid OutputValue */
            }
            break;

        case DIO_GroupD:
            if (OutputValue == DIO_Highfor1Pin)
            {
                SetBit(PORTD_Reg, PinNo);
            }
            else if (OutputValue == DIO_Lowfor1Pin)
            {
                ClearBit(PORTD_Reg, PinNo);
            }
            else
            {
                /* Invalid OutputValue */
            }
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName or PinNo */
    }
}
void DIO_WriteGroup(const uint8_t GroupName,  const uint8_t OutputValue)
{
    if (GroupName <= DIO_GroupD)
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            PORTA_Reg = OutputValue;
            break;

        case DIO_GroupB:
            PORTB_Reg = OutputValue;
            break;

        case DIO_GroupC:
            PORTC_Reg = OutputValue;
            break;

        case DIO_GroupD:
            PORTD_Reg = OutputValue;
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName */
    }
}

// InputState 
void DIO_ReadPin(const uint8_t GroupName , const uint8_t PinNo, uint8_t *InputState)
{
    if ((GroupName <= DIO_GroupD) &&
        (PinNo <= DIO_Pin7) &&
        (InputState != NULL))
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            *InputState = ReadBit(PINA_Reg, PinNo);
            break;

        case DIO_GroupB:
            *InputState = ReadBit(PINB_Reg, PinNo);
            break;

        case DIO_GroupC:
            *InputState = ReadBit(PINC_Reg, PinNo);
            break;

        case DIO_GroupD:
            *InputState = ReadBit(PIND_Reg, PinNo);
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid parameters */
    }
}
// uint8_t DIO_ReadPin(const uint8_t GroupName , const uint8_t PinNo);
void DIO_ReadGroup(const uint8_t GroupName , uint8_t *InputState)
{
    if ((GroupName <= DIO_GroupD) &&
        (InputState != NULL))
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            *InputState = PINA_Reg;
            break;

        case DIO_GroupB:
            *InputState = PINB_Reg;
            break;

        case DIO_GroupC:
            *InputState = PINC_Reg;
            break;

        case DIO_GroupD:
            *InputState = PIND_Reg;
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid parameters */
    }
}
// uint8_t DIO_ReadGroup(const uint8_t GroupName );


// Toggle 
void DIO_TogglePin(const uint8_t GroupName , const uint8_t PinNo)
{
    if ((GroupName <= DIO_GroupD) &&
        (PinNo <= DIO_Pin7))
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            ToggleBit(PORTA_Reg, PinNo);
            break;

        case DIO_GroupB:
            ToggleBit(PORTB_Reg, PinNo);
            break;

        case DIO_GroupC:
            ToggleBit(PORTC_Reg, PinNo);
            break;

        case DIO_GroupD:
            ToggleBit(PORTD_Reg, PinNo);
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName or PinNo */
    }
}
void DIO_ToggleGroup(const uint8_t GroupName )
{
    if (GroupName <= DIO_GroupD)
    {
        switch (GroupName)
        {
        case DIO_GroupA:
            PORTA_Reg = (uint8_t)~PORTA_Reg;
            break;

        case DIO_GroupB:
            PORTB_Reg = (uint8_t)~PORTB_Reg;
            break;

        case DIO_GroupC:
            PORTC_Reg = (uint8_t)~PORTC_Reg;
            break;

        case DIO_GroupD:
            PORTD_Reg = (uint8_t)~PORTD_Reg;
            break;

        default:
            /* Invalid GroupName */
            break;
        }
    }
    else
    {
        /* Invalid GroupName */
    }
}