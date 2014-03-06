#ifndef __QPRINTF_H
#define __QPRINTF_H

extern int sprintf(char *buf, const char *fmt, ...);
extern int qprintf(USCI_UART_info *uart, const char *fmt, ...);

#endif