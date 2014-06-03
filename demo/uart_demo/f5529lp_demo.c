
#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "isr_wrapper.h"

int16_t f0(uint16_t v, int8_t c){
	if (USCI_A0_VECTOR ==  (v>>8))
		qprintf(UART0, "It is A0\n");
	else
		qprintf(UART0, "It is A1\n");
	return 0;
}

isr_callback_8 rx_list[]={f0,NULL};

void main(){
	
	WDT_DISABLE;
	
  	USCI_A0_ISR_callbacks = rx_list;
  	USCI_A1_ISR_callbacks = rx_list;
	
	uart_init(UART0, 1100000, 9600);
	uart_init(UART1, 1100000, 9600);
	uart_XLED_enable(UART0);
	uart_XLED_enable(UART1);
	uart_interrupt_enable(UART0);
	uart_interrupt_enable(UART1);
	_EINT();
	while (1){
		qprintf(UART0, "good game\n");
		qprintf(UART1, "niceboat\n");
		__delay_cycles(1000000);
	}
}




