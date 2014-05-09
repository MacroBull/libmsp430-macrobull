
#ifndef __PIN_H
#define __PIN_H

#include <msp430.h>
#include "misc.h"
#include "hw_obj.h"

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
