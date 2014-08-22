
#include "spi.h"

///////simple control///////////////
inline void spi_port_enable(spi_handle this){
	*this->XD_PORT_SEL |= this->SIMO | this->SOMI;
	*this->XD_PORT_SEL2 |= this->SIMO | this->SOMI;
	*this->CLK_PORT_SEL |= this->SCLK;
	*this->CLK_PORT_SEL2 |= this->SCLK;
}

inline void spi_XLED_enable(spi_handle this){
	*this->XLED_PORT_DIR |= this->XLED;
}

inline void spi_XLED_on(spi_handle this){
	*this->XLED_PORT_OUT |= this->XLED;
}

inline void spi_XLED_off(spi_handle this){
	*this->XLED_PORT_OUT &= ~this->XLED;
}

inline void spi_TX_wait(spi_handle this){
	while (!(*this->IFG & this->TXIFG));
}

inline void spi_RX_wait(spi_handle this){
	while (!(*this->IFG & this->RXIFG));
}

inline void spi_interrupt_enable(spi_handle this){
// 	this->rx_isr = rx_isr;
	*this->IE |= this->RXIE;
}

inline void spi_interrupt_disable(spi_handle this){
	*this->IE &= ~this->RXIE;
}

/////////main functions//////////////////
void spi_init(spi_handle this, uint32_t freq, uint32_t baud, uint8_t mode){ 
	/*init spi interface "this", set buadrate by calculating from frequency
	 */
	uint8_t tmp;
	spi_port_enable(this);  //enble port for special function
	//*this->CTL1 |= UCSWRST;
	*this->CTL1 = UCSWRST + UCSSEL_2; //reset and set clock sourceh
	*this->CTL0 = UCSYNC + UCMSB + mode;
	
	freq = ((freq << 3) + 4) / baud;
	tmp = freq >> 11;
	*this->BR1= tmp; //BR1 <10, no overflow
	freq -= (tmp << 11);
	tmp = freq >> 3;
	*this->BR0= tmp;
	*this->MCTL = _UCBR[ freq - (tmp << 3) ];
	
	*this->CTL1 &= ~UCSWRST; 
	
}

inline char spi__transmit8(spi_handle this, char c){
	
	spi_TX_wait(this);
	*this->TXBUF = c;
	spi_RX_wait(this);
	return *this->RXBUF;
}

inline int spi__transmit16(spi_handle this, int n){
	int r;
	
	spi_TX_wait(this);
	*this->TXBUF = (char)(n >> 8);
	spi_RX_wait(this);
	r = *this->RXBUF;
	spi_TX_wait(this);
	*this->TXBUF = (char)(n & 0xff);
	r = r << 8;
	spi_RX_wait(this);
	return r + *this->RXBUF;
	
}

char spi_transmit8(spi_handle this, char c){
	char r;
	spi_XLED_on(this);
	r = spi__transmit8(this, c);
	spi_XLED_off(this);
	return r;
}

int spi_transmit16(spi_handle this, int n){
	int r;
	spi_XLED_on(this);
	r = spi__transmit16(this, n);
	spi_XLED_off(this);
	return r;
}
/*
void spi_write(spi_handle this,  char *data, uint16_t cnt){
	char *p;
	
	spi_XLED_on(this);
	
	p = data + cnt - 1;
	while (p>=data){
		spi_TX_wait(this);
		*this->TXBUF = *p;
		p--;
	}
	
	spi_XLED_off(this);
	
}

char *spi_read(spi_handle this, char *buf, uint16_t max_cnt){
	char *p = buf + max_cnt;
	
	spi_XLED_on(this);
	
	while (p>buf){ 
		p--;
		spi_RX_wait(this);
		*p = *this->RXBUF;
	}
	
	spi_XLED_off(this);
	
	return p;
	
}*/


char spi_reg8_read8(spi_handle this, char addr, uint16_t wait){
	char r;
	
	spi_XLED_on(this);
	
	spi__transmit8(this, addr);
	while (wait--);
	r = spi__transmit8(this, SPI_READ_LOGIC);
	
	spi_XLED_off(this);
	return  r;
}

int spi_reg8_read16(spi_handle this, char addr, uint16_t wait){ // no delay...
	int r;
	
	spi_XLED_on(this);
	
	spi__transmit8(this, addr);
	while (wait--);
	r = spi__transmit16(this, SPI_READ_LOGIC);
	
	spi_XLED_off(this);
	return  r;
}

void spi_reg8_write8(spi_handle this, char addr, char val, uint16_t wait){
	
	spi_XLED_on(this);
	
	spi__transmit8(this, addr);
	while (wait--);
	spi__transmit8(this, val);
	
	spi_XLED_off(this);
}

void spi_reg8_write16(spi_handle this, char addr, int val, uint16_t wait){
	
	spi_XLED_on(this);
	
	spi__transmit8(this, addr);
	while (wait--);
	spi__transmit16(this, val);
	
	spi_XLED_off(this);
}

int spi_reg16_read16(spi_handle this, uint16_t addr, uint16_t wait){ // no delay...
	int r;
	
	spi_XLED_on(this);
	
	spi__transmit16(this, addr);
	while (wait--);
	r = spi__transmit16(this, SPI_READ_LOGIC);
	
	spi_XLED_off(this);
	return  r;
}

void spi_reg16_write16(spi_handle this, uint16_t addr, int val, uint16_t wait){
	
	spi_XLED_on(this);
	
	spi__transmit16(this, addr);
	while (wait--);
	spi__transmit16(this, val);
	
	spi_XLED_off(this);
}

//////////////////CCS Low-level/////////////////
// inline char ccsSpiTransmit8(spi_handle this, char c){
// 
// 	spi_TX_wait(this);
// 	*this->TXBUF = c;
// 	spi_RX_wait(this);
// 	return *this->RXBUF;
// }


