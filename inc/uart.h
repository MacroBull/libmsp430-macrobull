

#ifndef __UART_H
#define __UART_H

//#define _ENABLE_USCI_UART_RX_IP

#include <msp430.h>
#include <stdint.h>
#include "misc.h"
#include "uart_obj.h"
// #include "interrupt_proxy.h"


extern inline void uart_XD_enable(uart_handle this);
extern inline void uart_XLED_enable(uart_handle this);
extern inline void uart_TXLED_on(uart_handle this);
extern inline void uart_TXLED_off(uart_handle this);
extern inline void uart_RXLED_on(uart_handle this);
extern inline void uart_RXLED_off(uart_handle this);

extern inline void uart_TX_wait(uart_handle this);
extern inline void uart_interrupt_enable(uart_handle this);
extern inline void uart_interrupt_disable(uart_handle this);

extern void uart_init(uart_handle this, uint32_t freq, uint32_t baud);

extern inline void uart__putchar(uart_handle this, char c);


/*MCTL references*/

#define UCBR0 0b00000000
#define UCBR1 0b00000010
#define UCBR2 0b00100010
#define UCBR3 0b00101010
#define UCBR4 0b10101010
#define UCBR5 0b10101110
#define UCBR6 0b11101110
#define UCBR7 0b11111110

static const uint8_t _UCBR[] = {
	UCBR0, UCBR1, UCBR2, UCBR3, UCBR4, UCBR5, UCBR6, UCBR7
};
	

#endif