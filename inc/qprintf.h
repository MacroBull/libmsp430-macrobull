#ifndef __QPRINTF_H
#define __QPRINTF_H


#define _DISABLE_FLOAT
#warning _DISABLE_FLOAT defined


#define ZEROPAD 1	  /* pad with zero */
#define SIGN	2	  /* unsigned/signed int */
#define PLUS	4	  /* show plus */
#define SPACE   8	  /* space if plus */
#define LEFT	16	 /* left justified */
#define SMALL   32	 /* Must be 32 == 0x20 */
#define SPECIAL 64	 /* 0x */
#define FLOAT   128	 /* float/double */

#ifndef PRINT_BUF_SIZE
	#define PRINT_BUF_SIZE 32
#endif


#include "uart_obj.h"

extern uint16_t sprintf(char *buf, const char *fmt, ...);
extern uint16_t qprintf(uart_handle uart, const char *fmt, ...);

#endif
