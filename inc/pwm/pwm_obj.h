
#ifndef __PWM_OBJ_H
#define __PWM_OBJ_H

#include <stdint.h>

#include "hw_obj.h"

#define _CCR0 CCR[0]

typedef struct {
	
	const addr PORT_SEL, PORT_SEL2, PORT_DIR;
	/* const */ uint8_t OUT1; // TA1~TAn mask = TAs << TA0 #!important
	uint8_t OUTs;
	
	const addr16 CTL;
	const addr16 CCR[8]; // each CCR
	const addr16 CCTL[8]; // each output mode
	
} pwm_obj;

typedef pwm_obj *pwm_handle;

#endif
