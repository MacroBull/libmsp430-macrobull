/*
 * @author : macrobull
 * for msp430f5529, DCO @ 1.1MHz
 * for msp430g2553, DCO @ 8MHz
 * 
 * 1. Continuously read from PCF8563 RTC second value in BCD code
 * followed with 7 spaces(0x20)
 * 
 * 2. Try to read multiple data but halt by slave device,
 * the data pointer freeze at where the transmission halted
 * expected result is in 8 bytes
 */


#include <msp430.h>
#include "dev.h"
#include "uart.h"
#include "i2c.h"
//#include "qprintf.h"


void main(){
	
	WDT_disable;
	
	/* Launchpad clock set */
	//BC8MSET;
	//USCI_UART_init(_USCI_UART0, 8000000, 9600);
	/* f5529 clock set */
	USCI_UART_init(_USCI_UART1, 1100000, 9600);
	
	USCI_I2C_XLED_enable(_USCI_I2C0);
	USCI_I2C_slave_addr_setter(_USCI_I2C0, 0x51); //PCF8563 RTC HW addr
	/* Launchpad clock set */
	//USCI_I2C_init(_USCI_I2C0, 8000000, 400000, 1); //@400kHz
	/* f5529 clock set */
	USCI_I2C_init(_USCI_I2C0, 1100000, 400000, 1); //@400kHz
	
	while (1){
		
		/* 1. get data by read register from i2c device with no delay */
		char sec = USCI_I2C_reg8_read8(_USCI_I2C0, 0x02);
		qputc( _USCI_UART1, sec & 0x7f); // MSb = VL -> see PCF8563 datasheet
		qputs( _USCI_UART1,"       ");
		
		char x[10] = {0x20, 0x21, 0x22, 0x23, 
			0x24, 0x25, 0x26, 0x27, 0x28, 0x00};
		
		x[0] = 0x02;
		
		
		/* 2. read multiple data with uncertain length */
		USCI_I2C_write( _USCI_I2C0, x, 1); // write 1 byte starting from x[0]
		char *s = USCI_I2C_read( _USCI_I2C0, x, 2); // read 2 byte with LSB = x[0]
		qputs( _USCI_UART1, s); // normally s = &x[1] 
		
		__delay_cycles(100000);
		
	}
}
	