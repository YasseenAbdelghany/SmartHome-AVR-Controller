/**
 * @file KeyPad_Program.c
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief
 * @version 0.2
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "KeyPad_Interface.h"

static const uint8_t KPD_RowPins[KPD_ROWS_NUM]   = {KPD_R0Pin,KPD_R1Pin,KPD_R2Pin,KPD_R3Pin};
static const uint8_t KPD_RowGroups[KPD_ROWS_NUM] = {KPD_R0Group,KPD_R1Group,KPD_R2Group,KPD_R3Group};
static const uint8_t KPD_ColPins[KPD_COLS_NUM]   = {KPD_C0Pin,KPD_C1Pin,KPD_C2Pin,KPD_C3Pin};
static const uint8_t KPD_ColGroups[KPD_COLS_NUM] = {KPD_C0Group,KPD_C1Group,KPD_C2Group,KPD_C3Group};

static const uint8_t KPD_Keys[KPD_ROWS_NUM][KPD_COLS_NUM] = KPD_ButtonValue;

void KPD_Init()
{
    uint8_t RowIndex;
    uint8_t ColIndex;

    for(RowIndex=0U; RowIndex<KPD_ROWS_NUM; RowIndex++)
    {
        DIO_DirectionSelectforPin(KPD_RowGroups[RowIndex],KPD_RowPins[RowIndex],DIO_Outputfor1Pin);
        DIO_WritePin(KPD_RowGroups[RowIndex],KPD_RowPins[RowIndex],DIO_Highfor1Pin); /* idle High */
    }

    for(ColIndex=0U; ColIndex<KPD_COLS_NUM; ColIndex++)
    {
        DIO_DirectionSelectforPin(KPD_ColGroups[ColIndex],KPD_ColPins[ColIndex],DIO_Inputfor1Pin);
        DIO_WritePin(KPD_ColGroups[ColIndex],KPD_ColPins[ColIndex],DIO_Highfor1Pin); /* enable internal pull-up */
    }
}

uint8_t KPD_GetPressedKey()
{
    uint8_t RowIndex;
    uint8_t ColIndex;
    uint8_t ColState;
    uint8_t PressedKey = KPD_NotPressed;

    for(RowIndex=0U; RowIndex<KPD_ROWS_NUM; RowIndex++)
    {
        /* Drive only this row Low, all other rows stay High */
        DIO_WritePin(KPD_RowGroups[RowIndex],KPD_RowPins[RowIndex],DIO_Lowfor1Pin);

        for(ColIndex=0U; ColIndex<KPD_COLS_NUM; ColIndex++)
        {
            DIO_ReadPin(KPD_ColGroups[ColIndex],KPD_ColPins[ColIndex],&ColState);
            if(ColState==DIO_Lowfor1Pin)
            {
                /* This row/column intersection is pulled Low -> pressed */
                PressedKey = KPD_Keys[RowIndex][ColIndex];
            }
            else
            {
                /* Not this column */
            }
        }

        /* Restore this row to idle High before scanning the next one */
        DIO_WritePin(KPD_RowGroups[RowIndex],KPD_RowPins[RowIndex],DIO_Highfor1Pin);
    }

    return PressedKey;
}
