
#ifndef __PWM_H
#define __PWM_H


#include <msp430.h>
#include <stdint.h>

#include "hw_obj.h"

#define _CCR0 CCR[0]

#define STOP	MC_0
#define UP		MC_1
#define CONT	MC_2
#define UP_DOWN	MC_3

#define TACLK	TASSEL_0
#define ACLK	TASSEL_1
#define SMCLK	TASSEL_2
#define INCLK	TASSEL_3

#define POUT	OUTMOD_7 // +duty%
#define NOUT	OUTMOD_2 // -duty%



extern void TA_PWM_enable(TA_PWM_info *this, uint16_t clock_source, char counter_mode, uint8_t outputs, uint16_t period);

extern void TA_PWM_setter(TA_PWM_info *this, uint8_t cc_id, uint16_t cc_cnt, uint16_t cc_mode);
	
#endif