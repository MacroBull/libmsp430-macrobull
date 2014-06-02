#ifndef __QPUT_H
#define __QPUT_H

#include "uart_obj.h"

/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	
static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */
	

extern void qputc(uart_handle uart, char n);
extern void qputh(uart_handle uart, char n);
extern void qputs(uart_handle uart, char *s);

#endif