
#include "misc.h"
#include "uart.h"


/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	
static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */
	
static void _puth(USCI_UART_info *uart, uint8_t n){ 
	n = (uint8_t) n; // force!
	USCI_UART__putchar(uart, digits[n >> 4]);
	USCI_UART__putchar(uart, digits[n & 0xf]);
}

static void _puts(USCI_UART_info *uart, char *s){
	while (*s){
		USCI_UART__putchar(uart, *s);
		s++;
	}
}



void qputc(USCI_UART_info *uart, char n){
	/* put byte in char */
	USCI_UART_TXLED_on(uart);
	USCI_UART__putchar(uart, n);
	USCI_UART_TXLED_off(uart);
}

void qputh(USCI_UART_info *uart, char n){
	/* put byte in hex */
	USCI_UART_TXLED_on(uart);
	_puth(uart, n);
	USCI_UART_TXLED_off(uart);
}

void qputs(USCI_UART_info *uart, char *s){
	/* put string */
	USCI_UART_TXLED_on(uart);
	_puts(uart, s);
	USCI_UART_TXLED_off(uart);
}
