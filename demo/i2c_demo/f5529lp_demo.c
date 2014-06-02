/*
 * 
 * 
 */


#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "isr_wrapper.h"

#include "i2c.h"

int16_t f0(uint16_t v, int8_t c){
	qprintf(UART1, "push\n");
	return 0;
}

_ISR_callback_8 rx_list[]={f0,NULL};

void main(){
	
	WDT_DISABLE;
	
  	USCI_A1_ISR_callbacks = rx_list;
	uart_init(UART1, 1100000, 9600);
	uart_XLED_enable(UART1);
	uart_interrupt_enable(UART1);
	
	i2c_XLED_enable(I2C0);
	i2c_slave_addr_setter(I2C0, 0x51);
	i2c_init(I2C0, 1100000, 400000, 1); //@400kHz
	
	qprintf(UART1, "Inited!\n");
// 	_EINT();
	while (1){
		char sec = i2c_reg8_read8(I2C0, 0x02);
		qprintf(UART1, "%u\n", sec);
		__delay_cycles(1000000);
	}
}




