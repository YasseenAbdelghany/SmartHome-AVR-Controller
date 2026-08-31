/**
 * @file SystemMap.h
 * @author Team4 -- Smart Home Controller
 * @brief Single source of truth for the whole team: EEPROM memory layout
 *        and pin assignments across all modules. Every APP-layer module
 *        includes this instead of hard-coding an address or duplicating
 *        a pin somewhere else in the codebase.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note EEPROM ADDRESSES (ATmega32 internal EEPROM, 1KB, 0x000-0x3FF):
 *   0x00-0x03  Authentication password (4 digits, 1 byte each)
 *   0x04       System Configuration: Temperature Threshold (1 byte)
 *   0x05-0x06  System Configuration: Light Threshold (uint16_t, 2 bytes)
 *   0x30       System Configuration: System Mode (Manual=0 / Auto=1)
 *   0x40       System Configuration: Alarm Enable (Disabled=0 / Enabled=1)
 *   0x50-0x8F  Event Logging: circular log region (64 bytes -- see
 *              EventLogging_Interface.h for the record format)
 *
 * @note PIN MAP (resolved to avoid conflicts -- see the two fixes below):
 *   PORT A: PA0=LM35(ADC0) PA1=LDR(ADC1) PA2=RoomLightLED PA3=FanRelay
 *           PA4=DoorRelay PA5=Buzzer PA6-7=spare
 *   PORT B: PB0=LCD_RS PB1=LCD_RW PB2=LCD_E PB3-7=spare
 *   PORT C: PC0-3=Keypad Rows  PC4-7=Keypad Columns
 *   PORT D: PD0=UART_RXD(peripheral) PD1=UART_TXD(peripheral)
 *           PD2=EmergencyButton(EXTI0) PD3=spare(EXTI1)
 *           PD4-7=LCD 4-bit data (D4-D7)
 *
 *   FIX 1: Keypad was originally on PA0-PA7 (KeyPad_Config.h), which
 *          collided with LM35/LDR also needing PA0/PA1 for ADC0/ADC1.
 *          Moved the whole keypad to PORT C.
 *   FIX 2: LCD was originally in 8-bit mode, claiming all 8 pins of
 *          PORT D -- leaving no room for the emergency button's external
 *          interrupt (INT0/INT1 are both on PORT D). Switched the LCD to
 *          4-bit mode (LCD_Config.h), which only needs D4-D7, freeing
 *          PD2/PD3 for EXTI.
 *
 * @note ASSUMPTION: the README's hardware table lists LM35+LDR+Buzzer+
 *       PushButton but no separate physical "flame/fire sensor". Fire
 *       detection is therefore implemented as the LM35 temperature
 *       crossing a high safety threshold (SystemMap_FireTempThreshold
 *       below), not a dedicated interrupt-driven sensor. If the team
 *       actually has a discrete flame sensor module, it should be wired
 *       to EXTI1 (PD3, currently spare) and Roaya's Alarm module updated
 *       to also trigger on that interrupt.
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef APP_SYSTEMMAP_H
#define APP_SYSTEMMAP_H

#include "../Mcal/DIO/DIO_Interface.h"

/* ---- EEPROM Map ---- */
#define SystemMap_EE_PasswordAddr        0x00U /* 4 bytes: 0x00-0x03 */
#define SystemMap_EE_PasswordLength      4U
#define SystemMap_EE_TempThresholdAddr   0x04U /* 1 byte              */
#define SystemMap_EE_LightThresholdAddr  0x05U /* 2 bytes: 0x05-0x06  */
#define SystemMap_EE_SystemModeAddr      0x30U /* 1 byte              */
#define SystemMap_EE_AlarmEnableAddr     0x40U /* 1 byte              */
#define SystemMap_EE_LogRegionStart      0x50U
#define SystemMap_EE_LogRegionEnd        0x90U /* exclusive           */

/* ---- Pin Map ---- */
#define SystemMap_LM35_Group      DIO_GroupA
#define SystemMap_LM35_ADCChannel 0U
#define SystemMap_LDR_Group       DIO_GroupA
#define SystemMap_LDR_ADCChannel  1U

#define SystemMap_RoomLight_Group DIO_GroupA
#define SystemMap_RoomLight_Pin   DIO_Pin2
#define SystemMap_RoomLight_ConnectionType LED_SourceConnection

#define SystemMap_FanRelay_Group  DIO_GroupA
#define SystemMap_FanRelay_Pin    DIO_Pin3
#define SystemMap_FanRelay_ConnectionType Relay_ActiveLow

#define SystemMap_DoorRelay_Group DIO_GroupA
#define SystemMap_DoorRelay_Pin   DIO_Pin4
#define SystemMap_DoorRelay_ConnectionType Relay_ActiveLow

#define SystemMap_Buzzer_Group    DIO_GroupA
#define SystemMap_Buzzer_Pin      DIO_Pin5

#define SystemMap_EmergencyBtn_Group DIO_GroupD
#define SystemMap_EmergencyBtn_Pin   DIO_Pin2 /* also EXTI0 */

/* Fire detection: no discrete sensor in the hardware table -- treated as
 * LM35 crossing a high safety threshold. See note above.
 */
#define SystemMap_FireTempThresholdC  50U

/* Default password used only on first boot / EEPROM blank state. */
#define SystemMap_DefaultPassword { '1','2','3','4' }

#endif /* APP_SYSTEMMAP_H */
