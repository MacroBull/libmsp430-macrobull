
#include <msp430.h>
#include <stdint.h>

#include <stdlib.h>

#include "dev.h"
#include "uart.h"
#include "qput.h"

#include "data/json.h"

int wait;
char text[52], *p, func;

int f(const uint16_t ISR_vector, uint8_t c){ 
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
	
	a = json_CreateIntObj("n", -38);
	b = json_CreateStringObj("me'", "JSON!");
	c = json_CreateBlobObj("b", "xx", 4);
	
	a->next = b;
	b->next = c;
	
	return a;
	
}


int main(void)
{
	
	WDTCTL = WDTPW + WDTHOLD; 
	//BC1MSET;
	uart_register(_USCI_UART0, 1); // register uart0 only
	//USCI_UART_XLED_enable(_USCI_UART0);
	USCI_UART_init(_USCI_UART0, 1100000, 9600);
	
	USCI_UART_ISR_setter(_USCI_UART0, f); //set registered isr for uart0 as function f
	
	P1DIR &= ~BIT3;
	P1REN |= BIT3;
	P1OUT |= BIT3;
	
	json_handle a;
	while (1){
		p = text;
		wait = 1;
		_BIS_SR(CPUOFF);
		wait = 0;
		*(--p) = '\0';
		
		if (P1IN & BIT3) // Key not pressed
			a = json_CreateObjectObj(NULL, objTest()); // an example
		else 
			a = json_parse(text); // try to parse input string
		
		
		json_dump(text, a);
		json_free_rude(a);
		qputs(_USCI_UART0, text);
		qputc(_USCI_UART0, '\n');
		
		
	}
	
}
