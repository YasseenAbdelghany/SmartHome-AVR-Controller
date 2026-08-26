/**
 * @file LED_Private.h
 * @author Soha Hossam
 * @brief Private types used internally/by the interface of the LED module.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _LED_PRIVATE_H
#define _LED_PRIVATE_H

typedef enum
{ /* One entry per physical LED wired to the board */
    LED_ROOM_LIGHT,
    LED_TOTAL_COUNT
} LED_Channel_t;

typedef enum
{
    LED_OFF,
    LED_ON
} LED_State_t;

#endif /*_LED_PRIVATE_H*/
