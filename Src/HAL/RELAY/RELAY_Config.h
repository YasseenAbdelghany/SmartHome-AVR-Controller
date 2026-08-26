/**
 * @file RELAY_Config.h
 * @author Soha Hossam
 * @brief Pin mapping for every relay channel driven by this module.
 * @version 0.1
 * @date 2026-08-25
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _RELAY_CONFIG_H
#define _RELAY_CONFIG_H

/* README "ATmega32 Pin Assignment" table: PA3 = Relay (Fan/AC), PA4 = Relay (Door Lock) */
#define RELAY_FAN_GROUP         DIO_GroupA
#define RELAY_FAN_PIN           DIO_Pin3

#define RELAY_DOORLOCK_GROUP    DIO_GroupA
#define RELAY_DOORLOCK_PIN      DIO_Pin4

#endif /*_RELAY_CONFIG_H*/
