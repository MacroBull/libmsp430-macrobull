
#ifndef __DEV_H
#define __DEV_H

#include <msp430.h>
#include "misc.h"
#include "hw_obj.h"

#if defined(_DEV_LAUNCHPAD) || defined(_DEV_EXP430G2) 

	static const char _USCI_UART_cnt=1;
	static USCI_UART_info _USCI_UART_table[]={
		
		{
			.XD_PORT_SEL = (addr)P1SEL_,
			.XD_PORT_SEL2 = (addr)P1SEL2_,
			
			.TXD = BIT2,
			.RXD = BIT1,
			
			.CTL0 = (addr)UCA0CTL0_,
			.CTL1 = (addr)UCA0CTL1_,
			.BR0 = (addr)UCA0BR0_,
			.BR1 = (addr)UCA0BR1_,
			.MCTL = (addr)UCA0MCTL_,
			
			.IE = (addr)IE2_,
			.IFG = (addr)IFG2_,
			
			.RXIE = UCA0RXIE,
			.TXIFG = UCA0TXIFG,
			.RXIFG = UCA0RXIFG,
			
			.TXBUF = (addr)UCA0TXBUF_,
			.RXBUF = (addr)UCA0RXBUF_,
			
			.ISR_vector = USCIAB0RX_VECTOR,
	
			.XLED_PORT_DIR = (addr)P1DIR_,
			.XLED_PORT_OUT = (addr)P1OUT_,
			
			.TXLED = BIT0,
			.RXLED = BIT6,
			
			.rx_isr = NULL,
			
		}
	};
	//#define _USCI_UART0 _USCI_UART_table[0]
	static USCI_UART_info *_USCI_UART0 = &_USCI_UART_table[0];
	
	
	static const char _USCI_I2C_cnt=1;
	static USCI_I2C_info _USCI_I2C_table[]={
		
		{
			.XD_PORT_SEL = (addr)P1SEL_,
			.XD_PORT_SEL2 = (addr)P1SEL2_,
			
			.SCL = BIT6,
			.SDA = BIT7,
			
			.CTL0 = (addr)UCB0CTL0_,
			.CTL1 = (addr)UCB0CTL1_,
			.BR0 = (addr)UCB0BR0_,
			.BR1 = (addr)UCB0BR1_,
			//.MCTL = (addr)UCB0MCTL_,
			
			.IE = (addr)IE2_,
			.IFG = (addr)IFG2_,
			.STAT = (addr)UCB0STAT_,
			
			.OA = (addr16)UCB0I2COA_,
			.SA = (addr16)UCB0I2CSA_,
			
			.RXIE = UCB0RXIE,
			.TXIFG = UCB0TXIFG,
			.RXIFG = UCB0RXIFG,
			
			.TXBUF = (addr)UCB0TXBUF_,
			.RXBUF = (addr)UCB0RXBUF_,
			
			.ISR_vector = USCIAB0RX_VECTOR,
	
			.XLED_PORT_DIR = (addr)P1DIR_,
			.XLED_PORT_OUT = (addr)P1OUT_,
			
			.XLED = BIT0,
			
			//.rx_isr = NULL,
			
		}
	};
	//#define _USCI_I2C0 _USCI_I2C_table[0]
	static USCI_I2C_info *_USCI_I2C0 = &_USCI_I2C_table[0];
	

	static const char _TA_PWM_cnt=1;
	static TA_PWM_info _TA_PWM_table[]={
		
		{
			.PORT_SEL = (addr)P1SEL_,
			.PORT_DIR = (addr)P1DIR_,
			
			.TA1 = 2,
			.TAs = 0x01,
	
			.CTL = (addr16)TACTL_, 
			.CCTL = { (addr16)CCTL0_,
				(addr16)CCTL1_,
				(addr16)CCTL2_
			},
			
			.CCR = { (addr16)CCR0_,
				(addr16)CCR1_,
				(addr16)CCR2_
			}
		
		}
	};
	
	static TA_PWM_info *_TA_PWM0 = &_TA_PWM_table[0];

#endif
	
#if defined(_DEV_EXP430F5529) 
	
	static const char _USCI_UART_cnt=2;
	static USCI_UART_info _USCI_UART_table[]={
		
		{
			.XD_PORT_SEL = (addr)PBSEL_,
			.XD_PORT_SEL2 = (addr)PBSEL_,
			
			.TXD = BIT3,
			.RXD = BIT4,
			
			.CTL0 = (addr)(UCA0CTLW0_+1),
			.CTL1 = (addr)UCA0CTLW0_,
			.BR0 = (addr)(UCA0BRW_),
			.BR1 = (addr)(UCA0BRW_+1),
			.MCTL = (addr)UCA0MCTL_,
			
			.IE = (addr)UCA0ICTL_,
			.IFG = (addr)(UCA0ICTL_+1),
			
			.RXIE = UCRXIE,
			.TXIFG = UCTXIFG,
			.RXIFG = UCRXIFG,
			
			.TXBUF = (addr)UCA0TXBUF_,
			.RXBUF = (addr)UCA0RXBUF_,
			
			.ISR_vector = USCI_A0_VECTOR,
	
			.XLED_PORT_DIR = (addr)PADIR_,
			.XLED_PORT_OUT = (addr)PAOUT_,
			
			.TXLED = BIT1,
			.RXLED = BIT2,
			
			.rx_isr = NULL,
			
		},
		{
			.XD_PORT_SEL = (addr)(PBSEL_+1),
			.XD_PORT_SEL2 = (addr)(PBSEL_+1),
			
			.TXD = BIT4,
			.RXD = BIT5,
			
			.CTL0 = (addr)(UCA1CTLW0_+1),
			.CTL1 = (addr)UCA1CTLW0_,
			.BR0 = (addr)(UCA1BRW_),
			.BR1 = (addr)(UCA1BRW_+1),
			.MCTL = (addr)UCA1MCTL_,
			
			.IE = (addr)UCA1ICTL_,
			.IFG = (addr)(UCA1ICTL_+1),
			
			.RXIE = UCRXIE,
			.TXIFG = UCTXIFG,
			.RXIFG = UCRXIFG,
			
			.TXBUF = (addr)UCA1TXBUF_,
			.RXBUF = (addr)UCA1RXBUF_,
			
			.ISR_vector = USCI_A1_VECTOR,
	
			.XLED_PORT_DIR = (addr)PADIR_,
			.XLED_PORT_OUT = (addr)PAOUT_,
			
			.TXLED = BIT3,
			.RXLED = BIT4,
			
			.rx_isr = NULL,
			
		}
	};
	//#define _USCI_UART0 _USCI_UART_table[0]
	static USCI_UART_info *_USCI_UART0 = &_USCI_UART_table[0];
	static USCI_UART_info *_USCI_UART1 = &_USCI_UART_table[1];
	
	
	static const char _USCI_I2C_cnt=2;
	static USCI_I2C_info _USCI_I2C_table[]={
		
		{
			.XD_PORT_SEL = (addr)PBSEL_,
			.XD_PORT_SEL2 = (addr)PBSEL_,
			
			.SCL = BIT1,
			.SDA = BIT0,
			
			.CTL0 = (addr)(UCB0CTLW0_+1),
			.CTL1 = (addr)UCB0CTLW0_,
			.BR0 = (addr)UCB0BRW_,
			.BR1 = (addr)(UCB0BRW_+1),
			//.MCTL = (addr)UCB0MCTL_,
			
			.IE = (addr)UCB0ICTL_,
			.IFG = (addr)(UCB0ICTL_+1),
			.STAT = (addr)UCB0STAT_,
			
			.OA = (addr16)UCB0I2COA_,
			.SA = (addr16)UCB0I2CSA_,
			
			.RXIE = UCRXIE,
			.TXIFG = UCTXIFG,
			.RXIFG = UCRXIFG,
			
			.TXBUF = (addr)UCB0TXBUF_,
			.RXBUF = (addr)UCB0RXBUF_,
			
			.ISR_vector = USCI_B0_VECTOR,
	
			.XLED_PORT_DIR = (addr)(PDDIR_+1),
			.XLED_PORT_OUT = (addr)(PDOUT_+1),
			
			.XLED = BIT1,
			
			//.rx_isr = NULL,
			
		},
		{		//TODO edit i2c1 @ UCB1
			.XD_PORT_SEL = (addr)PBSEL_,
			.XD_PORT_SEL2 = (addr)PBSEL_,
			
			.SCL = BIT1,
			.SDA = BIT0,
			
			.CTL0 = (addr)(UCB0CTLW0_+1),
			.CTL1 = (addr)UCB0CTLW0_,
			.BR0 = (addr)UCB0BRW_,
			.BR1 = (addr)(UCB0BRW_+1),
			//.MCTL = (addr)UCB0MCTL_,
			
			.IE = (addr)UCB0ICTL_,
			.IFG = (addr)(UCB0ICTL_+1),
			.STAT = (addr)UCB0STAT_,
			
			.OA = (addr16)UCB0I2COA_,
			.SA = (addr16)UCB0I2CSA_,
			
			.RXIE = UCRXIE,
			.TXIFG = UCTXIFG,
			.RXIFG = UCRXIFG,
			
			.TXBUF = (addr)UCB0TXBUF_,
			.RXBUF = (addr)UCB0RXBUF_,
			
			.ISR_vector = USCI_B0_VECTOR,
	
			.XLED_PORT_DIR = (addr)(PDDIR_+1),
			.XLED_PORT_OUT = (addr)(PDOUT_+1),
			
			.XLED = BIT2,
			
			//.rx_isr = NULL,
			
		}
	};
	static USCI_I2C_info *_USCI_I2C0 = &_USCI_I2C_table[0];
	static USCI_I2C_info *_USCI_I2C1 = &_USCI_I2C_table[1];
	

	static const char _TA_PWM_cnt=2;
	static TA_PWM_info _TA_PWM_table[]={
		
		{
			.PORT_SEL = (addr)PASEL_,
			.PORT_DIR = (addr)PADIR_,
			
			.TA1 = 2,
			.TAs = 0x0f,
	
			.CTL = (addr16)TA0CTL_, 
			
			.CCTL = { (addr16)TA0CCTL0_,
				(addr16)TA0CCTL1_,
				(addr16)TA0CCTL2_,
				(addr16)TA0CCTL3_,
				(addr16)TA0CCTL4_
			},
			
			.CCR = { (addr16)TA0CCR0_,
				(addr16)TA0CCR1_,
				(addr16)TA0CCR2_,
				(addr16)TA0CCR3_,
				(addr16)TA0CCR4_
			}
		
		},
		{
			.PORT_SEL = (addr)(PASEL_+1),
			.PORT_DIR = (addr)(PADIR_+1),
			
			.TA1 = 0,
			.TAs = 0x03,
	
			.CTL = (addr16)TA1CTL_, 
			
			.CCTL = { (addr16)TA1CCTL0_,
				(addr16)TA1CCTL1_,
				(addr16)TA1CCTL2_
			},
			
			.CCR = { (addr16)TA1CCR0_,
				(addr16)TA1CCR1_,
				(addr16)TA1CCR2_
			}
		
		}
	};
	
	static TA_PWM_info *_TA_PWM0 = &_TA_PWM_table[0];
	static TA_PWM_info *_TA_PWM1 = &_TA_PWM_table[1];

#endif

#endif