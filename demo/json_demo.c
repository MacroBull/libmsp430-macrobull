
#include <msp430.h>
#include <stdint.h>

#include "dev.h"
#include "uart.h"
#include "qput.h"

#include "data/json.h"

int wait;
char text[52], *p, func;

int f(const uint16_t ISR_vector, char c){ 
	// read input, end with '\n'
	if (wait) {
		*(p++) = c;
		if ('\n' == c)
			return -CPUOFF;
	}
	return 0;
	
}

json_handle objTest(){
	//a(n:38)->b(me:JSON!)->c(b:xx)
	json_handle a, b, c;
	
	a = json_createIntObj("n", -38);
	b = json_createStringObj("me'", "JSON!");
	c = json_createBlobObj("b", "xx", 4);
	
	a->next = b;
	b->next = c;
	
	return a;
	
}


int main(void)
{
	
	WDTCTL = WDTPW + WDTHOLD; 
	//BC1MSET;
	uart_register(_USCI_UART1, 1); // register uart0 only
	USCI_UART_XLED_enable(_USCI_UART1);
	USCI_UART_init(_USCI_UART1, 1100000, 9600);
	
	USCI_UART_ISR_setter(_USCI_UART1, f); 
	
	json_handle a;
	while (1){
		qputc(_USCI_UART1, '\n');
		__delay_cycles(200000);
		
	}
	
}
