
#ifndef __BSP_H
#define __BSP_H

#include <msp430.h>
#include "misc.h"


//////////////uart ////////////////////////
#ifdef __BOARD_HAS_UART__
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
		.CTL1 =	(addr)_PERIP_UART0_CTL1_ADDR,
		.BR0 =	(addr)_PERIP_UART0_BR0_ADDR,
		.BR1 =	(addr)_PERIP_UART0_BR1_ADDR,
		.MCTL =	(addr)_PERIP_UART0_MCTL_ADDR,
		
		.IE =	(addr)_PERIP_UART0_IE_ADDR,
		.IFG =	(addr)_PERIP_UART0_IFG_ADDR,
		
		.RXIE =	_PERIP_UART0_RXIE,
		.TXIFG =	_PERIP_UART0_TXIFG,
		.RXIFG =	_PERIP_UART0_RXIFG,
		
		.TXBUF =	(addr)_PERIP_UART0_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_UART0_RXBUF_ADDR,
	
		.ISR_vector =	_PERIP_UART0_ISR_VECTOR,
	
		.XLED_PORT_DIR =	(addr)&P1DIR,
		.XLED_PORT_OUT =	(addr)&P1OUT,

		.TXLED =	BIT0,
		.RXLED =	BIT6,
	
		
		
	
	}
};

static uart_handle UART0 = &UART_TABLE[0];

#endif

////////////////pwm///////////////////////
#ifdef __BOARD_HAS_PWM__

#define PWM_CNT _PERIP_PWM_CNT

#include "pwm/pwm_obj.h"

static pwm_obj PWM_TABLE[]={
	
	{
		.PORT_SEL = (addr)_PERIP_PWM0_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM0_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM0_PORT_DIR_ADDR,
		
		.OUT1 = _PERIP_PWM0_OUT1,
		.OUTs = 0x03 << 1,

		.CTL = (addr16)_PERIP_PWM0_CTL_ADDR, 
		.CCTL = { (addr16)_PERIP_PWM0_CCTL0_ADDR,
			(addr16)_PERIP_PWM0_CCTL1_ADDR,
			(addr16)_PERIP_PWM0_CCTL2_ADDR,
		},
		
		.CCR = { (addr16)_PERIP_PWM0_CCR0_ADDR,
			(addr16)_PERIP_PWM0_CCR1_ADDR,
			(addr16)_PERIP_PWM0_CCR2_ADDR,
		}
	
	},
	{
		.PORT_SEL = (addr)_PERIP_PWM1_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM1_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM1_PORT_DIR_ADDR,
		
		.OUT1 = _PERIP_PWM1_OUT1,
		.OUTs = 0x03 << 1,

		.CTL = (addr16)_PERIP_PWM1_CTL_ADDR, 
		.CCTL = { (addr16)_PERIP_PWM1_CCTL0_ADDR,
			(addr16)_PERIP_PWM1_CCTL1_ADDR,
			(addr16)_PERIP_PWM1_CCTL2_ADDR,
		},
		
		.CCR = { (addr16)_PERIP_PWM1_CCR0_ADDR,
			(addr16)_PERIP_PWM1_CCR1_ADDR,
			(addr16)_PERIP_PWM1_CCR2_ADDR,
		}
	
	}
};

static pwm_handle PWM0 = &PWM_TABLE[0];
static pwm_handle PWM1 = &PWM_TABLE[1];

#endif

//////////////i2c////////////////////
#ifdef __BOARD_HAS_I2C__

#define I2C_CNT _PERIP_I2C_CNT

#include "i2c_obj.h"
#include "i2c.h"

static i2c_obj I2C_TABLE[]={
	{
		.XD_PORT_SEL =	(addr)_PERIP_I2C0_XD_PORT_SEL_ADDR,
		.XD_PORT_SEL2 =	(addr)_PERIP_I2C0_XD_PORT_SEL2_ADDR,
		
		.SCL =	_PERIP_I2C0_SCL,
		.SDA =	_PERIP_I2C0_SDA,
		
		.CTL0 =	(addr)_PERIP_I2C0_CTL0_ADDR,
		.CTL1 =	(addr)_PERIP_I2C0_CTL1_ADDR,
		.BR0 =	(addr)_PERIP_I2C0_BR0_ADDR,
		.BR1 =	(addr)_PERIP_I2C0_BR1_ADDR,
// 		.MCTL =	(addr)_PERIP_I2C0_MCTL,
		
		.IE =	(addr)_PERIP_I2C0_IE_ADDR,
		.IFG =	(addr)_PERIP_I2C0_IFG_ADDR,
		.STAT = (addr)_PERIP_I2C0_STAT_ADDR,
		
		.OA = (addr16)_PERIP_I2C0_OA_ADDR,
		.SA = (addr16)_PERIP_I2C0_SA_ADDR,
		
		.RXIE =	_PERIP_I2C0_RXIE,
		.TXIFG =	_PERIP_I2C0_TXIFG,
		.RXIFG =	_PERIP_I2C0_RXIFG,
		
		.TXBUF =	(addr)_PERIP_I2C0_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_I2C0_RXBUF_ADDR,
		
		.ISR_vector =	_PERIP_I2C0_ISR_VECTOR,
		
//		.XLED_PORT_DIR =	(addr)PADIR_,
//		.XLED_PORT_OUT =	(addr)PAOUT_,
//
//		.XLED =	BIT0,
		
	}
};


static i2c_handle I2C0 = &I2C_TABLE[0];


#endif


//////////////////timer/////////////////////
#ifdef __BOARD_HAS_TIMER__

#define TIMER_CNT _PERIP_TIMER_CNT

#include "timer_obj.h"

static timer_obj TIMER_TABLE[]={
	{
		.CTL = (addr16)_PERIP_TIMER0_CTL_ADDR,
		.CCR0 = (addr16)_PERIP_TIMER0_CCR0_ADDR,
		
		.TIE = _PERIP_TIMER0_IE,

		.OV_ISR_vector = _PERIP_TIMER0_OV_ISR_VECTOR,
// 		.OV_ISR_callbacks = _PERIP_TIMER0_OV_ISR_CALLBACKS_ADDR,

		.events = NULL
	},
	{
		.CTL = (addr16)_PERIP_TIMER1_CTL_ADDR,
		.CCR0 = (addr16)_PERIP_TIMER1_CCR0_ADDR,
		
		.TIE = _PERIP_TIMER1_IE,

		.OV_ISR_vector = _PERIP_TIMER1_OV_ISR_VECTOR,
// 		.OV_ISR_callbacks = _PERIP_TIMER1_OV_ISR_CALLBACKS_ADDR,

		.events = NULL
	}
};

static timer_handle TIMER0 = &TIMER_TABLE[0];
static timer_handle TIMER1 = &TIMER_TABLE[1];

#endif

#endif