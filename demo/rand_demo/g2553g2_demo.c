
#include <msp430.h>
#include "wdt.h"
#include "calib_val.h"
#include "hal/perip.h"
#include "bsp/exp430g2.h"

#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "random.h"

void main(){

	WDT_DISABLE;

	BC8MSET;
	uart_init(UART0, 8000000, 9600);
	uart_XLED_enable(UART0);
	qputs(UART0, "Inited.\n");

	while (1){
		uint16_t m = rand_fromADC();
		uint16_t n = rand_fromVLO();
		qprintf(UART0, "%u %u \n", m, n);
		__delay_cycles(500000);
	}
}




