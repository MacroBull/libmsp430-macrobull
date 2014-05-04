/*
 * only register operation in master mode implemented
 */

#include "i2c.h"


/*
USCI_I2C_info *uart_table;
char i2c_cnt;
*/


/*
 * 
int uart_register(USCI_I2C_info *table, char cnt){
	//dev_init();
	uart_table = table;
	uart_cnt = cnt;
	USCI_I2C_RX_ISR_setter(uart_handler);
}

*/


void USCI_I2C_init(USCI_I2C_info *this, uint32_t freq, uint32_t baud, char is_master){ 
	
	uint8_t tmp;
	
	USCI_I2C_XD_enable(this);
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


/*
void USCI_I2C_ISR_setter(USCI_I2C_info *this, USCI_I2C_RX_ISR rx_isr){

	this->rx_isr = rx_isr;
	if (NULL != rx_isr) {
		*this->IE |= this->RXIE;
		_EINT();
	}
	else {
		*this->IE &= ~(this->RXIE);
		__bic_SR_register(GIE);
	}
	
}
*/
	

inline void USCI_I2C_XD_enable(USCI_I2C_info *this){
	*this->XD_PORT_SEL |= this->SCL + this->SDA;
	*this->XD_PORT_SEL2 |= this->SCL + this->SDA;
}

inline void USCI_I2C_XLED_enable(USCI_I2C_info *this){
	*this->XLED_PORT_DIR |= this->XLED;
}

inline void USCI_I2C_XLED_on(USCI_I2C_info *this){
	*this->XLED_PORT_OUT |= this->XLED;
}

inline void USCI_I2C_XLED_off(USCI_I2C_info *this){
	*this->XLED_PORT_OUT &= ~this->XLED;
}

inline void USCI_I2C_send_nack(USCI_I2C_info *this){
	*this->CTL1 |= UCTXNACK;
	while (*this->CTL1 & UCTXNACK);
}

inline void USCI_I2C_send_stop(USCI_I2C_info *this){
	*this->CTL1 |= UCTXSTP;
	while (*this->CTL1 & UCTXSTP);
	//while (!(*this->IFG & this->TXIFG));
}

inline void USCI_I2C_send_start(USCI_I2C_info *this, char is_send){
	
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

inline void USCI_I2C_reset(USCI_I2C_info *this){
	*this->CTL1 |= UCSWRST;
}

inline void USCI_I2C_set(USCI_I2C_info *this){
	*this->CTL1 &= ~UCSWRST;
}

inline void USCI_I2C_own_addr_setter(USCI_I2C_info *this, uint16_t addr){
	USCI_I2C_reset(this);
	*this->OA = 0x80 + addr;
}

inline void USCI_I2C_slave_addr_setter(USCI_I2C_info *this, uint16_t addr){
	USCI_I2C_reset(this);
	*this->SA = addr;
}

inline void USCI_I2C__write8(USCI_I2C_info *this, char c){
	
	USCI_I2C_send_start(this, 1);
	*this->TXBUF = c;
	//__bis_SR_register(CPUOFF + GIE);
	//while (UCB0CTL1 & UCTXSTT); // is OK
	while (!(*this->IFG & this->TXIFG));
	USCI_I2C_send_stop(this);

}

inline void USCI_I2C__write16(USCI_I2C_info *this, int n){
	
	USCI_I2C_send_start(this, 1);
	*this->TXBUF = (char)(n >> 8);
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(n & 0xff);
	while (!(*this->IFG & this->TXIFG));
	USCI_I2C_send_stop(this);

}

inline char USCI_I2C__read8(USCI_I2C_info *this){
	char r;
	
	USCI_I2C_send_start(this, 0);
	while (!(*this->IFG & this->RXIFG));
	r = *this->RXBUF;
	USCI_I2C_send_stop(this);
	return r;
}

inline int USCI_I2C__read16(USCI_I2C_info *this){
	int r;
	
	USCI_I2C_send_start(this, 0);
	while (!(*this->IFG & this->RXIFG));
	r = *this->RXBUF;
	r = r << 8;
	while (!(*this->IFG & this->RXIFG));
	r += *this->RXBUF;
	USCI_I2C_send_stop(this);
	return r;
}

void USCI_I2C_write(USCI_I2C_info *this,  char *data, uint16_t cnt){
	char *p;
	
	USCI_I2C_XLED_on(this);
	
	p = data + cnt - 1;
	USCI_I2C_send_start(this, 1);
	while (p>=data){
		*this->TXBUF = *p;
		p--;
		while (!(*this->IFG & this->TXIFG));
	}
	
	USCI_I2C_send_stop(this);
	
	USCI_I2C_XLED_off(this);

}

char *USCI_I2C_read(USCI_I2C_info *this, char *buf, uint16_t max_cnt){
	char *p = buf + max_cnt;
	
	USCI_I2C_XLED_on(this);
	USCI_I2C_send_start(this, 0);
	
	while ((p>buf)&&(*this->STAT & UCNACKIFG)){ // UCNACKIFG not work for this??? it works~~~ but as bellow
		p--;
		while (!(*this->IFG & this->RXIFG));
		*p = *this->RXBUF;
	}
	/* one buffer before NACK */
	p--;
	while (!(*this->IFG & this->RXIFG));
	*p = *this->RXBUF;
	
	USCI_I2C_send_stop(this);
	USCI_I2C_XLED_off(this);
	
	return p;
	
}


char USCI_I2C_reg8_read8(USCI_I2C_info *this, char addr){ // no delay...
	char r;
	
	USCI_I2C_XLED_on(this);
	
	USCI_I2C__write8(this, addr);
	r = USCI_I2C__read8(this);
	
	USCI_I2C_XLED_off(this);
	return  r;
}

int USCI_I2C_reg8_read16(USCI_I2C_info *this, char addr){ // no delay...
	int r;
	USCI_I2C_XLED_on(this);
	
	USCI_I2C__write8(this, addr);
	r = USCI_I2C__read16(this);
	USCI_I2C_XLED_off(this);
	
	return r;
}

void USCI_I2C_reg8_write8(USCI_I2C_info *this, char addr, char val){
	
	USCI_I2C_XLED_on(this);
	
	USCI_I2C_send_start(this, 1);
	*this->TXBUF = addr;
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = val;
	while (!(*this->IFG & this->TXIFG));
	USCI_I2C_send_stop(this);
	
	USCI_I2C_XLED_off(this);
}

void USCI_I2C_reg8_write16(USCI_I2C_info *this, char addr, int val){
	
	USCI_I2C_XLED_on(this);
	
	USCI_I2C_send_start(this, 1);
	*this->TXBUF = addr;
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(val >> 8);
	while (!(*this->IFG & this->TXIFG));
	*this->TXBUF = (char)(val & 0xff);
	while (!(*this->IFG & this->TXIFG));
	USCI_I2C_send_stop(this);
	
	USCI_I2C_XLED_off(this);
}

/*
char USCI_I2C_reg16_read8(USCI_I2C_info *this, char addr){ // no delay...
	USCI_I2C__write8(this, addr);
	return USCI_I2C__read8(this);
}

int USCI_I2C_reg16_read16(USCI_I2C_info *this, char addr){ // no delay...
	USCI_I2C__write8(this, addr);
	return USCI_I2C__read16(this);
}
*/