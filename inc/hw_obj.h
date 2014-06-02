
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
	
	const addr XD_PORT_SEL, XD_PORT_SEL2;
	const uint8_t TXD, RXD;
	
	const addr CTL0, CTL1, BR0, BR1, MCTL;
	const addr IE, IFG;
	const uint8_t RXIE, TXIFG, RXIFG;
	const addr TXBUF, RXBUF;
	
	const uint16_t ISR_vector;
	
	addr XLED_PORT_DIR, XLED_PORT_OUT;
	uint8_t TXLED, RXLED;
	
	USCI_UART_RX_ISR rx_isr;
	
	VTable *pVTable;
	
} USCI_UART_info;

typedef struct {
	
	const addr XD_PORT_SEL, XD_PORT_SEL2;
	const uint8_t SCL, SDA;
	
	const addr CTL0, CTL1, BR0, BR1; //, MCTL;
	const addr IE, IFG, STAT;
	const addr16 OA, SA;
	const uint8_t TXIE, RXIE, TXIFG, RXIFG;
	const addr TXBUF, RXBUF;
	
	const uint16_t ISR_vector;
	
	addr XLED_PORT_DIR, XLED_PORT_OUT;
	
	uint8_t XLED;
	
//	USCI_I2C_RX_ISR rx_isr;
	
	VTable *pVTable;
	
} USCI_I2C_info;


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