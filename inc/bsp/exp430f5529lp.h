
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
		.RXLED =	BIT0,
	
		
		
	
	},
	{
		.XD_PORT_SEL =	(addr)_PERIP_UART1_XD_PORT_SEL_ADDR,
		.XD_PORT_SEL2 =	(addr)_PERIP_UART1_XD_PORT_SEL2_ADDR,
		
		.TXD =	_PERIP_UART1_TXD,
		.RXD =	_PERIP_UART1_RXD,
		
		.CTL0 =	(addr)_PERIP_UART1_CTL0_ADDR,
		.CTL1 =	(addr)_PERIP_UART1_CTL1_ADDR,
		.BR0 =	(addr)_PERIP_UART1_BR0_ADDR,
		.BR1 =	(addr)_PERIP_UART1_BR1_ADDR,
		.MCTL =	(addr)_PERIP_UART1_MCTL_ADDR,
		
		.IE =	(addr)_PERIP_UART1_IE_ADDR,
		.IFG =	(addr)_PERIP_UART1_IFG_ADDR,
		
		.RXIE =	_PERIP_UART1_RXIE,
		.TXIFG =	_PERIP_UART1_TXIFG,
		.RXIFG =	_PERIP_UART1_RXIFG,
		
		.TXBUF =	(addr)_PERIP_UART1_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_UART1_RXBUF_ADDR,
	
		.ISR_vector =	_PERIP_UART1_ISR_VECTOR,
	
		.XLED_PORT_DIR =	(addr)&P4DIR,
		.XLED_PORT_OUT =	(addr)&P4OUT,

		.TXLED =	BIT7,
		.RXLED =	BIT7,
		
		
	
	}
};

static uart_handle UART0 = &UART_TABLE[0];
static uart_handle UART1 = &UART_TABLE[1];

////////////////pwm///////////////////////

#define PWM_CNT _PERIP_PWM_CNT

#include "pwm/pwm_obj.h"

static pwm_obj PWM_TABLE[]={
	
	{
		.PORT_SEL = (addr)_PERIP_PWM0_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM0_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM0_PORT_DIR_ADDR,
		
		.OUT1 = _PERIP_PWM0_OUT1,
		.OUTs = 0x0f << 1,

		.CTL = (addr16)_PERIP_PWM0_CTL_ADDR, 
		.CCTL = { (addr16)_PERIP_PWM0_CCTL0_ADDR,
			(addr16)_PERIP_PWM0_CCTL1_ADDR,
			(addr16)_PERIP_PWM0_CCTL2_ADDR,
			(addr16)_PERIP_PWM0_CCTL3_ADDR,
			(addr16)_PERIP_PWM0_CCTL4_ADDR,
		},
		
		.CCR = { (addr16)_PERIP_PWM0_CCR0_ADDR,
			(addr16)_PERIP_PWM0_CCR1_ADDR,
			(addr16)_PERIP_PWM0_CCR2_ADDR,
			(addr16)_PERIP_PWM0_CCR3_ADDR,
			(addr16)_PERIP_PWM0_CCR4_ADDR,
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
	
	},
	{
		.PORT_SEL = (addr)_PERIP_PWM2_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM2_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM2_PORT_DIR_ADDR,
		
		.OUT1 = _PERIP_PWM2_OUT1,
		.OUTs = 0x03 << 1,

		.CTL = (addr16)_PERIP_PWM2_CTL_ADDR, 
		.CCTL = { (addr16)_PERIP_PWM2_CCTL0_ADDR,
			(addr16)_PERIP_PWM2_CCTL1_ADDR,
			(addr16)_PERIP_PWM2_CCTL2_ADDR,
		},
		
		.CCR = { (addr16)_PERIP_PWM2_CCR0_ADDR,
			(addr16)_PERIP_PWM2_CCR1_ADDR,
			(addr16)_PERIP_PWM2_CCR2_ADDR,
		}
	
	},
	{
		.PORT_SEL = (addr)_PERIP_PWM3_PORT_SEL_ADDR,
		.PORT_SEL2 = (addr)_PERIP_PWM3_PORT_SEL2_ADDR,
		.PORT_DIR = (addr)_PERIP_PWM3_PORT_DIR_ADDR,
		
		.OUT1 = _PERIP_PWM3_OUT1,
		.OUTs = 0x3f << 1,

		.CTL = (addr16)_PERIP_PWM3_CTL_ADDR, 
		.CCTL = { (addr16)_PERIP_PWM3_CCTL0_ADDR,
			(addr16)_PERIP_PWM3_CCTL1_ADDR,
			(addr16)_PERIP_PWM3_CCTL2_ADDR,
			(addr16)_PERIP_PWM3_CCTL3_ADDR,
			(addr16)_PERIP_PWM3_CCTL4_ADDR,
			(addr16)_PERIP_PWM3_CCTL5_ADDR,
			(addr16)_PERIP_PWM3_CCTL6_ADDR,
		},
		
		.CCR = { (addr16)_PERIP_PWM3_CCR0_ADDR,
			(addr16)_PERIP_PWM3_CCR1_ADDR,
			(addr16)_PERIP_PWM3_CCR2_ADDR,
			(addr16)_PERIP_PWM3_CCR3_ADDR,
			(addr16)_PERIP_PWM3_CCR4_ADDR,
			(addr16)_PERIP_PWM3_CCR5_ADDR,
			(addr16)_PERIP_PWM3_CCR6_ADDR,
		}
	
	}
};

static pwm_handle PWM0 = &PWM_TABLE[0];
static pwm_handle PWM1 = &PWM_TABLE[1];
static pwm_handle PWM2 = &PWM_TABLE[2];

//////////////i2c////////////////////

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
		
	},
	{
		.XD_PORT_SEL =	(addr)_PERIP_I2C1_XD_PORT_SEL_ADDR,
		.XD_PORT_SEL2 =	(addr)_PERIP_I2C1_XD_PORT_SEL2_ADDR,
		
		.SCL =	_PERIP_I2C1_SCL,
		.SDA =	_PERIP_I2C1_SDA,
		
		.CTL0 =	(addr)_PERIP_I2C1_CTL0_ADDR,
		.CTL1 =	(addr)_PERIP_I2C1_CTL1_ADDR,
		.BR0 =	(addr)_PERIP_I2C1_BR0_ADDR,
		.BR1 =	(addr)_PERIP_I2C1_BR1_ADDR,
		// 		.MCTL =	(addr)_PERIP_I2C1_MCTL,
		
		.IE =	(addr)_PERIP_I2C1_IE_ADDR,
		.IFG =	(addr)_PERIP_I2C1_IFG_ADDR,
		.STAT = (addr)_PERIP_I2C1_STAT_ADDR,
		
		.OA = (addr16)_PERIP_I2C1_OA_ADDR,
		.SA = (addr16)_PERIP_I2C1_SA_ADDR,
		
		.RXIE =	_PERIP_I2C1_RXIE,
		.TXIFG =	_PERIP_I2C1_TXIFG,
		.RXIFG =	_PERIP_I2C1_RXIFG,
		
		.TXBUF =	(addr)_PERIP_I2C1_TXBUF_ADDR,
		.RXBUF =	(addr)_PERIP_I2C1_RXBUF_ADDR,
		
		.ISR_vector =	_PERIP_I2C1_ISR_VECTOR,
		
//		.XLED_PORT_DIR =	(addr)(PBDIR_+1),
//		.XLED_PORT_OUT =	(addr)(PBOUT_+1),
//
//		.XLED =	BIT7,
	}
};


static i2c_handle I2C0 = &I2C_TABLE[0];
static i2c_handle I2C1 = &I2C_TABLE[1];


#endif


//////////////////timer/////////////////////

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
	},
	{
		.CTL = (addr16)_PERIP_TIMER2_CTL_ADDR,
		.CCR0 = (addr16)_PERIP_TIMER2_CCR0_ADDR,
		
		.TIE = _PERIP_TIMER2_IE,

		.OV_ISR_vector = _PERIP_TIMER2_OV_ISR_VECTOR,
// 		.OV_ISR_callbacks = _PERIP_TIMER2_OV_ISR_CALLBACKS_ADDR,

		.events = NULL
	},
	{
		.CTL = (addr16)_PERIP_TIMER3_CTL_ADDR,
		.CCR0 = (addr16)_PERIP_TIMER3_CCR0_ADDR,
		
		.TIE = _PERIP_TIMER3_IE,

		.OV_ISR_vector = _PERIP_TIMER3_OV_ISR_VECTOR,
// 		.OV_ISR_callbacks = _PERIP_TIMER3_OV_ISR_CALLBACKS_ADDR,

		.events = NULL
	}
};

static timer_handle TIMER0 = &TIMER_TABLE[0];
static timer_handle TIMER1 = &TIMER_TABLE[1];
static timer_handle TIMER2 = &TIMER_TABLE[2];
