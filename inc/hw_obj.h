
#ifndef __HW_OBJ_H
#define __HW_OBJ_H

#include <stdint.h>

#include "misc.h"

typedef char *addr8; // Little Endian no problem
typedef addr8 addr; // Little Endian no problem
typedef int *addr16; // Little Endian no problem

typedef const uint16_t ISR_VECTOR; 


typedef void (*_PERIP_CTL_FUNC)(void *obj);



#endif

// typedef int (*USCI_UART_RX_ISR)(const uint16_t ISR_vector, char c);

/*



typedef struct {
	
	const addr PORT_SEL, PORT_DIR;
	const uint8_t TA1; // TA1~TAn mask = TAs << TA0
	uint8_t TAs;
	
	const addr16 CTL;
	const addr16 CCR[8]; // each CCR
	const addr16 CCTL[8]; // each output mode
	
	VTable *pVTable;
	
} TA_PWM_info;






#endif*/