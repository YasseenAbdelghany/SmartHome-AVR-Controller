/**
 * @file LED_Interface.h
 * @author Soha Hossam
 * @brief Public API of the LED HAL driver (Room Lights indication/control).
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _LED_INTERFACE_H
#define _LED_INTERFACE_H
#include <stdint.h>
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LED_Private.h"
#include "LED_Config.h"

/*API's*/

/**
 * @brief Configures the direction of every LED pin and drives them OFF.
 *        Must be called once before any other LED_* API.
 * @return void
 */
void LED_Init(void);

/**
 * @brief Drives a single LED channel ON or OFF.
 * @param Channel LED to drive (see LED_Channel_t).
 * @param State   Requested state, LED_ON or LED_OFF.
 * @return void
 */
void LED_SetState(const LED_Channel_t Channel, const LED_State_t State);

/**
 * @brief Reads back the last commanded state of an LED channel.
 * @param Channel LED to query (see LED_Channel_t).
 * @return LED_State_t Cached state of the channel (LED_OFF if Channel is invalid).
 */
LED_State_t LED_GetState(const LED_Channel_t Channel);

#endif /*_LED_INTERFACE_H*/
