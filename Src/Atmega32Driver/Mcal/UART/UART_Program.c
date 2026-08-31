/**
 * @file UART_Program.c
 * @author Team6 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "UART_Interface.h"

static volatile uint8_t UART_au8TxBuffer[UART_TX_BUFFER_SIZE];
static volatile uint8_t UART_u8TxHead = 0U;
static volatile uint8_t UART_u8TxTail = 0U;

static volatile uint8_t UART_au8RxBuffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t UART_u8RxHead = 0U;
static volatile uint8_t UART_u8RxTail = 0U;

void UART_Init(const UART_Config_t *Config)
{
    uint16_t Local_u16UBRR;

    if(Config!=NULL)
    {
        Local_u16UBRR = (uint16_t)(((F_CPU)/(16UL*Config->BaudRate))-1UL);

        UBRRH_Reg = (uint8_t)(Local_u16UBRR>>8);
        UBRRL_Reg = (uint8_t)(Local_u16UBRR);

        /* URSEL=1 selects UCSRC (this address is shared with UBRRH) */
        UCSRC_Reg = (uint8_t)((1U<<Bit_UART_URSEL)
                             | ((uint8_t)Config->Parity  << Bit_UART_UPM0)
                             | ((uint8_t)Config->StopBits<< Bit_UART_USBS)
                             | ((uint8_t)Config->DataBits<< Bit_UART_UCSZ0));

        UCSRB_Reg = (uint8_t)((1U<<Bit_UART_RXEN)|(1U<<Bit_UART_TXEN)|(1U<<Bit_UART_RXCIE));
        /* UDRIE is intentionally left off here -- UART_SendByte() turns it
         * on only once there is actually data queued, otherwise the ISR
         * would fire continuously with nothing to send.
         */
    }
    else
    {
        // NULL config: nothing to do
    }
}

void UART_SendByte(uint8_t Data)
{
    uint8_t Local_u8NextHead = (uint8_t)((UART_u8TxHead+1U)&UART_TX_BUFFER_MASK);

    if(Local_u8NextHead!=UART_u8TxTail) /* buffer not full */
    {
        UART_au8TxBuffer[UART_u8TxHead] = Data;
        UART_u8TxHead = Local_u8NextHead;
        SetBit(UCSRB_Reg,Bit_UART_UDRIE); /* make sure the drain ISR is running */
    }
    else
    {
        // TX buffer full: byte dropped (a lost debug byte beats stalling
        // the real-time loop waiting for space)
    }
}

void UART_SendString(const uint8_t *String)
{
    if(String!=NULL)
    {
        while(*String!=(uint8_t)0U)
        {
            UART_SendByte(*String);
            String++;
        }
    }
    else
    {
        // NULL pointer: nothing to send
    }
}

uint8_t UART_IsDataAvailable(void)
{
    uint8_t Local_u8Result;

    if(UART_u8RxHead!=UART_u8RxTail)
    {
        Local_u8Result = 1U;
    }
    else
    {
        Local_u8Result = 0U;
    }

    return Local_u8Result;
}

uint8_t UART_ReceiveByte(void)
{
    uint8_t Local_u8Data = 0U;

    if(UART_u8RxHead!=UART_u8RxTail)
    {
        Local_u8Data = UART_au8RxBuffer[UART_u8RxTail];
        UART_u8RxTail = (uint8_t)((UART_u8RxTail+1U)&UART_RX_BUFFER_MASK);
    }
    else
    {
        // nothing available: return 0 without advancing the buffer
    }

    return Local_u8Data;
}

/*ISR*/

/**
 * @brief RX Complete -- pushes the received byte into the RX ring buffer.
 *        If the buffer is full, the incoming byte is dropped.
 */
void __vector_13()
{
    uint8_t Local_u8Data     = UDR_Reg;
    uint8_t Local_u8NextHead = (uint8_t)((UART_u8RxHead+1U)&UART_RX_BUFFER_MASK);

    if(Local_u8NextHead!=UART_u8RxTail)
    {
        UART_au8RxBuffer[UART_u8RxHead] = Local_u8Data;
        UART_u8RxHead = Local_u8NextHead;
    }
    else
    {
        // RX buffer full: byte dropped
    }
}

/**
 * @brief Data Register Empty -- drains one byte from the TX ring buffer
 *        per interrupt. Disables itself once the buffer is empty.
 */
void __vector_14()
{
    if(UART_u8TxTail!=UART_u8TxHead)
    {
        UDR_Reg = UART_au8TxBuffer[UART_u8TxTail];
        UART_u8TxTail = (uint8_t)((UART_u8TxTail+1U)&UART_TX_BUFFER_MASK);
    }
    else
    {
        ClearBit(UCSRB_Reg,Bit_UART_UDRIE); /* nothing left, stop interrupting */
    }
}
