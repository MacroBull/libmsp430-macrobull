

#ifndef __UART_H
#define __UART_H

//#define _ENABLE_USCI_UART_RX_IP

#include <msp430.h>
#include <stdint.h>
#include "misc.h"
#include "hw_obj.h"
#include "interrupt_proxy.h"

extern void USCI_UART_init(USCI_UART_info *this, uint32_t freq, uint32_t baud);
extern void USCI_UART_ISR_setter(USCI_UART_info *this, USCI_UART_RX_ISR rx_isr);

extern inline void USCI_UART_XD_enable(USCI_UART_info *this);
extern inline void USCI_UART_XLED_enable(USCI_UART_info *this);
extern inline void USCI_UART_TXLED_on(USCI_UART_info *this);
extern inline void USCI_UART_TXLED_off(USCI_UART_info *this);
extern inline void USCI_UART_RXLED_on(USCI_UART_info *this);
extern inline void USCI_UART_RXLED_off(USCI_UART_info *this);
extern inline void USCI_UART_TX_wait(USCI_UART_info *this);

extern inline void USCI_UART__putchar(USCI_UART_info *this, char c);


static VTable USCI_UART_info_VTable[] = {
	
	{ 0, 0, (VFuncPtr)USCI_UART_init },
	{ 0, 0, (VFuncPtr)USCI_UART_ISR_setter },
	
	{ 0, 0, (VFuncPtr)USCI_UART_XD_enable },
	{ 0, 0, (VFuncPtr)USCI_UART_XLED_enable },
	{ 0, 0, (VFuncPtr)USCI_UART_TXLED_on },
	{ 0, 0, (VFuncPtr)USCI_UART_TXLED_off },
	{ 0, 0, (VFuncPtr)USCI_UART_RXLED_on },
	{ 0, 0, (VFuncPtr)USCI_UART_RXLED_off },
	{ 0, 0, (VFuncPtr)USCI_UART_TX_wait },
	
	/*private */
	{ 0, 0, (VFuncPtr)USCI_UART__putchar }

};

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