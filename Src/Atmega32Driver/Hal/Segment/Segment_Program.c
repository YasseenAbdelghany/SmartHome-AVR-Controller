/**
 * @file Segment_Program.c
 * @author Team1
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "Segment_Interface.h"
/*
    Cathode
    h g f e d c b a 
    7 6 5 4 3 2 1 0 
*/
static uint8_t SSD_NumberPatterns[10] =
{
    0x3FU, /* 0 */
    0x06U, /* 1 */
    0x5BU, /* 2 */
    0x4FU, /* 3 */
    0x66U, /* 4 */
    0x6DU, /* 5 */
    0x7DU, /* 6 */
    0x07U, /* 7 */
    0x7FU, /* 8 */
    0x6FU  /* 9 */
};

void SSD_Init(uint8_t SSDGroup)
{
    /* ASSUMPTION: DIO_DirectionSelectforGroup(Group,Direction) and
     * DIO_Outputfor8Pins exist in your DIO_Interface.h as the whole-port
     * counterparts of DIO_DirectionSelectforPin / DIO_Outputfor1Pin.
     */
    DIO_DirectionSelectforGroup(SSDGroup, DIO_Outputfor1Group);
}

void SSD_DisplayNumber(uint8_t SSDGroup, uint8_t SSDType, uint8_t Number)
{
    uint8_t LocalPattern;

    if (Number <= Segment_MaxNumber)
    {
        LocalPattern = SSD_NumberPatterns[Number];

        if (SSDType == SSD_Anode)
        {
            /* Common-Anode: segments are active LOW -> invert the pattern */
            LocalPattern = (uint8_t)(~LocalPattern);
        }
        else
        {
            /* Common-Cathode: segments are active HIGH, pattern used as-is */
        }

        /* ASSUMPTION: DIO_WriteGroup(Group,Value) exists in your
         * DIO_Interface.h as the whole-port counterpart of DIO_WritePin.
         */
        DIO_WriteGroup(SSDGroup, LocalPattern);
    }
    else
    {
        /* Invalid digit (>9): no action (defensive branch) */
    }
}

void SSD_Off(uint8_t SSDGroup, uint8_t SSDType)
{
    if (SSDType == SSD_Anode)
    {
        DIO_WriteGroup(SSDGroup, DIO_Highfor1Group); /* all segments off (active LOW)  */
    }
    else
    {
        DIO_WriteGroup(SSDGroup, DIO_Lowfor1Group); /* all segments off (active HIGH) */
    }
}
