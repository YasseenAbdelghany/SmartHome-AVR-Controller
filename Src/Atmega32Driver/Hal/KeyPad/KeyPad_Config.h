#ifndef KEYPAD_CONFIG
#define KEYPAD_CONFIG
#include "../../Mcal/DIO/DIO_Interface.h"



#define KPD_ROWS_NUM    4
#define KPD_COLS_NUM    4


#define KPD_R0Pin     DIO_Pin0
#define KPD_R0Group   DIO_GroupB

#define KPD_R1Pin     DIO_Pin1
#define KPD_R1Group   DIO_GroupB

#define KPD_R2Pin     DIO_Pin2
#define KPD_R2Group   DIO_GroupB

#define KPD_R3Pin     DIO_Pin3
#define KPD_R3Group   DIO_GroupB


#define KPD_C0Pin     DIO_Pin4
#define KPD_C0Group   DIO_GroupB

#define KPD_C1Pin     DIO_Pin5
#define KPD_C1Group   DIO_GroupB

#define KPD_C2Pin     DIO_Pin6
#define KPD_C2Group   DIO_GroupB

#define KPD_C3Pin     DIO_Pin7
#define KPD_C3Group   DIO_GroupB



#define KPD_ButtonValue { \
    {'7', '8', '9', '/'}, \
    {'4', '5', '6', '*'}, \
    {'1', '2', '3', '-'}, \
    {'C', '0', '=', '+'}  \
}
#endif /* KEYPAD_CONFIG */
