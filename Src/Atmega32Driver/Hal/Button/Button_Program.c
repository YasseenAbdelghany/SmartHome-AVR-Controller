#include "Button_Interface.h"

void Btn_Init(uint8_t ButtonGroup,uint8_t ButtonPin,uint8_t Connection)
{
    DIO_DirectionSelectforPin(ButtonGroup,ButtonPin,DIO_Inputfor1Pin);

    if(Connection==Button_InternalPullUp)
    {
        DIO_WritePin(ButtonGroup,ButtonPin,DIO_Highfor1Pin);
    }
    else if(Connection==Button_ExternalPullUp || Connection==Button_ExternalPullDown)
    {
        DIO_WritePin(ButtonGroup,ButtonPin,DIO_Lowfor1Pin);
    }
    else
    {
        // Error
    }
}

uint8_t Btn_ReadState(uint8_t ButtonGroup,uint8_t ButtonPin,uint8_t Connection)
{
    uint8_t ButtonState=0xFF;

    if(Connection==Button_InternalPullUp||
       Connection==Button_ExternalPullUp||
       Connection==Button_ExternalPullDown)
    {
        DIO_ReadPin(ButtonGroup,ButtonPin,&ButtonState);
    }
    else
    {
        // Error
    }

    return ButtonState;
}