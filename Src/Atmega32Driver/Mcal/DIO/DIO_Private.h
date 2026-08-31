#ifndef _DIO_PRIVATE_H
#define _DIO_PRIVATE_H

typedef enum
{
    DIO_GroupA,
    DIO_GroupB,
    DIO_GroupC,
    DIO_GroupD,
}DIO_Groups_t;

typedef enum 
{
    DIO_Pin0,
    DIO_Pin1,
    DIO_Pin2,
    DIO_Pin3,
    DIO_Pin4,
    DIO_Pin5,
    DIO_Pin6,    
    DIO_Pin7,
}DIO_Pins_t;


typedef enum 
{
    DIO_Inputfor1Pin ,
    DIO_Outputfor1Pin,
    DIO_Inputfor1Group=0x00,
    DIO_Outputfor1Group=0xFF,
}DIO_DirectionState_t;


typedef enum 
{
    DIO_Lowfor1Pin ,
    DIO_Highfor1Pin,
    DIO_Lowfor1Group=0x00,
    DIO_Highfor1Group=0xFF,
}DIO_OutputValue_t;



#endif /*_DIO_PRIVATE_H*/