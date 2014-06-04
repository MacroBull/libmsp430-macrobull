
#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "ucs.h"
#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "random.h"

void main(){

	WDT_DISABLE;

	ucs_DCOFreq_set(10000000);
	uart_init(UART1, 10000000, 9600);
	uart_XLED_enable(UART1);

	while (1){
		uint16_t m = rand_fromADC(250);
		uint16_t n = rand_fromVLO(PWM2);
		qprintf(UART1, "%u %u \n", m,  n);
		__delay_cycles(500000);
	}
}




