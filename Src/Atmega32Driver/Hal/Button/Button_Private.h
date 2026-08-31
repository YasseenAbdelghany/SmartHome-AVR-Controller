/**
 * @file Button_Private.h
 * @author Team1
 * @brief 
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _BUTTON_PRIVATE_H
#define _BUTTON_PRIVATE_H

typedef enum
{
    Button_InternalPullUp,
    Button_ExternalPullUp,
    Button_ExternalPullDown,
}Button_ConnectionType_t;


typedef enum 
{
    PullDown_NotPressed=0,
    PullDown_Pressed=1,
    PullUp_Pressed =0,
    PullUp_NotPressed=1,
}Button_PressedState_t;

#endif /*_BUTTON_PRIVATE_H */