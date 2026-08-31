/**
 * @file Atmega32Register.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief Memory-mapped register definitions for the ATmega32(L).
 * @version 0.2
 * @date 2026-08-28
 * @note Every address below was cross-checked against the official Atmel
 *       ATmega32(L) datasheet (doc 2503Q-AVR-02/11), "Register Summary"
 *       table, page 327-328. Do not edit an address without re-checking
 *       that table.
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

/*EXTI Phrepheral*/
#define MCUCR_Reg    *((volatile uint8_t*)0x55)
#define MCUCSR_Reg   *((volatile uint8_t*)0x54)
#define GICR_Reg     *((volatile uint8_t*)0x5B)
#define GIFR_Reg     *((volatile uint8_t*)0x5A)


/*ADC*/
#define ADMUX_Reg   *((volatile uint8_t*)0x27)
#define ADCSRA_Reg  *((volatile uint8_t*)0x26)
#define ADCH_Reg    *((volatile uint8_t*)0x25)
#define ADCL_Reg    *((volatile uint8_t*)0x24)
#define ADCData_Reg *((volatile uint16_t*)0x24)
#define SFIOR_Reg   *((volatile uint8_t*)0x50)

/*Analog Comparator*/
#define ACSR_Reg    *((volatile uint8_t*)0x28)

/*DIO-GroupA*/
#define DDRA_Reg  *((volatile uint8_t*)0x3A)
#define PORTA_Reg *((volatile uint8_t*)0x3B)
#define PINA_Reg  *((volatile uint8_t*)0x39)


/*DIO-GroupB*/
#define DDRB_Reg  *((volatile uint8_t*)0x37)
#define PORTB_Reg *((volatile uint8_t*)0x38)
#define PINB_Reg  *((volatile uint8_t*)0x36)

/*DIO-GroupC*/
#define DDRC_Reg  *((volatile uint8_t*)0x34)
#define PORTC_Reg *((volatile uint8_t*)0x35)
#define PINC_Reg  *((volatile uint8_t*)0x33)

/*DIO-GroupD*/
#define DDRD_Reg  *((volatile uint8_t*)0x31)
#define PORTD_Reg *((volatile uint8_t*)0x32)
#define PIND_Reg  *((volatile uint8_t*)0x30)



/*Timers*/
#define TIMSK_Reg   *((volatile uint8_t*)0x59)
#define TIFR_Reg    *((volatile uint8_t*)0x58)
#define TCCR0_Reg   *((volatile uint8_t*)0x53)
#define TCNT0_Reg   *((volatile uint8_t*)0x52)
#define OCR0_Reg    *((volatile uint8_t*)0x5C)

#define TCCR2_Reg   *((volatile uint8_t*)0x45)
#define TCNT2_Reg   *((volatile uint8_t*)0x44)
#define OCR2_Reg    *((volatile uint8_t*)0x43)
#define ASSR_Reg    *((volatile uint8_t*)0x42)

/* NOTE: fixed a typo here -- these were declared "voltile" (missing the
 * 'a') in the previous version, which does not compile: "voltile" is not
 * a recognized keyword, so every line below would have failed to build
 * the moment any Timer1 code referenced these registers.
 */
#define TCCR1A_Reg   *((volatile uint8_t*)0x4F)
#define TCCR1B_Reg   *((volatile uint8_t*)0x4E)

#define TCNT1_Reg    *((volatile uint16_t*)0x4C)
#define TCNT1L_Reg   *((volatile uint8_t*)0x4C)
#define TCNT1H_Reg   *((volatile uint8_t*)0x4D)

#define OCR1A_Reg    *((volatile uint16_t*)0x4A)
#define OCR1AL_Reg   *((volatile uint8_t*)0x4A)
#define OCR1AH_Reg   *((volatile uint8_t*)0x4B)

#define OCR1B_Reg    *((volatile uint16_t*)0x48)
#define OCR1BL_Reg   *((volatile uint8_t*)0x48)
#define OCR1BH_Reg   *((volatile uint8_t*)0x49)

#define ICR1_Reg     *((volatile uint16_t*)0x46)
#define ICR1L_Reg    *((volatile uint8_t*)0x46)
#define ICR1H_Reg    *((volatile uint8_t*)0x47)

/*Watchdog Timer*/
#define WDTCR_Reg   *((volatile uint8_t*)0x41)

/*USART*/
#define UDR_Reg     *((volatile uint8_t*)0x2C)
#define UCSRA_Reg   *((volatile uint8_t*)0x2B)
#define UCSRB_Reg   *((volatile uint8_t*)0x2A)
/* UCSRC shares its I/O address with UBRRH -- selected by the URSEL bit
 * (bit7) on write. Both macros point at the same address on purpose.
 */
#define UCSRC_Reg   *((volatile uint8_t*)0x40)
#define UBRRH_Reg   *((volatile uint8_t*)0x40)
#define UBRRL_Reg   *((volatile uint8_t*)0x29)

/*EEPROM*/
#define EEARH_Reg   *((volatile uint8_t*)0x3F)
#define EEARL_Reg   *((volatile uint8_t*)0x3E)
#define EEAR_Reg    *((volatile uint16_t*)0x3E)
#define EEDR_Reg    *((volatile uint8_t*)0x3D)
#define EECR_Reg    *((volatile uint8_t*)0x3C)

/*SPI*/
#define SPDR_Reg    *((volatile uint8_t*)0x2F)
#define SPSR_Reg    *((volatile uint8_t*)0x2E)
#define SPCR_Reg    *((volatile uint8_t*)0x2D)

/*TWI (I2C)*/
#define TWDR_Reg    *((volatile uint8_t*)0x23)
#define TWAR_Reg    *((volatile uint8_t*)0x22)
#define TWSR_Reg    *((volatile uint8_t*)0x21)
#define TWBR_Reg    *((volatile uint8_t*)0x20)
#define TWCR_Reg    *((volatile uint8_t*)0x56)

/*Boot Loader / SPM*/
#define SPMCR_Reg   *((volatile uint8_t*)0x57)

/*Oscillator Calibration*/
#define OSCCAL_Reg  *((volatile uint8_t*)0x51)

#endif /*_MCAL_ATMEGA32REGISTER_H*/
