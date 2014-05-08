/*
 * @author : macrobull
 * for msp430f5529, echo chars received in uart0 via uart1, uart0 continuously send 'Y'
 * baudrate=9.6k
 * isr register function may not ready for msp430f5529
 */


#include <msp430.h>
#include <stdint.h>


#include "dev.h"
#include "uart.h"
#include "qput.h"
#include "calib_val.h"

int f(const uint16_t ISR_vector, char c){ // "echo" function
	
	qputc(_USCI_UART0, c);
	
	return 0;
}

int main(void)
{
	BC1MSET;
	WDTCTL = WDTPW + WDTHOLD; 
	//BC1MSET;
	uart_register(_USCI_UART0, 1); // register uart0 only
	USCI_UART_XLED_enable(_USCI_UART0);
	USCI_UART_init(_USCI_UART0, 1000000, 9600);
	
	USCI_UART_ISR_setter(_USCI_UART0, f); //set registered isr for uart0 as function f
	
	while (1){
		qputc(_USCI_UART0,'Y');
		__delay_cycles(500000);
	}
	
}
