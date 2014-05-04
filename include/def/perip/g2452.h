
#ifndef __PERIP_H
#define __PERIP_H

#include <msp430.h>

//#include "hw_obj.h"

#define	_PERIP_PWM_CNT	1

#define	_PERIP_PWM0_PORT_SEL_ADDR	P1SEL_
#define	_PERIP_PWM0_PORT_SEL2_ADDR	P1SEL2_
#define	_PERIP_PWM0_PORT_DIR_ADDR	P1DIR_


#define	_PERIP_PWM0_OUT0	5
#define	_PERIP_PWM0_OUTs	BIT1  // Default P1.6 TA0.1 Only
/*
#define	_PERIP_PWM0_OUT0	1
#define	_PERIP_PWM0_OUTs	0x01
*/

#define	_PERIP_PWM0_CTL	TACTL_
#define	_PERIP_PWM0_CCTL0	CCTL0_
#define	_PERIP_PWM0_CCTL1	CCTL1_
#define	_PERIP_PWM0_CCTL2	CCTL2_

#define	_PERIP_PWM0_CCR0	CCR0_
#define	_PERIP_PWM0_CCR1	CCR1_
#define	_PERIP_PWM0_CCR2	CCR2_


#endif
