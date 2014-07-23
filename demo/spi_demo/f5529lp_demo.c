
#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "uart.h"
#include "spi.h"
#include "qput.h"

void main(){
	
	WDT_DISABLE;
	
	uart_init(UART1, 1100000, 9600);
	uart_XLED_enable(UART1);
	
	spi_init(SPI0, 1100000, 10000, SPI_MODE_MASTER);
	spi_XLED_enable(SPI0);
	
	
	qputs(UART1, "Starting...\n");
	
	int addr = 0xff00, val;
	
	while (1){
		val = spi_reg16_read16(SPI0, addr++, 20);
		
		qputh(UART1, addr >> 8);
		qputh(UART1, addr & 0xff);
		qputc(UART1, '=');
		qputh(UART1, val >> 8);
		qputh(UART1, val & 0xff);
		qputc(UART1, '\n');
		__delay_cycles(100000);
	}
}




