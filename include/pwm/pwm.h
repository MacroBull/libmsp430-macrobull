
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
#define TBCLK	TBSSEL_0

#define ACLK	TASSEL_1
#define SMCLK	TASSEL_2
#define INCLK	TASSEL_3

#define POUT	OUTMOD_7 // +duty%
#define NOUT	OUTMOD_2 // -duty%
#define TOGGLE	OUTMOD_4 // -duty%

typedef struct {
	
	const addr PORT_SEL, PORT_SEL2, PORT_DIR;
	/* const */ uint8_t OUT0; // TA1~TAn mask = TAs << TA0 #!important
	uint8_t OUTs;
	
	const addr16 CTL;
	const addr16 CCR[8]; // each CCR
	const addr16 CCTL[8]; // each output mode
	
} PWM_OBJ;

typedef PWM_OBJ *PWM_HANDLE;

#endif
