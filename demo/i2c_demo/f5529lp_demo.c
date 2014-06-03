/*
 * This description is old, but code still works
 - * @author : macrobull
 - * for msp430f5529, DCO @ 1.1MHz <- now this!
 - * for msp430g2553, DCO @ 8MHz
 - * 
 - * 1. Continuously read from PCF8563 RTC second value in BCD code
 - * followed with 7 spaces(0x20)
 - * 
 - * 2. Try to read multiple data but halt by slave device,
 - * the data pointer freeze at where the transmission halted
 - * expected result is in 8 bytes
 - */

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
	uart_init(UART1, 1100000, 9600);
	uart_XLED_enable(UART1);
	
	i2c_XLED_enable(I2C0);
	i2c_slave_addr_setter(I2C0, 0x51); //PCF8563 RTC HW addr
	i2c_init(I2C0, 1100000, 400000, 1); //@400kHz
	
	qprintf(UART1, "Inited!\n");
	while (1){
	
		/* 1. get data by read register from i2c device with no delay */
		char sec = i2c_reg8_read8(I2C0, 0x02);
		qputc(UART1, sec & 0x7f); // MSb = VL> see PCF8563 datasheet
		qputc(UART1,'\n');
		
		/* 2. read multiple data with uncertain length */
		char x[10] = {0x20, 0x21, 0x22, 0x23, 
			0x24, 0x25, 0x26, 0x27, 0x28, 0x00};
		x[0] = 0x02;
		
		i2c_write( I2C0, x, 1); // write 1 byte starting from x[0]
		char *s = i2c_read(I2C0, x, 2); // read 2 byte with LSB = x[0]
		qputs(UART1, s); // normally s = &x[1] 
		
		__delay_cycles(100000);
	}
}




