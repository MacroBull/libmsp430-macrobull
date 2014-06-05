
#include <msp430.h>
#include "wdt.h"
#include "calib_val.h"
#include "hal/perip.h"
#include "bsp/exp430g2.h"

#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "isr_wrapper.h"

int16_t f0(uint16_t v, int8_t c){
	uart_RXLED_on(UART0);
	qprintf(UART0, "A0:%c\n", c);
	uart_RXLED_off(UART0);
	return 0;
}

isr_callback_8 rx_list[]={f0, NULL};
//isr_callback_8 rx_list[]={uart_TXLED_off, f0, uart_RXLED_off, NULL};

void main(){
	
	WDT_DISABLE;
// 	BC1MSET;
	
	USCIAB0RX_ISR_callbacks = rx_list;
	
	uart_init(UART0, 1100000, 9600);
	uart_XLED_enable(UART0);
	uart_interrupt_enable(UART0);
	
	_EINT();
	while (1){
		qprintf(UART0, "good game\n");
		__delay_cycles(1000000);
	}
}




