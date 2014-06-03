
#ifndef __I2C_OBJ_H
#define __I2C_OBJ_H


#include <stdint.h>

#include "hw_obj.h"


typedef int (*i2c_isr)(const uint16_t ISR_vector, char c);


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
	
} i2c_obj;

typedef i2c_obj *i2c_handle;

#endif
