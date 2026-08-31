/**
 * @file UART_Private.h
 * @author Team6 (Khaled)
 * @brief USART private bit positions and internal types.
 * @version 0.1
 * @date 2026-08-28
 *
 * @note Bit positions verified against the ATmega32(L) datasheet:
 *       UCSRA = RXC(7) TXC(6) UDRE(5) FE(4) DOR(3) PE(2) U2X(1) MPCM(0)
 *       UCSRB = RXCIE(7) TXCIE(6) UDRIE(5) RXEN(4) TXEN(3) UCSZ2(2) RXB8(1) TXB8(0)
 *       UCSRC = URSEL(7) UMSEL(6) UPM1(5) UPM0(4) USBS(3) UCSZ1(2) UCSZ0(1) UCPOL(0)
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef UART_PRIVATE
#define UART_PRIVATE

#include <stdint.h>

/* UCSRA bits */
#define Bit_UART_MPCM  0
#define Bit_UART_U2X   1
#define Bit_UART_PE    2
#define Bit_UART_DOR   3
#define Bit_UART_FE    4
#define Bit_UART_UDRE  5
#define Bit_UART_TXC   6
#define Bit_UART_RXC   7

/* UCSRB bits */
#define Bit_UART_TXB8  0
#define Bit_UART_RXB8  1
#define Bit_UART_UCSZ2 2
#define Bit_UART_TXEN  3
#define Bit_UART_RXEN  4
#define Bit_UART_UDRIE 5
#define Bit_UART_TXCIE 6
#define Bit_UART_RXCIE 7

/* UCSRC bits (write requires URSEL=1, since this address is shared with UBRRH) */
#define Bit_UART_UCPOL 0
#define Bit_UART_UCSZ0 1
#define Bit_UART_UCSZ1 2
#define Bit_UART_USBS  3
#define Bit_UART_UPM0  4
#define Bit_UART_UPM1  5
#define Bit_UART_UMSEL 6
#define Bit_UART_URSEL 7

typedef enum
{
    UART_5Bit,
    UART_6Bit,
    UART_7Bit,
    UART_8Bit,
}UART_DataBits_t;

typedef enum
{
    UART_1StopBit,
    UART_2StopBit,
}UART_StopBits_t;

typedef enum
{
    UART_ParityDisabled,
    UART_ParityEven=2,
    UART_ParityOdd=3,
}UART_Parity_t;

typedef struct
{
    uint32_t         BaudRate;
    UART_DataBits_t   DataBits;
    UART_StopBits_t   StopBits;
    UART_Parity_t     Parity;
}UART_Config_t;

/* TX/RX ring buffer sizes. MUST be a power of 2 so index wrap-around can
 * be done with a bitmask instead of a modulo (no hardware divider on AVR).
 */
#define UART_TX_BUFFER_SIZE 32U
#define UART_RX_BUFFER_SIZE 32U
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE-1U)
#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE-1U)

#endif /* UART_PRIVATE */
