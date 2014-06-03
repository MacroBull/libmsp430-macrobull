

#ifndef __UART_OBJ_H
#define __UART_OBJ_H

#include <stdint.h>

#include "hw_obj.h"

// #include "uart.h"


typedef int (*uart_isr)(const uint16_t ISR_vector, char c);

typedef struct {
	
	const addr XD_PORT_SEL, XD_PORT_SEL2;
	const uint8_t TXD, RXD;
	
	const addr CTL0, CTL1, BR0, BR1, MCTL;
	const addr IE, IFG;
	const uint8_t RXIE, TXIFG, RXIFG;
	const addr TXBUF, RXBUF;
	
	ISR_VECTOR ISR_vector;
	
	addr XLED_PORT_DIR, XLED_PORT_OUT;
	uint8_t TXLED, RXLED;
	
	uart_isr rx_isr;
	
// 	_PERIP_CTL_FUNC uart_XD_enable;
// 	_PERIP_CTL_FUNC uart_TX_wait;
	
	
} uart_obj;

typedef uart_obj *uart_handle;


#endif
