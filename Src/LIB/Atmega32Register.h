/**
 * @file Atmega32Register.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _MCAL_ATMEGA32REGISTER_H
#define _MCAL_ATMEGA32REGISTER_H
#include <stdint.h>
/*IO- Memory Map Address*/

#define SREG_Reg *((volatile uint8_t*)0x5F)
/*Stack Pointer */
#define SPH_Reg *((volatile uint8_t*)0x5E)
#define SPL_Reg *((volatile uint8_t*)0x5D)
#define SP_Reg  *((volatile uint16_t*)0x5D)
/*------------------------------------------*/
#define OCRO_Reg *((volatile uint8_t *)0x5C)
#define GICR_Reg *((volatile uint8_t *)0x5B)
#define GIFR_Reg *((volatile uint8_t *)0x5A)
#define TIMSK_Reg *((volatile uint8_t *)0x59)
#define TIFR_Reg *((volatile uint8_t *)0x58)
#define SPMCR_Reg *((volatile uint8_t *)0x57)
#define TWCR_Reg *((volatile uint8_t *)0x56)
#define MCUCR_Reg *((volatile uint8_t *)0x55)
#define MCUCSR_Reg *((volatile uint8_t *)0x54)
#define TCCRO_Reg *((volatile uint8_t *)0x53)
#define TCNTO_Reg *((volatile uint8_t *)0x52)
#define OSCCAL_Reg *((volatile uint8_t *)0x52)
#define OCDR_Reg *((volatile uint8_t *)0x51)
#define SFIOR_Reg *((volatile uint8_t *)0x50)
#define TCCR1A_Reg *((volatile uint8_t *)0x4F)
#define TCCR1B_Reg *((volatile uint8_t *)0x4E)
#define TCNT1H_Reg *((volatile uint8_t *)0x4D)
#define TCNT1L_Reg *((volatile uint8_t *)0x4C)
#define OCR1AH_Reg *((volatile uint8_t *)0x4B)
#define OCR1AL_Reg *((volatile uint8_t *)0x4A)
#define OCR1BH_Reg *((volatile uint8_t *)0x49)
#define OCR1BL_Reg *((volatile uint8_t *)0x48)
#define ICR1H_Reg *((volatile uint8_t *)0x47)
#define ICR1L_Reg *((volatile uint8_t *)0x46)
#define TCCR2_Reg *((volatile uint8_t *)0x45)
#define TCNT2_Reg *((volatile uint8_t *)0x44)
#define OCR2_Reg *((volatile uint8_t *)0x43)
#define ASSR_Reg *((volatile uint8_t *)0x42)
#define WDTCR_Reg *((volatile uint8_t *)0x41)
#define UBRRH_Reg *((volatile uint8_t *)0x41)
#define UCSRC_Reg *((volatile uint8_t *)0x40)
#define EEARH_Reg *((volatile uint8_t *)0x3F)
#define EEARL_Reg *((volatile uint8_t *)0x3E)
#define EEDR_Reg *((volatile uint8_t *)0x3D)
#define EECR_Reg *((volatile uint8_t *)0x3C)
#define PORTA_Reg *((volatile uint8_t *)0x3B)
#define DDRA_Reg *((volatile uint8_t *)0x3A)
#define PINA_Reg *((volatile uint8_t *)0x39)
#define PORTB_Reg *((volatile uint8_t *)0x38)
#define DDRB_Reg *((volatile uint8_t *)0x37)
#define PINB_Reg *((volatile uint8_t *)0x36)
#define PORTC_Reg *((volatile uint8_t *)0x35)
#define DDRC_Reg *((volatile uint8_t *)0x34)
#define PINC_Reg *((volatile uint8_t *)0x33)
#define PORTD_Reg *((volatile uint8_t *)0x32)
#define DDRD_Reg *((volatile uint8_t *)0x31)
#define PIND_Reg *((volatile uint8_t *)0x30)
#define SPDR_Reg *((volatile uint8_t *)0x2F)
#define SPSR_Reg *((volatile uint8_t *)0x2E)
#define SPCR_Reg *((volatile uint8_t *)0x2D)
#define UDR_Reg *((volatile uint8_t *)0x2C)
#define UCSRA_Reg *((volatile uint8_t *)0x2B)
#define UCSRB_Reg *((volatile uint8_t *)0x2A)
#define UBRRL_Reg *((volatile uint8_t *)0x29)
#define ACSR_Reg *((volatile uint8_t *)0x28)
#define ADMUX_Reg *((volatile uint8_t *)0x27)
#define ADCSRA_Reg *((volatile uint8_t *)0x26)
#define ADCH_Reg *((volatile uint8_t *)0x25)
#define ADCL_Reg *((volatile uint8_t *)0x24)
#define TWDR_Reg *((volatile uint8_t *)0x23)
#define TWAR_Reg *((volatile uint8_t *)0x22)
#define TWSR_Reg *((volatile uint8_t *)0x21)
#define TWBR_Reg *((volatile uint8_t *)0x20)

#endif /*_MCAL_ATMEGA32REGISTER_H*/