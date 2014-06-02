#ifndef __QPRINTF_H
#define __QPRINTF_H

#include "uart_obj.h"

extern int sprintf(char *buf, const char *fmt, ...);
extern int qprintf(uart_handle uart, const char *fmt, ...);

#endif