
#ifndef __PIN_H
#define __PIN_H

#include <msp430.h>
#include "misc.h"
#include "hw_obj.h"

//////////////uart ////////////////////////
#define UART_CNT _PERIP_UART_CNT

#include "uart_obj.h"
#include "uart.h"

static uart_obj UART_TABLE[]={
	
	{
		.XD_PORT_SEL =	(addr)_PERIP_UART0_XD_PORT_SEL_ADDR,
		.XD_PORT_SEL2 =	(addr)_PERIP_UART0_XD_PORT_SEL2_ADDR,
		
		.TXD =	_PERIP_UART0_TXD,
		.RXD =	_PERIP_UART0_RXD,
		
		.CTL0 =	(addr)_PERIP_UART0_CTL0_ADDR,
		.CTL1 =	(addr)_PERIP_UART0_CTL1,
		.BR0 =	(addr)_PERIP_UART0_BR0,
		.BR1 =	(addr)_PERIP_UART0_BR1,
		.MCTL =	(addr)_PERIP_UART0_MCTL,
		
		.IE =	(addr)_PERIP_UART0_IE_ADDR,
		.IFG =	(addr)_PERIP_UART0_IFG_ADDR,
		
		.RXIE =	_PERIP_UART0_RXIE,
		.TXIFG =	_PERIP_UART0_TXIFG,
		.RXIFG =	_PERIP_UART0_RXIFG,
		
		.TXBUF =	(addr)_PERIP_UART0_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_UART0_RXBUF_ADDR,
		
		.ISR_vector =	_PERIP_UART0_ISR_VECTOR,
		
		.XLED_PORT_DIR =	(addr)_PERIP_UART0_XLED_PORT_DIR_ADDR,
		.XLED_PORT_OUT =	(addr)_PERIP_UART0_XLED_PORT_OUT_ADDR,
		
		.TXLED =	_PERIP_UART0_TXLED,
		.RXLED =	_PERIP_UART0_RXLED,
		
		// 		.rx_isr =	_PERIP_UART0_RX_ISR
		
		.uart_XD_enable = (void *)&uart_XD_enable,
		.uart_TX_wait = (void *)&uart_TX_wait
		
		
		
	}
};

static uart_handle UART0 = &UART_TABLE[0];
static uart_handle UART1 = &UART_TABLE[1];


/////////////////////PWM/////////////////////
#define PWM_CNT _PERIP_PWM_CNT

static PWM_OBJ PWM_TABLE[]={
	
	{
		.PORT_SEL = (addr)_PERIP_PWM0_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM0_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM0_PORT_DIR_ADDR,
		
		.OUT0 = _PERIP_PWM0_OUT0,
		//.OUTs = _PERIP_PWM0_OUTs,

		.CTL = (addr16)_PERIP_PWM0_CTL, 
		.CCTL = { (addr16)_PERIP_PWM0_CCTL0,
			(addr16)_PERIP_PWM0_CCTL1,
			(addr16)_PERIP_PWM0_CCTL2
		},
		
		.CCR = { (addr16)_PERIP_PWM0_CCR0,
			(addr16)_PERIP_PWM0_CCR1,
			(addr16)_PERIP_PWM0_CCR2
		}
	
	}
};

static PWM_HANDLE PWM0 = &PWM_TABLE[0];

#endif
