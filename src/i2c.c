/*
 * only register operation in master mode implemented
 */

#include "i2c_obj.h"
#include "i2c.h"


void i2c_init(i2c_handle this, uint32_t freq, uint32_t baud, char is_master){ 
	
	uint8_t tmp;
	
	i2c_XD_enable(this);
	//*this->CTL1 |= UCSWRST;
	*this->CTL1 = UCSWRST + UCSSEL_2;
	*this->CTL0 = UCMODE_3 + UCSYNC;
	*this->CTL0 |= is_master << 3;
	
	freq = ( freq & 1) + freq / baud;
	tmp = freq & 0xff;
	*this->BR0= tmp;
	tmp = freq >> 8;
	*this->BR1= tmp;
	
	*this->CTL1 &= ~UCSWRST;
}



inline void i2c_XD_enable(i2c_handle this){
	*this->XD_PORT_SEL |= this->SCL + this->SDA;
	*this->XD_PORT_SEL2 |= this->SCL + this->SDA;
}

inline void i2c_XLED_enable(i2c_handle this){
	*this->XLED_PORT_DIR |= this->XLED;
}

inline void i2c_XLED_on(i2c_handle this){
	*this->XLED_PORT_OUT |= this->XLED;
}

inline void i2c_XLED_off(i2c_handle this){
	*this->XLED_PORT_OUT &= ~this->XLED;
}

inline void i2c_send_nack(i2c_handle this){
	*this->CTL1 |= UCTXNACK;
	while (*this->CTL1 & UCTXNACK);
}

inline void i2c_send_stop(i2c_handle this){
	*this->CTL1 |= UCTXSTP;
	while (*this->CTL1 & UCTXSTP);
	//while (!(*this->IFG & this->TXIFG));
}

inline void i2c_send_start(i2c_handle this, char is_send){
	
	//*this->CTL1 = ( (*this->CTL1) && 0b11000000 ) + (is_send << 4) + UCTXSTT;
	if (is_send) {
		*this->CTL1 = ( (*this->CTL1) & 0b11000000 ) + UCTR + UCTXSTT;
		while (!(*this->IFG & this->TXIFG));
	}
	else {
		*this->CTL1 = ( (*this->CTL1) & 0b11000000 ) + UCTXSTT;
		while (*this->CTL1 & UCTXSTT);
	}
}

inline void i2c_reset(i2c_handle this){
	*this->CTL1 |= UCSWRST;
}

inline void i2c_set(i2c_handle this){
	*this->CTL1 &= ~UCSWRST;
}

inline void i2c_own_addr_setter(i2c_handle this, uint16_t addr){
	i2c_reset(this);
	*this->OA = 0x80 + addr;
}

inline void i2c_slave_addr_setter(i2c_handle this, uint16_t addr){
	i2c_reset(this);
	*this->SA = addr;
}

inline void i2c__write8(i2c_handle this, char c){
	
	i2c_send_start(this, 1);
	*this->TXBUF = c;
	//__bis_SR_register(CPUOFF + GIE);
	//while (UCB0CTL1 & UCTXSTT); // is OK
	while (!(*this->IFG & this->TXIFG));
	i2c_send_stop(this);

}

inline void i2c__write16(i2c_handle this, int n){
	
	i2c_send_start(this, 1);
	*this->TXBUF = (char)(n >> 8);
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(n & 0xff);
	while (!(*this->IFG & this->TXIFG));
	i2c_send_stop(this);

}

inline char i2c__read8(i2c_handle this){
	char r;
	
	i2c_send_start(this, 0);
	while (!(*this->IFG & this->RXIFG));
	r = *this->RXBUF;
	i2c_send_stop(this);
	return r;
}

inline int i2c__read16(i2c_handle this){
	int r;
	
	i2c_send_start(this, 0);
	while (!(*this->IFG & this->RXIFG));
	r = *this->RXBUF;
	r = r << 8;
	while (!(*this->IFG & this->RXIFG));
	r += *this->RXBUF;
	i2c_send_stop(this);
	return r;
}

void i2c_write(i2c_handle this,  char *data, uint16_t cnt){
	char *p;
	
	i2c_XLED_on(this);
	
	p = data + cnt - 1;
	i2c_send_start(this, 1);
	while (p>=data){
		*this->TXBUF = *p;
		p--;
		while (!(*this->IFG & this->TXIFG));
	}
	
	i2c_send_stop(this);
	
	i2c_XLED_off(this);

}

char *i2c_read(i2c_handle this, char *buf, uint16_t max_cnt){
	char *p = buf + max_cnt;
	
	i2c_XLED_on(this);
	i2c_send_start(this, 0);
	
	while ((p>buf)&&(*this->STAT & UCNACKIFG)){ // UCNACKIFG not work for this??? it works~~~ but as bellow
		p--;
		while (!(*this->IFG & this->RXIFG));
		*p = *this->RXBUF;
	}
	/* one buffer before NACK */
	p--;
	while (!(*this->IFG & this->RXIFG));
	*p = *this->RXBUF;
	
	i2c_send_stop(this);
	i2c_XLED_off(this);
	
	return p;
	
}


char i2c_reg8_read8(i2c_handle this, char addr){ // no delay...
	char r;
	
	i2c_XLED_on(this);
	
	i2c__write8(this, addr);
	r = i2c__read8(this);
	
	i2c_XLED_off(this);
	return  r;
}

int i2c_reg8_read16(i2c_handle this, char addr){ // no delay...
	int r;
	i2c_XLED_on(this);
	
	i2c__write8(this, addr);
	r = i2c__read16(this);
	i2c_XLED_off(this);
	
	return r;
}

void i2c_reg8_write8(i2c_handle this, char addr, char val){
	
	i2c_XLED_on(this);
	
	i2c_send_start(this, 1);
	*this->TXBUF = addr;
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = val;
	while (!(*this->IFG & this->TXIFG));
	i2c_send_stop(this);
	
	i2c_XLED_off(this);
}

void i2c_reg8_write16(i2c_handle this, char addr, int val){
	
	i2c_XLED_on(this);
	
	i2c_send_start(this, 1);
	*this->TXBUF = addr;
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(val >> 8);
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(val & 0xff);
	while (!(*this->IFG & this->TXIFG));
	i2c_send_stop(this);
	
	i2c_XLED_off(this);
}

/*
char i2c_reg16_read8(i2c_handle this, char addr){ // no delay...
	i2c__write8(this, addr);
	return i2c__read8(this);
}

int i2c_reg16_read16(i2c_handle this, char addr){ // no delay...
	i2c__write8(this, addr);
	return i2c__read16(this);
}
*/