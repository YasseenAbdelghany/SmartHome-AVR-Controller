/**
 * @file RELAY_Private.h
 * @author Soha Hossam
 * @brief Private types used internally/by the interface of the RELAY module.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _RELAY_PRIVATE_H
#define _RELAY_PRIVATE_H

typedef enum
{ /* One entry per physical relay wired to the board */
    RELAY_FAN,
    RELAY_DOOR_LOCK,
    RELAY_TOTAL_COUNT
} RELAY_Channel_t;

typedef enum
{
    RELAY_OFF,
    RELAY_ON
} RELAY_State_t;

#endif /*_RELAY_PRIVATE_H*/
