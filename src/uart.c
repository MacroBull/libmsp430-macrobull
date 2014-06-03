
#include "uart.h"

///////simple control///////////////
inline void uart_XD_enable(uart_handle this){
	*this->XD_PORT_SEL = *this->XD_PORT_SEL2 |= this->TXD | this->RXD;
}

inline void uart_XLED_enable(uart_handle this){
	*this->XLED_PORT_DIR |= this->TXLED | this->RXLED;
}

inline void uart_TXLED_on(uart_handle this){
	*this->XLED_PORT_OUT |= this->TXLED;
}

inline void uart_TXLED_off(uart_handle this){
	*this->XLED_PORT_OUT &= ~this->TXLED;
}

inline void uart_RXLED_on(uart_handle this){
	*this->XLED_PORT_OUT |= this->RXLED;
}

inline void uart_RXLED_off(uart_handle this){
	*this->XLED_PORT_OUT &= ~this->RXLED;
}

inline void uart_TX_wait(uart_handle this){
	while (!(*this->IFG & this->TXIFG));
}

inline void uart_RX_wait(uart_handle this){
	while (!(*this->IFG & this->RXIFG));
}

inline void uart_interrupt_enable(uart_handle this){
// 	this->rx_isr = rx_isr;
	*this->IE |= this->RXIE;
}

inline void uart_interrupt_disable(uart_handle this){
	*this->IE &= ~this->RXIE;
}

/////////main functions//////////////////
void uart_init(uart_handle this, uint32_t freq, uint32_t baud){ 
	/*init uart interface "this", set buadrate by calculating from frequency
	 */
	uint8_t tmp;
	uart_XD_enable(this);  //enble port for special function
	//*this->CTL1 |= UCSWRST;
	*this->CTL1 = UCSWRST + UCSSEL_2; //reset and set clock source
	
	freq = ((freq << 3) + 4) / baud;
	tmp = freq >> 11;
	*this->BR1= tmp; //BR1 <10, no overflow
	freq -= (tmp << 11);
	tmp = freq >> 3;
	*this->BR0= tmp;
	*this->MCTL = _UCBR[ freq - (tmp << 3) ];
	
	*this->CTL1 &= ~UCSWRST; 
	
}

inline void uart__putchar(uart_handle this, char c){
	/* putc protype without led blink
	 */
	uart_TX_wait(this);
	*this->TXBUF = c;
}

inline char uart__getchar(uart_handle this){
	uart_RX_wait(this);
	return *this->RXBUF;
}







