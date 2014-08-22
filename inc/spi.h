

#ifndef __SPI_H
#define __SPI_H

//#define _ENABLE_USCI_UART_RX_IP

#include <msp430.h>
#include <stdint.h>
#include "misc.h"
#include "spi_obj.h"
// #include "interrupt_proxy.h"


#define SPI_MODE_MASTER	UCMST
#define SPI_MODE_SLAVE	0

#ifndef SPI_READ_LOGIC
#define SPI_READ_LOGIC 0
#endif


extern inline void spi_port_enable(spi_handle this);
extern inline void spi_XLED_enable(spi_handle this);
extern inline void spi_XLED_on(spi_handle this);
extern inline void spi_XLED_off(spi_handle this);

extern inline void spi_TX_wait(spi_handle this);
extern inline void spi_RX_wait(spi_handle this);
extern inline void spi_interrupt_enable(spi_handle this);
extern inline void spi_interrupt_disable(spi_handle this);

extern void spi_init(spi_handle this, uint32_t freq, uint32_t baud, uint8_t mode);

extern inline char spi__transmit8(spi_handle this, char c);
extern inline int spi__transmit16(spi_handle this, int n);

extern inline char spi_transmit8(spi_handle this, char c);
extern inline int spi_transmit16(spi_handle this, int n);

//extern void spi_write(spi_handle this,  char *data, uint16_t cnt);
//extern char *spi_read(spi_handle this, char *buf, uint16_t max_cnt);

extern char spi_reg8_read8(spi_handle this, char addr, uint16_t wait);
extern int spi_reg8_read16(spi_handle this, char addr, uint16_t wait);
extern void spi_reg8_write8(spi_handle this, char addr, char val, uint16_t wait);
extern void spi_reg8_write16(spi_handle this, char addr, int val, uint16_t wait);

extern int spi_reg16_read16(spi_handle this, uint16_t addr, uint16_t wait);
extern void spi_reg16_write16(spi_handle this, uint16_t addr, int val, uint16_t wait);


/*MCTL references*/

#ifndef UCBR7

	#define UCBR0 0b00000000
	#define UCBR1 0b00000010
	#define UCBR2 0b00100010
	#define UCBR3 0b00101010
	#define UCBR4 0b10101010
	#define UCBR5 0b10101110
	#define UCBR6 0b11101110
	#define UCBR7 0b11111110

	static const uint8_t _UCBR[] = {
		UCBR0, UCBR1, UCBR2, UCBR3, UCBR4, UCBR5, UCBR6, UCBR7
	};
	
#endif


#endif
