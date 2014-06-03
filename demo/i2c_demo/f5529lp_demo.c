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


void main(){
	
	WDT_DISABLE;
	
// 	ucs_DCOFreq_set(1100000);
	uart_init(UART0, 1100000, 9600);
	uart_XLED_enable(UART0);
	
// 	i2c_XLED_enable(I2C0);
// 	i2c_slave_addr_setter(I2C0, 0x51);
// 	i2c_init(I2C0, 1100000, 400000, 1); //@400kHz
	
	qprintf(UART0, "Inited!\n");
// 	_EINT();
	while (1){
		qprintf(UART0, "%gg\n");
		__delay_cycles(1000000);
	}
}




