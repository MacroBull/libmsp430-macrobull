
#include "misc.h"
#include "qput.h"
#include "uart.h"


/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	
static void _puth(uart_handle uart, uint8_t n){ 
	n = (uint8_t) n; // force!
	uart__putchar(uart, digits[n >> 4]);
	uart__putchar(uart, digits[n & 0xf]);
}

static void _puts(uart_handle uart, char *s){
	while (*s){
		uart__putchar(uart, *s);
		s++;
	}
}



void qputc(uart_handle uart, char n){
	/* put byte in char */
	uart_TXLED_on(uart);
	uart__putchar(uart, n);
	uart_TXLED_off(uart);
}

void qputh(uart_handle uart, char n){
	/* put byte in hex */
	uart_TXLED_on(uart);
	_puth(uart, n);
	uart_TXLED_off(uart);
}

void qputs(uart_handle uart, char *s){
	/* put string */
	uart_TXLED_on(uart);
	_puts(uart, s);
	uart_TXLED_off(uart);
}

void qputsln(uart_handle uart, char *s){
	/* put string */
	uart_TXLED_on(uart);
	_puts(uart, s);
	uart__putchar(uart, '\n');
	uart_TXLED_off(uart);
}
