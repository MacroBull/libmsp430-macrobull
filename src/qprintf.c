/*
 * simplified quick printf 
 * buf size = 32 by default 
 * 
 * original: http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/arch/x86/boot/printf.c
 * 
 * https://dl.dropboxusercontent.com/u/73985358/lib-macrobull/msp430/include/qprintf.c
 */

#include <msp430.h>

#include <stdint.h>
#include <stdarg.h>

#include "misc.h"
#include "uart.h"
#include "qput.h"
#include "qprintf.h"

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

#define do_div(n,base) ({ \
	int __res; \
	__res = ((unsigned int) n) % (unsigned) base; \
	n = ((unsigned int) n) / (unsigned) base; \
	__res; })
	
#define isdigit(c) ((c>='0') && (c<='9'))


static int skip_atoi(const char **s){
	
	int i = 0;
	while (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
	
}

static int qstrlen(const char *s, int maxlen){
	int l = maxlen;
	while ( (*s++) && (--l));
	return maxlen - l;
}




static char *number(char *str, int num, char base, char size, char precision, uint8_t type){

	char tmp[18];
	uint8_t c, sign, locase;
	uint8_t i;

	/* locase = 0 or 0x20. ORing digits or letters with 'locase'
	* produces same digits or (maybe lowercased) letters */
	
	locase = (type & SMALL);
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 36)
		return NULL;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAL) {
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
		while (num != 0)
			tmp[i++] = (digits[do_div(num, base)] | locase);
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type & (ZEROPAD + LEFT)))
		while (size-- > 0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type & SPECIAL) {
		if (base == 8)
			*str++ = '0';
		else if (base == 16) {
			*str++ = '0';
			*str++ = ('X' | locase);
		}
	}
	if (!(type & LEFT))
		while (size-- > 0)
			*str++ = c;
	while (i < precision--)
		*str++ = '0';
	while (i-- > 0)
		*str++ = tmp[i];
	while (size-- > 0)
		*str++ = ' ';
	
	return str;
	
}

#ifndef _DISABLE_FLOAT
char *number_float(char *str, double num_f, char size, char precision, uint8_t type){
	
	//char *st = str;
	//unsigned long num;
	uint16_t num;
	char tmp[11];
	uint8_t c, sign;
	uint8_t i;

	if (type & LEFT)
		type &= ~ZEROPAD;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num_f < 0) {
			sign = '-';
			num_f = -num_f;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	
	for (i=0; i<precision; i++) num_f *= 10;
	num= (unsigned int)(num_f + 0.5);
	//num= (unsigned int)(num_f + 0.5);
	
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
		while (num != 0) {
			if (i == precision) tmp[i++] = '.';
			tmp[i++] = digits[do_div(num, 10)];
		}
		
	size -= i;
	if (!(type & (ZEROPAD + LEFT)))
		while (size-- > 0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	
	if (!(type & LEFT))
		while (size-- > 0)
			*str++ = c;
		
	while (i-- > 0)
		*str++ = tmp[i];
	while (size-- > 0)
		*str++ = ' ';
	
	return str;
	
}
#endif

int vsprintf(char *buf, const char *fmt, va_list args){
	
	int len;
	unsigned int num;
	char i, base;
	char *str;
	const char *s;
	
	#ifndef _DISABLE_FLOAT
	double num_float;
	#endif
	
	uint8_t flags;			 /* flags to number() */
 
	char field_width;		/* width of output field */
	char precision;		 /* min. # of digits for integers; max
						number of chars for from string */
 
	for (str = buf; *fmt; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
 
		/* process flags */
	flags = 0;
	repeat:
		++fmt;	 /* this also skips first '%' */
		switch (*fmt) {
		case '-':
			flags |= LEFT;
			goto repeat;
		case '+':
			flags |= PLUS;
			goto repeat;
		case ' ':
			flags |= SPACE;
			goto repeat;
		case '#':
			flags |= SPECIAL;
			goto repeat;
		case '0':
			flags |= ZEROPAD;
			goto repeat;
		}
 
		/* get field width */
		field_width = -1;
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			/* it's the next argument */
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}
 
		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}
 
		/* default base */
		base = 10;
 
		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (uint8_t)va_arg(args, int);
			while (--field_width > 0)
				*str++ = ' ';
			continue;
 
		case 's':
			s = va_arg(args, char *);
			len = qstrlen(s, precision);
 
			if (!(flags & LEFT))
				while (len < field_width--)
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;
			while (len < field_width--)
				*str++ = ' ';
			continue;
		/*
		case 'p':
			if (field_width == -1) {
				field_width = 2 * sizeof(void *);
				flags |= ZEROPAD;
			}
			str = number(str,
				 (unsigned int)va_arg(args, void *), 16,
				 field_width, precision, flags);
			continue;
		*/
		case '%':
			*str++ = '%';
			continue;
 
			/* integer number formats - set up the flags and "break" */
		case 'o':
			base = 8;
			break;
 
		case 'x':
			flags |= SMALL;
		case 'X':
			base = 16;
			break;
 
		//case 'i':
		case 'd':
			flags |= SIGN;
		case 'u':
			break;
		#ifndef _DISABLE_FLOAT
		case 'f':
			flags |= SIGN + FLOAT;
			if (precision <=0 ) precision = 3;
			num_float = va_arg(args, double );
			str = number_float(str, num_float, field_width, precision, flags);
			break;
		#endif
 
		default:
			*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			continue;
		};
		
		if (!(flags & FLOAT)) {
			if (flags & SIGN)
				num = va_arg(args, int);
			else
				num = va_arg(args, uint16_t);
			str = number(str, num, base, field_width, precision, flags);
		};
	}
	*str = 0;
	return str - buf;
	
}
 
int sprintf(char *buf, const char *fmt, ...){
	
	va_list args;
	uint16_t i;
 
	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);
	return i;
	
}
 
int qprintf(uart_handle uart, const char *fmt, ...){
	char printf_buf[PRINT_BUF_SIZE];
	va_list args;
	uint16_t printed;

	va_start(args, fmt);
	printed = vsprintf(printf_buf, fmt, args);
	va_end(args);
 
	qputs(uart, printf_buf);
	
	return printed;
	
}
