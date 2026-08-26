/**
 * @file LED_Config.h
 * @author Soha Hossam
 * @brief Pin mapping for every LED channel driven by this module.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _LED_CONFIG_H
#define _LED_CONFIG_H

/* README "ATmega32 Pin Assignment" table: PA2 = LED (Room Lights Output) */
#define LED_ROOM_LIGHT_GROUP    DIO_GroupA
#define LED_ROOM_LIGHT_PIN      DIO_Pin2

#endif /*_LED_CONFIG_H*/
