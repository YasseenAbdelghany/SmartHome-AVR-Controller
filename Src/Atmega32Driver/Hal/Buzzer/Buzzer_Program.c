/**
 * @file Buzzer_Program.c
 * @author Team1
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "Buzzer_Interface.h"

void Buzzer_Init(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    DIO_DirectionSelectforPin(BuzzerGroup, BuzzerPin, DIO_Outputfor1Pin);
    DIO_WritePin(BuzzerGroup, BuzzerPin, DIO_Lowfor1Pin);
}

void Buzzer_On(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    DIO_WritePin(BuzzerGroup, BuzzerPin, DIO_Highfor1Pin);
}

void Buzzer_Off(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    DIO_WritePin(BuzzerGroup, BuzzerPin, DIO_Lowfor1Pin);
}