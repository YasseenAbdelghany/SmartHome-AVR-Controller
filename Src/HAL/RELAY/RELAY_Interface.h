/**
 * @file RELAY_Interface.h
 * @author Soha Hossam
 * @brief Public API of the RELAY HAL driver (Fan/AC + Door Lock heavy-load control).
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _RELAY_INTERFACE_H
#define _RELAY_INTERFACE_H
#include <stdint.h>
#include "../../MCAL/DIO/DIO_Interface.h"
#include "RELAY_Private.h"
#include "RELAY_Config.h"

/*API's*/

/**
 * @brief Configures the direction of every relay pin and drives them OFF (de-energized).
 *        Must be called once before any other RELAY_* API.
 * @return void
 */
void RELAY_Init(void);

/**
 * @brief Drives a single relay channel ON or OFF.
 * @param Channel Relay to drive (see RELAY_Channel_t).
 * @param State   Requested state, RELAY_ON or RELAY_OFF.
 * @return void
 */
void RELAY_SetState(const RELAY_Channel_t Channel, const RELAY_State_t State);

/**
 * @brief Reads back the last commanded state of a relay channel.
 * @param Channel Relay to query (see RELAY_Channel_t).
 * @return RELAY_State_t Cached state of the channel (RELAY_OFF if Channel is invalid).
 */
RELAY_State_t RELAY_GetState(const RELAY_Channel_t Channel);

#endif /*_RELAY_INTERFACE_H*/
