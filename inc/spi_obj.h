

#ifndef __SPI_OBJ_H
#define __SPI_OBJ_H

#include <stdint.h>

#include "hw_obj.h"

// #include "spi.h"


typedef int (*spi_isr)(const uint16_t ISR_vector, char c);

typedef struct {
	
	const addr XD_PORT_SEL, XD_PORT_SEL2, CLK_PORT_SEL, CLK_PORT_SEL2;
	const uint8_t SIMO, SOMI, SCLK;
	
	const addr CTL0, CTL1, BR0, BR1, MCTL;
	const addr IE, IFG;
	const uint8_t RXIE, TXIFG, RXIFG;
	const addr TXBUF, RXBUF;
	
	ISR_VECTOR ISR_vector;
	
	addr XLED_PORT_DIR, XLED_PORT_OUT;
	uint8_t XLED;
	
	spi_isr rx_isr;
	
// 	_PERIP_CTL_FUNC spi_XD_enable;
// 	_PERIP_CTL_FUNC spi_TX_wait;
	
	
} spi_obj;

typedef spi_obj *spi_handle;


#endif
