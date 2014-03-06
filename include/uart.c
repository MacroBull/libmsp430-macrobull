
#include "uart.h"

USCI_UART_info *uart_table; // link to global uart_table, for compiler bugs
char uart_cnt;

int uart_handler(const uint16_t ISR_vector, char c){ 
	/*register this handler to isr, scan for real recept function and call
	 */
	
	int i;
	for (i=0;i<uart_cnt;i++){
		if ( ISR_vector == uart_table[i].ISR_vector ){
			USCI_UART_RXLED_on(&uart_table[i]);
			i = uart_table[i].rx_isr(ISR_vector, c);
			USCI_UART_RXLED_off(&uart_table[i]);
			break;
		}
	}
	return i;
	
}


int uart_register(USCI_UART_info *table, char cnt){ 
	/*copy needed gobal table to local table
	 */
	//dev_init();
	uart_table = table;
	uart_cnt = cnt;
	USCI_UART_RX_ISR_setter(uart_handler);
	_EINT();
}

void USCI_UART_init(USCI_UART_info *this, uint32_t freq, uint32_t baud){ 
	/*init uart interface "this", set buadrate by calculating from frequency
	 */
	uint8_t tmp;
	USCI_UART_XD_enable(this);  //enble port for special function
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

void USCI_UART_ISR_setter(USCI_UART_info *this, USCI_UART_RX_ISR rx_isr){
	/* register a function to an uart interface or discard it
	 */
	this->rx_isr = rx_isr;
	if (NULL != rx_isr) {
		*this->IE |= this->RXIE;
	}
	else {
		*this->IE &= ~(this->RXIE);
		//__bic_SR_register(GIE);
	}
	
}
	

inline void USCI_UART_XD_enable(USCI_UART_info *this){
	*this->XD_PORT_SEL = *this->XD_PORT_SEL2 |= this->TXD + this->RXD;
}

inline void USCI_UART_XLED_enable(USCI_UART_info *this){
	*this->XLED_PORT_DIR |= this->TXLED + this->RXLED;
}

inline void USCI_UART_TXLED_on(USCI_UART_info *this){
	*this->XLED_PORT_OUT |= this->TXLED;
}

inline void USCI_UART_TXLED_off(USCI_UART_info *this){
	*this->XLED_PORT_OUT &= ~this->TXLED;
}

inline void USCI_UART_RXLED_on(USCI_UART_info *this){
	*this->XLED_PORT_OUT |= this->RXLED;
}

inline void USCI_UART_RXLED_off(USCI_UART_info *this){
	*this->XLED_PORT_OUT &= ~this->RXLED;
}

inline void USCI_UART_TX_wait(USCI_UART_info *this){
	while (!(*this->IFG & this->TXIFG));
}

inline void USCI_UART__putchar(USCI_UART_info *this, char c){
	/* putc protype without led blink
	 */
	USCI_UART_TX_wait(this);
	*this->TXBUF = c;
}
