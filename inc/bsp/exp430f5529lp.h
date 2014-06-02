
#ifndef __BSP_H
#define __BSP_H

#include <msp430.h>
#include "misc.h"


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
	
		.XLED_PORT_DIR =	(addr)PADIR_,
		.XLED_PORT_OUT =	(addr)PAOUT_,
	
		.TXLED =	BIT0,
		.RXLED =	BIT0,
	
// 		.rx_isr =	_PERIP_UART0_RX_ISR

		.uart_XD_enable = (void *)&uart_XD_enable,
		.uart_TX_wait = (void *)&uart_TX_wait
		
		
	
	},
	{
		.XD_PORT_SEL =	(addr)_PERIP_UART1_XD_PORT_SEL_ADDR,
		.XD_PORT_SEL2 =	(addr)_PERIP_UART1_XD_PORT_SEL2_ADDR,
		
		.TXD =	_PERIP_UART1_TXD,
		.RXD =	_PERIP_UART1_RXD,
		
		.CTL0 =	(addr)_PERIP_UART1_CTL0_ADDR,
		.CTL1 =	(addr)_PERIP_UART1_CTL1,
		.BR0 =	(addr)_PERIP_UART1_BR0,
		.BR1 =	(addr)_PERIP_UART1_BR1,
		.MCTL =	(addr)_PERIP_UART1_MCTL,
		
		.IE =	(addr)_PERIP_UART1_IE_ADDR,
		.IFG =	(addr)_PERIP_UART1_IFG_ADDR,
		
		.RXIE =	_PERIP_UART1_RXIE,
		.TXIFG =	_PERIP_UART1_TXIFG,
		.RXIFG =	_PERIP_UART1_RXIFG,
		
		.TXBUF =	(addr)_PERIP_UART1_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_UART1_RXBUF_ADDR,
	
		.ISR_vector =	_PERIP_UART1_ISR_VECTOR,
	
		.XLED_PORT_DIR =	(addr)(PBDIR_+1),
		.XLED_PORT_OUT =	(addr)(PBOUT_+1),
	
		.TXLED =	BIT7,
		.RXLED =	BIT7,
	
// 		.rx_isr =	_PERIP_UART1_RX_ISR

		.uart_XD_enable = (void *)&uart_XD_enable,
		.uart_TX_wait = (void *)&uart_TX_wait
		
		
	
	}
};

static uart_handle UART0 = &UART_TABLE[0];
static uart_handle UART1 = &UART_TABLE[1];



// #define PWM_CNT _PERIP_PWM_CNT
// 
// static PWM_OBJ PWM_TABLE[]={
// 	
// 	{
// 		.PORT_SEL = (addr)_PERIP_PWM0_PORT_SEL_ADDR,
// 		.PORT_SEL2 = (addr)_PERIP_PWM0_PORT_SEL2_ADDR,
// 		.PORT_DIR = (addr)_PERIP_PWM0_PORT_DIR_ADDR,
// 		
// 		.OUT0 = _PERIP_PWM0_OUT0,
// 		//.OUTs = _PERIP_PWM0_OUTs,
// 
// 		.CTL = (addr16)_PERIP_PWM0_CTL, 
// 		.CCTL = { (addr16)_PERIP_PWM0_CCTL0,
// 			(addr16)_PERIP_PWM0_CCTL1,
// 			(addr16)_PERIP_PWM0_CCTL2
// 		},
// 		
// 		.CCR = { (addr16)_PERIP_PWM0_CCR0,
// 			(addr16)_PERIP_PWM0_CCR1,
// 			(addr16)_PERIP_PWM0_CCR2
// 		}
// 	
// 	}
// };
// 
// static PWM_HANDLE PWM0 = &PWM_TABLE[0];

#endif
