#ifndef __QPUT_H
#define __QPUT_H


/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	
static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */
	

extern void qputc(USCI_UART_info *uart, char n);
extern void qputh(USCI_UART_info *uart, char n);
extern void qputs(USCI_UART_info *uart, char *s);

#endif